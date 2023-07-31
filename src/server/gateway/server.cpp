#include "server.h"
#include "clientmap.h"
#include "constant/msg.h"
#include <math.h>
#include <stdexcept>
#include "token/jwt_token.h"

ClientPtr ChatServer::registerClient(const TcpConnectionPtr &conn,
                                     const string &message) {
    json j = json::parse(message);
    int platform;
    std::string userId;
    std::string token;
    try {
        platform = j["platform"];
        userId = j["userId"];
        token = j["token"];
    } catch (...) {
        json j;
        j["code"] = MSG_CODE_INVALID_MSG_PARAM;
        j["msg"] = "invalid message";
        conn->shutdown();
        return nullptr;
    }

    try {
        auto tokeninfo = parseToken(token);
        if (tokeninfo.userID != userId || tokeninfo.platform != platform
            || tokeninfo.expireTimeSeconds < 0) {
            throw std::invalid_argument("invalid token");
        }
        auto tokenInRedis = authCache.getToken(
            getTokenKey(tokeninfo.userID, tokeninfo.platform));
        if (tokenInRedis.empty() || tokenInRedis == "ERROR") {
            throw std::invalid_argument("invalid token");
        }
    } catch (...) {
        json j;
        j["code"] = MSG_CODE_INVALID_TOKEN;
        j["msg"] = "invalid token";
        conn->shutdown();
        return nullptr;
    }

    auto client =
        std::make_shared<Client>(platform, userId, conn, shared_from_this());

    clientMap.insert(client);
    return client;
}

void ChatServer::onStringMessage(const TcpConnectionPtr &conn,
                                 const string &message, Timestamp st) {
    auto client = clientMap.find(conn);
    if (!client) {
        client = registerClient(conn, message);
        if (!client) { return; }
    }
    client->handlerMsg(message);
}

int main(int argc, char *argv[]) {
    EventLoop loop;
    uint16_t port = static_cast<uint16_t>(8081);
    std::cout << "TcpServer listening on 0.0.0.0:8081" << std::endl;
    InetAddress serverAddr(port);
    ChatServer server(&loop, serverAddr);
    if (argc > 2) { server.setThreadNum(atoi(argv[2])); }
    server.start();
    loop.loop();
}