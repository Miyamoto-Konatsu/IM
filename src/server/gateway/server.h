#ifndef SERVER_GATEWAY_H
#define SERVER_GATEWAY_H

#include "muduo/base/Logging.h"
#include "muduo/net/Buffer.h"
#include "muduo/net/Endian.h"
#include "muduo/net/TcpConnection.h"
#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "codec.h"
#include "muduo/base/ThreadLocalSingleton.h"
#include "muduo/base/ThreadLocal.h"
#include "clientmap.h"
#include <muduo/base/Singleton.h>
#include <memory>
#include <json.hpp>

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

class ChatServer : muduo::noncopyable,
                   std::enable_shared_from_this<ChatServer> {
public:
    ChatServer(muduo::net::EventLoop *loop, const InetAddress &listenAddr) :
        server_(loop, listenAddr, "ChatServer"),
        clientMap(muduo::Singleton<ClientMap>::instance()),
        codec_(std::bind(&ChatServer::onStringMessage, this, _1, _2, _3)) {
        server_.setConnectionCallback(
            std::bind(&ChatServer::onConnection, this, _1));
        server_.setMessageCallback(
            std::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
    }

    void setThreadNum(int numThreads) {
        server_.setThreadNum(numThreads);
    }

    void start() {
        // server_.setThreadInitCallback(
        //     std::bind(&ChatServer::threadInit, this, _1));
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr &conn) {
        LOG_INFO << conn->peerAddress().toIpPort() << " -> "
                 << conn->localAddress().toIpPort() << " is "
                 << (conn->connected() ? "UP" : "DOWN");
        if (conn->connected()) {
            // do nothing
        } else {
            clientMap.erase(conn);
        }
    }

    void onStringMessage(const TcpConnectionPtr &conn, const string &message,
                         Timestamp st) {
        auto client = clientMap.find(conn);
        if (!client) {
            //从message中解析出platform和id
            json j = json::parse(message);
            int platform = j["platform"];
            std::string userId = j["userId"];
            client = std::make_shared<Client>(platform, userId, conn,
                                              shared_from_this());
            clientMap.insert(client);
        }
        client->handlerMsg(message);
    }

    TcpServer server_;
    LengthHeaderCodec codec_;
    ClientMap &clientMap;
};

#endif // SERVER_GATEWAY_H