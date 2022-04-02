#include "Common.h"
#include "MessageType.h"
#include "json.hpp"
#include "server/model/Group.h"
#include "server/model/User.h"
#include <arpa/inet.h>
#include <condition_variable>
#include <iostream>
#include <muduo/net/Socket.h>
#include <muduo/net/TcpServer.h>
#include <mutex>
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
condition_variable CV;
mutex MUTEX;
json response;
int USER_ID = -1;
vector<User> FRIENDS;
vector<Group> GROUPS;

using MsgHandler = function<bool(const json &)>;

unordered_map<MsgType, MsgHandler> handler_map_;

bool HandleChatMsg(const json &response);
void ShowFriends();
bool QueryGroup(int);
bool Send(int fd, json &request) {
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "Create group failed" << endl;
        free(packet);
        return false;
    }
    free(packet);
    return true;
}

bool AddFriend(int fd);

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
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "Register failed" << endl;
        free(packet);
        return false;
    }
    free(packet);
    /* char buf[1024] = {0};
    if (-1 == recv(fd, buf, 1024, 0)) {
        return false;
    } */
    unique_lock<mutex> lock(MUTEX);
    cout << "wait" << endl;

    CV.wait(lock);
    // response = json::parse(buf);
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
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "Sign in failed" << endl;
        free(packet);
        return false;
    }
    free(packet);

    /* char buf[1024] = {0};

    if (-1 == recv(fd, buf, 1024, 0)) {
        return false;
    } */
    unique_lock<mutex> lock(MUTEX);
    cout << "wait" << endl;

    CV.wait(lock);
    // response = json::parse(buf);
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
    QueryGroup(fd);
    return true;
}

bool SignOut(int fd) {

    json request;
    request["msg_type"] = MsgType::sign_out;
    request["user_id"] = USER_ID;
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "Sign out failed" << endl;
        free(packet);
        return false;
    }
    free(packet);
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
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "SendMsg failed" << endl;
        free(packet);
        return false;
    }
    free(packet);
    return true;
}

bool SendGroupMsg(int fd) {
    int group_id;
    char message[1024] = {0};
    cout << "Input group id please:";
    cin >> group_id;
    cin.get();
    cout << "Input message please:";
    cin.getline(message, 1024);
    bool in_group = false;
    int group_index = 0;
    for (int i = 0; i < GROUPS.size(); ++i) {
        if (GROUPS[i].GetGroupId() == group_id) {
            in_group = true;
            group_index = i;
            break;
        }
    }
    if (!in_group) {
        cout << group_id << " is not your group, please join in it first"
             << endl;
        return false;
    }

    json request;
    request["msg_type"] = MsgType::chat_send;
    request["user_id"] = USER_ID;

    request["msg"] = message;

    for (const auto &group_user : GROUPS[group_index].GetGroupUser()) {
        request["friend_id"] = group_user.GetUserId();
        if (!Send(fd, request))
            return false;
    }

    return true;
}

bool CreateGroup(int fd) {
    char group_name[60] = {0};
    char group_desc[500] = {0};
    cout << "Input group name please:";
    cin.get();
    cin.getline(group_name, 50);
    cout << "Input group desc please:";
    cin.getline(group_desc, 50);
    json request;
    request["msg_type"] = MsgType::create_group;
    request["user_id"] = USER_ID;
    request["group_name"] = string(group_name);
    request["group_desc"] = string(group_desc);
    return Send(fd, request);
}

bool QueryGroup(int fd) {
    json request;
    request["msg_type"] = MsgType::query_group;
    request["user_id"] = USER_ID;
    return Send(fd, request);
}
bool JoinInGroup(int fd) {
    int group_id;
    cout << "Input group id please:";
    cin >> group_id;
    json request;
    request["msg_type"] = MsgType::join_in_group;
    request["user_id"] = USER_ID;
    request["group_id"] = group_id;
    return Send(fd, request);
}

void RecvFromServer(int fd, bool *running) {
    while (*running) {
        char data_length_buf[4] = {0};
        while (true) {
            auto size = recv(fd, data_length_buf, 4, MSG_PEEK);
            if (size == 4) {
                recv(fd, data_length_buf, 4, 0);
                break;
            }
            if (size == -1)
                exit(-1);
        }
        int32_t be32 = *(int32_t *)(data_length_buf); // SIGBUS   //转化成32位
        const int32_t data_length =
            muduo::net::sockets::networkToHost32(be32); //转换成主机字节序
        char *data_buf = (char *)(malloc(data_length));
        memset(data_buf, 0, data_length);
        while (true) {
            auto size = recv(fd, data_buf, data_length, MSG_PEEK);
            if (size == data_length) {
                recv(fd, data_buf, data_length, 0);
                break;
            }
            if (size == -1) {
                cout << "Error occurs in function RecvFromServer" << endl;
                exit(-1);
            }
        }
        response = json::parse(data_buf);
        if (response.contains("msg_type") == false)
            continue;
        else if (response["msg_type"] == MsgType::sign_in_res ||
                 response["msg_type"] == MsgType::sign_up_res) {
            unique_lock<mutex> lock(MUTEX);
            CV.notify_one();
            continue;
        }
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

bool HandleAddFriendMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["user_id"] << endl;
        cout << response["friend_id"] << endl;
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    cout << response["friend_id"] << endl;
    cout << response["msg"] << endl;
    FRIENDS.emplace_back(stoi(response["friend_id"].dump()),
                         response["nickname"], "", response["state"]);
    return true;
}

bool HandleCreateGroupMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["group_id"] << endl;
    cout << response["msg"] << endl;
    /* FRIENDS.emplace_back(stoi(response["friend_id"].dump()),
                         response["nickname"], "", response["state"]); */
    return true;
}

bool HandleJoinGroupMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    Group group;
    group.SetGroupId(response["group_id"]);

    vector<string> group_users_string = response["group_user"];

    for (auto &group_user_string : group_users_string) {
        GroupUser group_user;
        json group_user_json = json::parse(group_user_string.c_str());
        group_user.SetUserId(group_user_json["user_id"]);
        // group_user.SetNickname(group_user_json["nickname"]);
        // group_user.SetRole(group_user_json["role"]);
        group.GetGroupUser().push_back(group_user);
    }
    GROUPS.push_back(group);
    return true;
}

bool HandleNewGroupUserMsg(const json &response) {
    GroupUser group_user;
    group_user.SetUserId(response["user_id"]);
    int group_id = response["group_id"];
    cout << group_user.GetUserId() << "加入群组" << group_id << endl;
    for (auto &group : GROUPS) {
        if (group.GetGroupId() == group_id) {
            group.GetGroupUser().push_back(group_user);
            return true;
        }
    }
    return false;
}
bool HandleQueryGroupMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["msg"] << endl;
    vector<string> groups_string = response["groups"];

    GROUPS.clear();
    for (auto &group_string : groups_string) {
        Group group;
        json group_json = json::parse(group_string.c_str());
        group.SetGroupId(group_json["group_id"]);
        group.SetGroupName(group_json["group_name"]);
        group.SetGroupDesc(group_json["group_desc"]);

        vector<string> group_users_string = group_json["group_user"];

        for (auto &group_user_string : group_users_string) {
            GroupUser group_user;
            json group_user_json = json::parse(group_user_string.c_str());
            group_user.SetUserId(group_user_json["user_id"]);
            group_user.SetNickname(group_user_json["nickname"]);
            group_user.SetRole(group_user_json["role"]);
            group.GetGroupUser().push_back(group_user);
        }
        GROUPS.push_back(group);
    }
    return true;
}
int Client(int client_fd) {
    while (true) {
        cout << "1 : Send message" << endl;
        cout << "2 : Sign out" << endl;
        cout << "3 : Add friend" << endl;
        cout << "4 : Show friends" << endl;
        cout << "5 : Create Group" << endl;
        cout << "6 : Join in Group" << endl;
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
            AddFriend(client_fd);
            break;
        case 4:
            ShowFriends();
            break;
        case 5:
            CreateGroup(client_fd);
            break;
        case 6:
            JoinInGroup(client_fd);
            break;
        case 7:
            SendGroupMsg(client_fd);
            break;
        case 8:
            QueryGroup(client_fd);
            break;
        default:
            break;
        }
    }
}

bool AddFriend(int fd) {
    int friend_id;
    cout << "Input friend id please:";
    cin >> friend_id;
    json request;
    request["msg_type"] = MsgType::add_friend;
    request["user_id"] = USER_ID;
    request["friend_id"] = friend_id;
    char *packet = GeneratePacket(request.dump());
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet, PacketLength(request.dump()), 0)) {
        cout << "Sign in failed" << endl;
        free(packet);
        return false;
    }
    free(packet);
    return true;
}

void InitHandlerMap() {
    handler_map_[MsgType::chat_send] = MsgHandler(&HandleChatMsg);
    handler_map_[MsgType::add_friend_res] = MsgHandler(&HandleAddFriendMsg);
    handler_map_[MsgType::create_group_res] = MsgHandler(&HandleCreateGroupMsg);
    handler_map_[MsgType::join_in_group_res] = MsgHandler(&HandleJoinGroupMsg);
    handler_map_[MsgType::query_group_res] = MsgHandler(&HandleQueryGroupMsg);
    handler_map_[MsgType::new_group_user] = MsgHandler(&HandleNewGroupUserMsg);
}

int main(int argc, char *argv[]) {
    /*  if (argc != 3) {
         cout << "server ip and port are needed" << endl;
         exit(0);
     } */
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    char ip[] = "127.0.0.1";
    char port[] = "6000";
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
    bool running = true;

    std::thread t(RecvFromServer, client_fd, &running);
    t.detach();

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
            { Client(client_fd); }
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