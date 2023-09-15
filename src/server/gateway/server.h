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
#include "cache/auth.h"
#include "gateMsghandler.h"
#include <csignal>
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;


class ChatServer : public std::enable_shared_from_this<ChatServer> {
public:
    ChatServer(muduo::net::EventLoop *loop, const InetAddress &listenAddr) :
        server_(loop, listenAddr, "ChatServer"), msgHandler(),
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

    GateMsgHandler &getMsgHandler() {
        return msgHandler;
    }

    void send(muduo::net::TcpConnection *conn, const string &message);

    ClientMap &getClientMap() {
        return clientMap;
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
                         Timestamp st);

    ClientPtr registerClient(const TcpConnectionPtr &conn,
                             const string &message);
    TcpServer server_;
    LengthHeaderCodec codec_;
    ClientMap &clientMap;
    AuthCache authCache;
    GateMsgHandler msgHandler;
};

#endif // SERVER_GATEWAY_H