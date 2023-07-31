#ifndef CLIENT_GATEWAY_H
#define CLIENT_GATEWAY_H
#include <memory>
#include <muduo/net/TcpConnection.h>

using muduo::net::TcpConnectionPtr;
class ChatServer;
class Client {
public:
    Client(int platform, std::string userId, TcpConnectionPtr conn,
           std::shared_ptr<ChatServer> server) :
        platform_(platform),
        server_(server), conn_(conn), id_(userId) {
    }

    Client(const Client &) = delete;

    Client &operator=(const Client &) = delete;

    ~Client() = default;

    std::string getClinetId() const {
        return id_;
    }

    int getPlatform() const {
        return platform_;
    }

    TcpConnectionPtr getConn() const {
        return conn_;
    }

    void handlerMsg(const std::string &msg);

private:
    int platform_;
    std::shared_ptr<ChatServer> server_;
    TcpConnectionPtr conn_;
    std::string id_;
};
#endif