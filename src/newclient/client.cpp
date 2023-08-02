#include "client.h"
#include <iostream>
#include "constant/msg.h"
void Client::onConnection(const muduo::net::TcpConnectionPtr &conn) {
    // do nothing
}

void Client::onMessage(const muduo::net::TcpConnectionPtr &conn,
                       const std::string &message,
                       muduo::Timestamp receiveTime) {
    std::cout << "receive message: " << message << std::endl;
    std::cout << "receive time: " << receiveTime.toFormattedString()
              << std::endl;
}

void Client::registerClient() {
    json data;
    data["userID"] = user_.getUserID();
    data["token"] = user_.getToken();
    data["platform"] = platform_;
    connClient_->send(data.dump());
}
void Client::login() {
    std::string userID, password, secret = "secret";
    int platform;
    std::cout << "userID: ";
    std::cin >> userID;
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "platform: ";
    std::cin >> platform;
    std::string token =
        apiClient_->authUserToken(userID, password, secret, platform);
    std::cout << "token: " << token << std::endl;
    user_.setUserID(userID);
    user_.setSecret(secret);
    user_.setToken(token);
    platform_ = platform;
    registerClient();
}

void Client::sendMsg() {
    std::string toUserID, groupID;
    std::string content;
    int msgType;
    json msgSend;
    msgSend["type"] = TCP_MSG_OP_TYPE_SEND_MSG;
    std::cout << "msg type: \n single chat:1\n group chat:2" << std::endl;
    std::cin >> msgType;
    switch (msgType) {
    case TCP_MSG_SINGLE_CHAT_TYPE: {
        std::cout << "to userID: ";
        std::cin >> toUserID;
        std::cin.get();
        std::cout << "content: ";
        std::getline(std::cin, content);
        json data;
        data["toUserID"] = toUserID;
        data["content"] = content;
        data["msgType"] = TCP_MSG_SINGLE_CHAT_TYPE;
        data["fromUserID"] = user_.getUserID();
        msgSend["data"] = data;
        connClient_->send(msgSend.dump());
        break;
    }
    case TCP_MSG_GROUP_CHAT_TYPE: {
        std::cout << "groupID: ";
        std::cin >> groupID;
        std::cout << "content: ";
        std::cin.get();
        std::getline(std::cin, content);
        json data;
        data["groupID"] = toUserID;
        data["content"] = content;
        data["msgType"] = TCP_MSG_GROUP_CHAT_TYPE;
        data["fromUserID"] = user_.getUserID();
        msgSend["data"] = data;
        connClient_->send(msgSend.dump());
        break;
    }
    default: {
        std::cout << "msg type error" << std::endl;
        return;
    }
    }
}
void Client::main() {
    mainThread_ = std::thread([this]() {
        std::string message;
        while (true) {
            std::cout << "input message: ";
            std::cin >> message;
            if (message == "login") {
                login();

            } else if (message == "exit") {
                break;
            } else if (message == "send") {
                sendMsg();
            }
        }
    });
}
int main() {
    muduo::net::EventLoop loop;
    std::shared_ptr<ConnClient> connClient = std::make_shared<ConnClient>(
        &loop, muduo::net::InetAddress(8081), "ConnClient");

    std::shared_ptr<ApiClient> apiClient =
        std::make_shared<ApiClient>("localhost", 8080);

    Client client(connClient, apiClient);
    connClient->connect();
    client.main();
    loop.loop();
    return 0;
}
