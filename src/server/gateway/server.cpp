#include "server.h"
#include "client.h"
#include "clientmap.h"
#include "constant/msg.h"
#include <math.h>
#include <memory>
#include <stdexcept>
#include "token/jwt_token.h"
#include <muduo/base/Logging.h>
#include "rpcService.h"
#include <csignal>

ClientPtr ChatServer::registerClient(const TcpConnectionPtr &conn,
                                     const string &message) {
    json j = json::parse(message);
    int platform;
    std::string userId;
    std::string token;
    try {
        platform = j["platform"];
        userId = j["userID"];
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

void ChatServer::send(muduo::net::TcpConnection *conn, const string &message) {
    codec_.send(conn, message);
}

int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);
    muduo::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
    EventLoop loop;
    uint16_t port = static_cast<uint16_t>(8081);
    std::cout << "TcpServer listening on 0.0.0.0:8081" << std::endl;
    InetAddress serverAddr(port);
    std::shared_ptr<ChatServer> server =
        std::make_shared<ChatServer>(&loop, serverAddr);

    server->setThreadNum(8);

    server->start();
    GatewayServiceImpl::startServer(server);
    loop.loop();
}