#include "client.h"
#include <cassert>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include <tuple>
#include "constant/msg.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/EventLoopThreadPool.h"

void Client::onConnection(const muduo::net::TcpConnectionPtr &conn) {
    if (conn->connected()) {
        std::cout << "connected" << std::endl;
        isConnect_ = true;
    } else {
        std::cout << "disconnected" << std::endl;
        isConnect_ = false;
    }
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
        data["groupID"] = groupID;
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

void Client::login(std::string userID, std::string password, int platform) {
    std::string secret("secret");
    std::string token =
        apiClient_->authUserToken(userID, password, secret, platform);
    std::cout << "token: " << token << std::endl;
    user_.setUserID(userID);
    user_.setToken(token);
    platform_ = platform;
    registerClient();
}

void Client::sendMsg(std::string toUserID, std::string content, int msgType) {
    json msgSend;
    msgSend["type"] = TCP_MSG_OP_TYPE_SEND_MSG;
    switch (msgType) {
    case TCP_MSG_SINGLE_CHAT_TYPE: {
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

void test(std::string userID, muduo::net::EventLoop *loop) {
    signal(SIGPIPE, SIG_IGN);
    std::shared_ptr<ConnClient> connClient = std::make_shared<ConnClient>(
        loop, muduo::net::InetAddress(8081), "ConnClient");

    std::shared_ptr<ApiClient> apiClient =
        std::make_shared<ApiClient>("localhost", 8080);

    Client client(connClient, apiClient);
    connClient->connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (!client.isConnect()) { return; }
    try{
        client.login(userID, "test", 1);
    } catch (...) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 20);

    int i = 0;
    while (i < 1000) {
        int randomNumber = dis(gen); // 生成随机数
        std::stringstream ss;
        ss << randomNumber;
        std::string toUserID = ss.str();
        std::string content =
            userID + "hello " + toUserID + " " + std::to_string(i++);
        client.sendMsg(toUserID, content, TCP_MSG_SINGLE_CHAT_TYPE);
        //std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    while (true) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
}

int main() {
    muduo::net ::EventLoop loop;

    // muduo::net ::EventLoopThreadPool loopPool(&loop, "chat-loadtest");
    // loopPool.setThreadNum(6);
    // loopPool.start();
    // std::vector<std::thread> threads;
    // for (int i = 0; i < 20; i++) {
    //     threads.push_back(
    //         std::thread(test, std::to_string(i), loopPool.getNextLoop()));
    // }
    // for (int i = 0; i < 20; i++) { threads[i].join(); }
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
