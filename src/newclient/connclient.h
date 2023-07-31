#ifndef CONNCLIENT_NEWCLIENT_H
#define CONNCLIENT_NEWCLIENT_H
#include <functional>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Logging.h>
#include "codec.h"

using MsgCallback = std::function<void(const muduo::net::TcpConnectionPtr &,
                                       const std::string &, muduo::Timestamp)>;
class ConnClient {
public:
    ConnClient(muduo::net::EventLoop *loop,
               const muduo::net::InetAddress &serverAddr,
               const std::string &name) :
        loop_(loop),
        client_(loop_, serverAddr, name), serverAddr_(serverAddr),
        codec_(std::bind(&ConnClient::onMessage, this, std::placeholders::_1,
                         std::placeholders::_2, std::placeholders::_3)) {
        client_.enableRetry();
    }
    ~ConnClient() = default;
    
    void connect();
    void disconnect();
    void stop();
    void send(const std::string &message);
    void setConnectionCallback(const muduo::net::ConnectionCallback &cb);
    void setMessageCallback(const MsgCallback &cb);
    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   const std::string &, muduo::Timestamp);

private:
    muduo::net::EventLoop *loop_;
    muduo::net::TcpClient client_;
    muduo::net::InetAddress serverAddr_;
    LengthHeaderCodec codec_;
    MsgCallback mcb_;
    muduo::net::ConnectionCallback ccb_;
};

#endif