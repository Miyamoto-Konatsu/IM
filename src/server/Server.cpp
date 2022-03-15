#include "server/Server.h"
#include "server/Service.h"
#include <functional>
#include <iostream>
#include "json.hpp"
#include "MessageType.h"

Server::Server(EventLoop *loop, const InetAddress &inet_addr,
               const string &name)
    : server_(loop, inet_addr, name), loop_(loop) {
    server_.setConnectionCallback(
        std::bind(&Server::onConnection, this, std::placeholders::_1));
    server_.setMessageCallback(
        std::bind(&Server::onMessage, this, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
}

void Server::start() { server_.start(); }

void Server::onConnection(const TcpConnectionPtr &conn) {
    if (conn->disconnected()) {
        std::cout << conn->peerAddress().toIpPort() << "closed" << std::endl;
        conn->shutdown();
    }
}

void Server::onMessage(const TcpConnectionPtr &conn, Buffer *buf,
                       Timestamp time) {
    muduo::string msg(buf->retrieveAllAsString());
    nlohmann::json msg_json = nlohmann::json::parse(msg.c_str());
    Service* service = Service::GetInstance();
    MsgType msg_type = msg_json["msg_type"].get<MsgType>();
    MsgHandler handler =  service->GetHandler(msg_type);
    handler(conn, msg_json, time);
}

