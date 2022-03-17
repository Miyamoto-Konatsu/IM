#include "MessageType.h"
#include "json.hpp"
#include "server/model/User.h"

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;
using json = nlohmann::json;

int USER_ID = -1;
vector<User> FRIENDS;

bool HandleChatMsg(const json &response);
void ShowFriends();
using MsgHandler = function<bool(const json &)>;

unordered_map<MsgType, MsgHandler> handler_map_;

bool Insert(int fd);

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
    char password[20] = {0};
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
    USER_ID = response["user_id"];
    vector<string> friend_json = response.at("friends");
    for (const auto &f : friend_json) {
        json f_js = json::parse(f);
        FRIENDS.emplace_back(f_js.at("user_id"), f_js.at("nickname"), "guess",
                             f_js.at("state"));
    }

    //历史消息
    if (response.contains("offlinemsg")) {
        vector<string> message_json = response.at("offlinemsg");
        cout << "未读消息" << endl;
        for (const auto &message : message_json) {
            json msg = json::parse(message);
            cout << msg.at("user_id") << ": ";
            cout << msg.at("msg") << endl;
        }
    }
    return true;
}

bool SignOut(int fd) {

    json request;
    request["msg_type"] = MsgType::sign_out;
    request["user_id"] = USER_ID;
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "Sign out failed" << endl;
    }
    cout << "Sign out success" << endl;

    //登出后重置
    USER_ID = -1;
    FRIENDS.clear();
}

bool SendMsg(int fd) {
    int friend_id;
    char message[1024] = {0};
    cout << "Input friend id please:";
    cin >> friend_id;
    cin.get();
    cout << "Input message please:";
    cin.getline(message, 1024);
    bool is_friend = false;
    for (const auto &f : FRIENDS) {
        if (f.GetUserId() == friend_id) {
            is_friend = true;
            break;
        }
    }
    if (!is_friend) {
        cout << friend_id << " is not your friend, please add him first"
             << endl;
        return false;
    }
    json request;
    request["msg_type"] = MsgType::chat_send;
    request["user_id"] = USER_ID;
    request["friend_id"] = friend_id;
    request["msg"] = message;
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "Send failed" << endl;
        return false;
    }
    return true;
}

bool RecvFromServer(int fd) {
    while (true) {
        char buf[1024] = {0};
        if (-1 == recv(fd, buf, 1024, 0)) {
            cout << "Error occurs in function RecvFromServer" << endl;
            exit(-1);
        }
        json response = json::parse(buf);
        handler_map_[response["msg_type"]](response);
    }
}

bool HandleChatMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    cout << response["friend_id"] << endl;
    cout << response["msg"] << endl;
    return true;
}

bool HandleInsertMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["user_id"] << endl;
        cout << response["friend_id"] << endl;
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    cout << response["friend_id"] << endl;
    cout << response["msg"] << endl;
    return true;
}

int Client(int client_fd) {
    while (true) {
        cout << "1 : Send message" << endl;
        cout << "2 : Sign out" << endl;
        cout << "3 : Add friend" << endl;
        cout << "4 : Show friends" << endl;
        string input;
        cin >> input;
        switch (atoi(input.c_str())) {
        case 1:
            SendMsg(client_fd);
            break;
        case 2:
            SignOut(client_fd);
            return true;
        case 3:
            Insert(client_fd);
        case 4:
            ShowFriends();
        default:
            break;
        }
    }
}

bool Insert(int fd) {
    int friend_id;
    cout << "Input friend id please:";
    cin >> friend_id;
    json request;
    request["msg_type"] = MsgType::add_friend;
    request["user_id"] = USER_ID;
    request["friend_id"] = friend_id;
    if (-1 == send(fd, request.dump().c_str(), request.dump().size() + 1, 0)) {
        cout << "send add_friend failed" << endl;
        return false;
    }
    return true;
}

void InitHandlerMap() {
    handler_map_[MsgType::chat_send] = MsgHandler(&HandleChatMsg);
    handler_map_[MsgType::add_friend_res] = MsgHandler(&HandleInsertMsg);
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
    InitHandlerMap();
    while (true) {
        cout << "1 : Sign up" << endl;
        cout << "2 : Sign in" << endl;
        cout << "other : Quit" << endl;
        string input;
        cin >> input;
        switch (atoi(input.c_str())) {
        case 1:
            Register(client_fd);
            break;
        case 2:
            if (!SignIn(client_fd))
                break;
            {
                std::thread t(RecvFromServer, client_fd);
                t.detach();
            }
            Client(client_fd);
            break;
        default:
            close(client_fd);
            return 0;
        }
    }
    close(client_fd);
    return 0;
}

void ShowFriends() {
    for (const auto &f : FRIENDS) {
        cout << "id: " << f.GetUserId() << " nickname: " << f.GetNickname()
             << " state: " << f.GetState() << endl;
    }
}
