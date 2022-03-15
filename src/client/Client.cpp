#include "MessageType.h"
#include "json.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
using json = nlohmann::json;

bool Register(int fd) {
    char nickname[50], password[20];
    cout << "Input nickname please:";
    cin >> nickname;
    cout << "Input password please:";
    cin >> password;
    json request;
    request["msg_type"] = MsgType::sign_up;
    request["nickname"] = string(nickname);
    request["password"] = string(password);
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "Sign up failed" << endl;
        return false;
    }
    char buf[1024] = {0};
    if (-1 == recv(fd, buf, 1024, 0)) {
        return false;
    }
    json response = json::parse(buf);
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    return true;
}

bool SignIn(int fd) {
    int user_id;
    char password[20];
    cout << "Input user id please:";
    cin >> user_id;
    cout << "Input password please:";
    cin >> password;
    json request;
    request["msg_type"] = MsgType::sign_in;
    request["user_id"] = user_id;
    request["password"] = string(password);
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "Sign in failed" << endl;
        return false;
    }
    char buf[1024] = {0};

    if (-1 == recv(fd, buf, 1024, 0)) {
        return false;
    }
    json response = json::parse(buf);
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    cout << response["nickname"] << endl;
    return true;
}

bool SignOut(int fd) {
    int user_id;
    char password[20];
    cout << "Input user id please:";
    cin >> user_id;
    json request;
    request["msg_type"] = MsgType::sign_out;
    request["user_id"] = user_id;
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "Sign out failed" << endl;
    }
}

int main(int argc, char *argv[]) {
    /*  if (argc != 3) {
         cout << "server ip and port are needed" << endl;
         exit(0);
     } */
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    char ip[] = "127.0.0.1";
    char port[] = "8899";
    sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(port));
    sa.sin_addr.s_addr = inet_addr(ip);
    if (connect(client_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr))) {
        cout << "connect failed" << endl;
        exit(0);
    }

    while (true) {
        cout << "1 : Sign up" << endl;
        cout << "2 : Sign in" << endl;
        cout << "3 : Sign out" << endl;
        string input;
        cin >> input;
        switch (atoi(input.c_str())) {
        case 1:
            Register(client_fd);
            break;
        case 2:
            SignIn(client_fd);
            break;
        case 3:
            SignOut(client_fd);
            break;
        default:
            break;
        }
    }
    return 0;
}