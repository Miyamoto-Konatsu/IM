#ifndef CLIENT_NEWCLIENT_H
#define CLIENT_NEWCLIENT_H

#include <atomic>
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

    // string fromUserID = 1;
    // string toUserID = 2;
    // string groupID = 3;
    // int32 msgType = 4;
    // int64 startSeq = 5;
    // int64 endSeq = 6;
    void syncMsgsHelper(const std::string &fromUserID,const std::string& toUserID, const std::string &groupID
                  , int msgType, int64_t startSeq, int64_t endSeq);

    void syncMsgs();

    void getAllUnreadConversations();

    void joinGroup();

    void createGroup();
    
    void main();

    void registerClient();

    void login(std::string userID, std::string password, int platform);

    void sendMsg(std::string toUserID, std::string content, int msgType);

    bool isConnect() {
        return isConnect_;
    }
private:
    std::shared_ptr<ApiClient> apiClient_;
    std::shared_ptr<ConnClient> connClient_;
    User user_;
    int platform_;
    std::thread mainThread_;
    std::atomic<bool> isConnect_;
};
#endif