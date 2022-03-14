#include "Server.h"
#include <functional>
#include <iostream>

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
    std::cout << conn->peerAddress().toIpPort() << " sent:";
    muduo::string msg(buf->retrieveAllAsString());
    std::cout << msg << "time:" << time.toString() << std::endl;
    conn->send(msg);
}