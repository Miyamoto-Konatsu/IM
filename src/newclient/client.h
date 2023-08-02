#ifndef CLIENT_NEWCLIENT_H
#define CLIENT_NEWCLIENT_H

#include <httplib.h>
#include <memory>
#include <muduo/net/TcpConnection.h>
#include "connclient.h"
#include "apiclient.h"
#include "user.h"

class Client {
public:
    Client(std::shared_ptr<ConnClient> connClient,
           std::shared_ptr<ApiClient> apiClient) :
        connClient_(connClient),
        apiClient_(apiClient) {
        connClient_->setConnectionCallback(
            std::bind(&Client::onConnection, this, std::placeholders::_1));
        connClient_->setMessageCallback(
            std::bind(&Client::onMessage, this, std::placeholders::_1,
                      std::placeholders::_2, std::placeholders::_3));
    }
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   const std::string &message, muduo::Timestamp receiveTime);

    // 输入用户名和密码和终端，然后获取token
    void login();
    
    void sendMsg();
    void main();

    void registerClient();

private:
    std::shared_ptr<ApiClient> apiClient_;
    std::shared_ptr<ConnClient> connClient_;
    User user_;
    int platform_;
    std::thread mainThread_;
};
#endif