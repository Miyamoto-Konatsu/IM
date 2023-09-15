#include "connclient.h"
#include "muduo/net/Callbacks.h"
#include <cassert>
#include <thread>

void ConnClient::connect() {
    client_.connect();
}

void ConnClient::disconnect() {
    client_.disconnect();
}

void ConnClient::stop() {
    client_.stop();
}

void ConnClient::send(const std::string &message) {
    codec_.send(get_pointer(client_.connection()), message);
}

void ConnClient::setConnectionCallback(
    const muduo::net::ConnectionCallback &cb) {
    client_.setConnectionCallback(cb);
}

void ConnClient::setMessageCallback(const MsgCallback &cb) {
    mcb_ = cb;
    client_.setMessageCallback(
        std::bind(&LengthHeaderCodec::onMessage, &codec_, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
}

void ConnClient::onMessage(const muduo::net::TcpConnectionPtr &conn,
                           const std::string &message,
                           muduo::Timestamp receiveTime) {
    mcb_(conn, message, receiveTime);
}

bool ConnClient::connected() {
    return muduo::get_pointer(client_.connection()) != nullptr;
}