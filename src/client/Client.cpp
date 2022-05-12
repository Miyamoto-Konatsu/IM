#include "Common.h"
#include "MessageType.h"
#include "aes128.hpp"
#include "json.hpp"
#include "server/model/Group.h"
#include "server/model/User.h"
#include "server/msgidserver/MsgCommon.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <condition_variable>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/Socket.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/TimerQueue.h>
#include <mutex>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#define MsgIdServerPort 6008
#define RetryTimes 3
#define RetryInterval 3
#define ACKCheckInterval 3
typedef int UserIdType;
using namespace std;
using json = nlohmann::json;
using namespace muduo::net;
using namespace muduo;

TimerQueue *timer_queue;
mutex timer_queue_mutex;

condition_variable CV;
mutex MUTEX;
json response;
int USER_ID = -1;
vector<User> FRIENDS;
vector<Group> GROUPS;
unordered_map<MsgIdType, json>
    MESSAGE_SENT; //成功发送出去的消息，不一定被服务器接受
unordered_set<MsgIdType> MESSAGE_SUCCESS; //收到ack的消息
mutex MESSAGE_SENT_MUTEX;                 //保护MESSAGE_SENT的互斥量
mutex MESSAGE_SUCCESS_MUTEX;              //保护MESSAGE_SUCCESS的互斥量
unordered_map<UserIdType, unordered_set<MsgIdType>> MESSAGE_RECVED;
mutex MESSAGE_RECVED_MUTEX;
int client_fd;
using MsgHandler = function<bool(const json &)>;

unordered_map<MsgType, MsgHandler> handler_map_;

class ConnectionError : public exception {
  public:
    ConnectionError(const char *msg) : msg(msg) {}
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT {
        return msg;
    }

  private:
    const char *msg;
};

bool HandleChatMsg(const json &response);
bool HandleChatResMsg(const json &response);
void ShowFriends();
bool QueryGroup(int);
bool AddFriend(int fd);

/*
   return true 代表发送成功，但不一定被成功接收
   return false 代表 error
*/
bool Send(int fd, json &request) {
    uint32_t packet_length;
    auto packet = GeneratePacket(request.dump(), packet_length);
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet.get(), packet_length, 0)) {
        LOG_DEBUG << "send failed";
        return false;
    }
    return true;
}
/*
检查是否收到ack，request里有
*/
void CheckMsgAck(json request) {
    lock_guard<mutex> lock2(MESSAGE_SUCCESS_MUTEX);
    if (MESSAGE_SUCCESS.find(request["msg_id"].get<MsgIdType>()) ==
        MESSAGE_SUCCESS.end()) {
        MsgIdType msg_id = request["friend_id"].get<MsgIdType>();
        string msg = request["msg"];
        LOG_DEBUG << "Message to " << msg_id
                  << " failed. Message content: " << msg;
    }
}

//返回接受到的各种消息
json Recv(int fd) {
    char data_length_buf[PACKET_HEADER_LENGTH] = {0};
    while (true) {
        auto size = recv(fd, data_length_buf, PACKET_HEADER_LENGTH, MSG_PEEK);
        if (size == PACKET_HEADER_LENGTH) {
            recv(fd, data_length_buf, PACKET_HEADER_LENGTH, 0);
            break;
        }
        if (size == 0) {
            throw ConnectionError("msg id server disconnected");
        }
        if (size == -1 && errno != EAGAIN) {
            throw ConnectionError("msg id server connetction error");
        }
    }
    int32_t data_length = *(int32_t *)(data_length_buf); // SIGBUS //转化成32位
    /*  const int32_t data_length =
         muduo::net::sockets::networkToHost32(be32);  *///转换成主机字节序
    char *data_buf = (char *)(malloc(data_length));
    memset(data_buf, 0, data_length);
    while (true) {
        auto size = recv(fd, data_buf, data_length, MSG_PEEK);
        if (size == data_length) {
            recv(fd, data_buf, data_length, 0);
            break;
        }
        if (size == 0) {
            throw ConnectionError("msg id server disconnected");
        }
        if (size == -1 && errno != EAGAIN) {
            throw ConnectionError("msg id server connetction error");
        }
    }

    string encrypt(data_length + 1, '\000');
    memcpy(&encrypt[0], data_buf, data_length);
    free(data_buf);
    auto s = DecryptPacket(move(encrypt));
    response = json::parse(s);
    return response;
}

/*
尝试发送消息，发送失败则会加入时间队列，等待下次发送。
发送失败次数过多，会停止发送，并提示发送。
发送成功后，等待一段时间之后会检查是否收到消息ACK，没收到会提示发送失败；
收到ack则表示成功发送到服务器。
*/
void TrySend(int fd, json request, int retry_times) {
    if (retry_times <= 0) {
        cout << "message to" << request["friend_id"]
             << "failed. Message content: ";
        cout << request["msg"] << endl;
        return;
    }
    lock_guard<mutex> lock(timer_queue_mutex);
    if (Send(fd, request) == false) {
        Timestamp now = Timestamp::now();
        timer_queue->addTimer(std::bind(&TrySend, fd, request, retry_times - 1),
                              addTime(now, ACKCheckInterval), 0);
    } else { //发送成功后，等待一段时间之后会检查是否收到消息ACK，没收到会提示发送失败，收到
        Timestamp now = Timestamp::now();
        timer_queue->addTimer(std::bind(&CheckMsgAck, request),
                              addTime(now, ACKCheckInterval), 0);
    }
}

class MsgIdGetter {
  public:
    static MsgIdGetter *GetInstance();
    /*获取msgid时网络出现问题会尝试重新建立连接
      获取成功时返回消息id
      获取失败时返回-1
    */
    int GetMsgId(int user_id) {
        json request;
        request["user_id"] = user_id;
        request["msg_type"] = MsgType::get_msg_id;
        int retry_times = RetryTimes;
        while (retry_times--) {
            if (!Send(msg_id_server_fd, request)) {
                close(msg_id_server_fd);
                Connect();
                continue;
            }
            try {
                auto response = Recv(msg_id_server_fd);
                return response["msg_id"].get<MsgIdType>() > 0
                           ? response["msg_id"].get<MsgIdType>()
                           : -1;
            } catch (const ConnectionError &e) {
                LOG_DEBUG << e.what();
                Connect();
                continue;
            } catch (const json::parse_error &e) {
                LOG_DEBUG << e.what();
                continue;
            } catch (...) {
                throw;
            }
        }
        return -1;
    }

  private:
    MsgIdGetter() { Connect(); }

    void Connect() {
        char ip[] = "127.0.0.1";
        sockaddr_in sa;
        memset(&sa, 0, sizeof(sa));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(MsgIdServerPort);
        sa.sin_addr.s_addr = inet_addr(ip);
        int retry_times = RetryTimes;
        while (retry_times--) {
            msg_id_server_fd = socket(AF_INET, SOCK_STREAM, 0);

            if (connect(msg_id_server_fd, (struct sockaddr *)&sa,
                        sizeof(struct sockaddr))) {
                LOG_DEBUG << "connect failed, retry.";
                sleep(RetryInterval);
            } else {
                LOG_DEBUG << "Successfully connected to the message id server.";
                return;
            }
        }
        LOG_DEBUG << "connect failed!";
        exit(0);
    }
    DISABLE_COPY_AND_MOVE(MsgIdGetter);

    int msg_id_server_fd = -1;
};

MsgIdGetter *MsgIdGetter::GetInstance() {
    static MsgIdGetter getter;
    return &getter;
}

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
    uint32_t packet_length;
    auto packet = GeneratePacket(request.dump(), packet_length);
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet.get(), packet_length, 0)) {
        cout << "Register failed" << endl;

        return false;
    }

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
    uint32_t packet_length;
    auto packet = GeneratePacket(request.dump(), packet_length);
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet.get(), packet_length, 0)) {
        cout << "Sign in failed" << endl;
        return false;
    }

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
    uint32_t packet_length;
    auto packet = GeneratePacket(request.dump(), packet_length);
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet.get(), packet_length, 0)) {
        cout << "Sign out failed" << endl;
        return false;
    }
    cout << "Sign out success" << endl;

    //登出后重置
    USER_ID = -1;
    FRIENDS.clear();
    return true;
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
    MsgIdGetter *msg_Id_getter = MsgIdGetter::GetInstance();
    int msg_id = msg_Id_getter->GetMsgId(USER_ID);
    if (msg_id == -1) {
        LOG_INFO << message << "send error";
        return false;
    }
    json request;
    request["msg_type"] = MsgType::chat;
    request["user_id"] = USER_ID;
    request["friend_id"] = friend_id;
    request["msg"] = message;
    request["msg_id"] = msg_id;
    TrySend(fd, request, RetryTimes);

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
    request["msg_type"] = MsgType::chat;
    request["user_id"] = USER_ID;

    request["msg"] = message;

    for (const auto &group_user : GROUPS[group_index].GetGroupUser()) {
        request["friend_id"] = group_user.GetUserId();
        MsgIdGetter *msg_Id_getter = MsgIdGetter::GetInstance();
        int msg_id = msg_Id_getter->GetMsgId(USER_ID);
        if (msg_id == -1) {
            LOG_INFO << message << "send error";
            return false;
        }
        request["msg_id"] = msg_id;
        TrySend(client_fd, request, RetryTimes);
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
        json response = Recv(fd);
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
/*
显示接受到的消息
将消息id加入MESSAGE_RECV，对消息进行去重
*/
bool HandleChatMsg(const json &response) {
    UserIdType user_id = response["user_id"].get<UserIdType>();
    ;
    MsgIdType msg_id = response["msg_id"].get<MsgIdType>();
    json response_ack;
    {
        response_ack["user_id"] = user_id;
        response_ack["friend_id"] = response["friend_id"].get<UserIdType>();
        response_ack["msg_id"] = msg_id;
        response_ack["msg_type"] = MsgType::chat_res;

        lock_guard<mutex> lock(MESSAGE_RECVED_MUTEX);
        if (MESSAGE_RECVED[user_id].find(msg_id) !=
            MESSAGE_RECVED[user_id].end()) {
            LOG_DEBUG << "Recv duplicate message from " << user_id;
            Send(client_fd, response_ack);
            return false;
        }
        MESSAGE_RECVED[user_id].insert(msg_id);
        Send(client_fd, response_ack);
    }

    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    cout << response["user_id"] << endl;
    cout << response["friend_id"] << endl;
    cout << response["msg"] << endl;

    return true;
}

/*
  处理消息发送成功后接受到的ack
  将消息id加入MESSAGE_SUCCESS
*/

bool HandleChatResMsg(const json &response) {
    if (response.contains("err_msg")) {
        cout << response["err_msg"] << endl;
        return false;
    }
    if (!response.contains("msg_id")) {
        return false;
    }
    lock_guard<mutex> lock(MESSAGE_SUCCESS_MUTEX);
    MESSAGE_SUCCESS.insert(response["msg_id"].get<MsgIdType>());
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
        cout << "7 : Send group message" << endl;
        cout << "8 : Query group" << endl;
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
    uint32_t packet_length;
    auto packet = GeneratePacket(request.dump(), packet_length);
    if (nullptr == packet)
        return false;
    if (-1 == send(fd, packet.get(), packet_length, 0)) {
        cout << "Sign in failed" << endl;
        return false;
    }
    return true;
}

void InitHandlerMap() {
    handler_map_[MsgType::chat] = MsgHandler(&HandleChatMsg);
    handler_map_[MsgType::chat_res] = MsgHandler(&HandleChatResMsg);
    handler_map_[MsgType::add_friend_res] = MsgHandler(&HandleAddFriendMsg);
    handler_map_[MsgType::create_group_res] = MsgHandler(&HandleCreateGroupMsg);
    handler_map_[MsgType::join_in_group_res] = MsgHandler(&HandleJoinGroupMsg);
    handler_map_[MsgType::query_group_res] = MsgHandler(&HandleQueryGroupMsg);
    handler_map_[MsgType::new_group_user] = MsgHandler(&HandleNewGroupUserMsg);
}
void loop_func() {
    EventLoop *loop = new EventLoop;
    timer_queue = new TimerQueue(loop);
    loop->loop();
}

int main(int argc, char *argv[]) {
    /*  if (argc != 3) {
         cout << "server ip and port are needed" << endl;
         exit(0);
     } */
    Logger::setLogLevel(Logger::LogLevel::DEBUG);
    thread loop_thread(&loop_func);
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    char ip[] = "127.0.0.1";
    char *port = argv[1];
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