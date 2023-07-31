#include "client.h"
#include <iostream>

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

void Client::send(const std::string &message) {
    connClient_->send(message);
}

void Client::login() {
    std::string userID, password, secret="secret";
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
    // std::string loginMessage = user_.loginMessage();
    // std::cout << "login message: " << loginMessage << std::endl;
    // connClient_->send(loginMessage);
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
            } else {
                send(message);
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
