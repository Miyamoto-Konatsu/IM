#include "server/Service.h"
#include "Common.h"
#include "MessageType.h"
#include "server/msgidserver/MsgCommon.h"
#include "server/myserver/MyServer.h"
#include "sha256.hpp"
#include "unordered_map"
#include <string>
using namespace std;
/* using namespace muduo;
using namespace muduo::net; */
using namespace std::placeholders;
using gp::Connection;
void Send(Connection *conn, const nlohmann::json &response) {
    try {
        uint32_t packet_length;
        auto res = GeneratePacket(response.dump(), packet_length);
        if (res == nullptr)
            return;
        conn->Send(res, packet_length);
    } catch (const exception &e) {
        LOG_DEBUG << e.what();
    }
}

Service::Service() {
    redis_.SetSubscribeCallback(
        std::bind(&Service::SubscribeCallback, this, _1, _2));
    handler_map_[MsgType::sign_up] =
        std::bind(&Service::Register, this, _1, _2);
    handler_map_[MsgType::sign_in] = std::bind(&Service::SignIn, this, _1, _2);
    handler_map_[MsgType::sign_out] =
        std::bind(&Service::SignOut, this, _1, _2);
    handler_map_[MsgType::chat] = std::bind(&Service::Chat, this, _1, _2);
    handler_map_[MsgType::chat_res] =
        std::bind(&Service::ChatRes, this, _1, _2);
    handler_map_[MsgType::add_friend] =
        std::bind(&Service::AddFriend, this, _1, _2);
    handler_map_[MsgType::create_group] =
        std::bind(&Service::CreateGroup, this, _1, _2);
    handler_map_[MsgType::join_in_group] =
        std::bind(&Service::JoinInGroup, this, _1, _2);
    handler_map_[MsgType::query_group] =
        std::bind(&Service::QueryGroup, this, _1, _2);
    thread timer(&Service::StartTimer, this);
    timer.detach();
}

Service *Service::GetInstance() {
    static Service service;
    return &service;
}

MsgHandler Service::GetHandler(MsgType msg_type) {
    return handler_map_[msg_type];
}

void Service::Register(Connection *conn, const nlohmann::json &msg) {
    muduo::string nickname = msg["nickname"];
    muduo::string password = msg["password"];
    User new_user(nickname, EncryptPassword(password));
    bool insert_res = this->user_model_.Insert(new_user);

    nlohmann::json response;
    response["msg_type"] = MsgType::sign_up_res;

    if (insert_res) {
        response["user_id"] = new_user.GetUserId();
        Send(conn, response);
    } else {
        response["err_msg"] = "Register failed";
        Send(conn, response);
    }
}

void Service::SignIn(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"].get<int>();
    muduo::string password = msg["password"].get<string>();
    User user;
    bool query_res = this->user_model_.QueryUser(user_id, user);
    nlohmann::json response;
    response["msg_type"] = MsgType::sign_in_res;

    if (!query_res || !CheckPassword(password, user.GetPassword())) {
        response["err_msg"] = "Invalid user id or password is wrong";
        LOG_DEBUG << "Invalid user id or password is wrong";
        Send(conn, response);
        return;
    }

    {
        lock_guard<mutex> lock(mtx_);

        if (redis_.IsOnline(user.GetUserId())) {
            response["err_msg"] = "The user is online, sign in failed";
            LOG_DEBUG << "The user is online, sign in failed";
            Send(conn, response);
            return;
        }
    }

    // user.SetState("online");
    // this->user_model_.UpdateState(user);

    response["nickname"] = user.GetNickname();
    response["user_id"] = user.GetUserId();
    response["state"] = user.GetState();

    //获取朋友列表
    unique_ptr<vector<User>> friends =
        this->friend_model_.GetFriend(user.GetUserId());
    vector<string> friends_json;
    {
        lock_guard<mutex> lock(mtx_);
        for (const auto &my_friend : *friends) {
            nlohmann::json f;
            f["user_id"] = my_friend.GetUserId();
            f["nickname"] = my_friend.GetNickname();
            f["state"] =
                redis_.IsOnline(my_friend.GetUserId()) ? "online" : "offline";
            friends_json.push_back(f.dump());
        }
    }
    response["friends"] = friends_json;

    //获取历史消息
    unique_ptr<vector<string>> messages =
        this->offline_message_model_.Query(user.GetUserId());
    if (!messages->empty()) {
        response["offlinemsg"] = *messages;
        this->offline_message_model_.Delete(user.GetUserId());
    }

    LOG_DEBUG << user.GetNickname() << " sign in success";

    //保存用户的连接
    {
        lock_guard<mutex> lock(mtx_);
        user_2_conn_[user.GetUserId()] = conn;
        redis_.Subscribe(user.GetUserId());
        redis_.SignIn(user.GetUserId());
    }

    Send(conn, response);
}

void Service::SignOut(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"].get<int>();
    User user;
    bool query_res = this->user_model_.QueryUser(user_id, user);
    if (!query_res) {
        LOG_DEBUG << "Invalid user id ";
        return;
    }
    lock_guard<mutex> lock(mtx_);

    if (!redis_.IsOnline(user_id)) {
        LOG_DEBUG << "The account is offline, so nothing occurs";
        return;
    }

    redis_.SignOut(user.GetUserId());
    redis_.Unsubscribe(user.GetUserId());
    user_2_conn_.erase(user.GetUserId());

    /*
        user.SetState("offline");
        this->user_model_.UpdateState(user); */
}

void Service::AckCheck(const nlohmann::json &msg) {
    UserIdType user_id = msg["user_id"].get<UserIdType>();
    MsgIdType msg_id = msg["msg_id"].get<MsgIdType>();
    //未收到ack
    lock_guard<mutex> lock(message_ack_mutex_);
    if (message_ack_[user_id].find(msg_id) == message_ack_[user_id].end()) {
        SendMsg(msg);
        return;
    }
    //收到ack
    else {
        message_ack_[user_id].erase(msg_id);
        string message(msg["msg"]);
        LOG_DEBUG << "user_id:" << user_id << ", msg_content:" << message
                  << "  被成功接受。";
    }
}

void Service::ChatRes(Connection *conn, const nlohmann::json &msg) {
    UserIdType user_id = msg["user_id"].get<UserIdType>();
    MsgIdType msg_id = msg["msg_id"].get<MsgIdType>();
    lock_guard<mutex> lock_conn(mtx_);
    //消息发送者登录在本服务器
    if (user_2_conn_.find(user_id) != user_2_conn_.end()) {
        lock_guard<mutex> lock_msg(message_ack_mutex_);
        message_ack_[user_id].insert(msg_id);
    }
    //登录在其他服务器时，把ack转发过去
    else if (redis_.IsOnline(user_id)) {
        LOG_DEBUG << user_id << " online, but login in other server , send ack";
        redis_.Publish(user_id, msg.dump());
    }
}

void Service::AddAckCheckTimer(const nlohmann::json &msg) {
    lock_guard<mutex> lock(timer_queue_mutex_);
    gp::Timestamp timer = gp::Timestamp::Now().AddTime(RetryInterval);
    timer_queue_->AddTimer(bind(&Service::AckCheck, this, msg), timer);
}

bool Service::SendMsg(const nlohmann::json &msg) {
    lock_guard<mutex> lock(mtx_);
    UserIdType user_id = msg["user_id"].get<UserIdType>();
    UserIdType friend_id = msg["friend_id"].get<UserIdType>();
    LOG_DEBUG << user_id << " Send message to " << friend_id;
    //朋友在线
    if (user_2_conn_.find(friend_id) != user_2_conn_.end()) {
        LOG_DEBUG << friend_id << " online , Send message";
        Send(user_2_conn_[friend_id], msg);
        //AddAckCheckTimer(msg);
        return true;
    }
    //朋友在线,在别的服务器登录
    if (redis_.IsOnline(friend_id)) {
        LOG_DEBUG << friend_id
                  << " online, but login in other server , Send message";
        redis_.Publish(friend_id, msg.dump());
        //AddAckCheckTimer(msg);
        return true;
    }
    //不在线
    LOG_DEBUG << friend_id << " offline , Send message to database";

    this->offline_message_model_.Insert(friend_id, msg.dump());
    return false;
}

void Service::Chat(Connection *conn, const nlohmann::json &msg) {
    if (msg.contains("msg_id") == false)
        return;
    nlohmann::json response;
    response["msg_type"] = MsgType::chat_res;
    response["msg_id"] = msg["msg_id"].get<MsgIdType>();

    Send(conn, response); //给发送者ack

    UserIdType user_id = msg["user_id"].get<UserIdType>();
    MsgIdType msg_id = msg["msg_id"].get<MsgIdType>();
    {
        lock_guard<mutex> lock(message_recv_mutex_);
        if (message_recv_[user_id].find(msg_id) != message_recv_[user_id].end())
            return;
        message_recv_[user_id].insert(msg_id);
    }
    //接受者在线时则转发消息，检测ack
    //接受者不在线时，将消息存入数据库，不检测ack
    if (SendMsg(msg)) //转发
    {
        AddAckCheckTimer(msg);
    }
}

void Service::HandleClientException(Connection *conn) {

    User user;
    lock_guard<mutex> lock(mtx_);
    for (const auto &p : user_2_conn_) {
        if (p.second == conn) {
            user.SetUserId(p.first);
            redis_.SignOut(user.GetUserId());
            redis_.Unsubscribe(user.GetUserId());
            user_2_conn_.erase(user.GetUserId());
            
            // this->user_model_.UpdateState(user);
            LOG_DEBUG << p.first << " disconnected";
            break;
        }
    }
}

void Service::AddFriend(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"];
    int friend_id = msg["friend_id"];

    nlohmann::json response;
    response["msg_type"] = MsgType::add_friend_res;
    response["user_id"] = user_id;
    response["friend_id"] = friend_id;
    bool insert_res = this->friend_model_.Insert(user_id, friend_id);
    if (!insert_res) {
        LOG_DEBUG << user_id << " add " << friend_id << " failed";
        response["err_msg"] = "Add friend failed, please check friend_id. Or "
                              "you two are alreadly friends ";
        Send(conn, response);
        return;
    }
    User new_friend;
    this->user_model_.QueryUser(friend_id, new_friend);
    response["nickname"] = new_friend.GetNickname();
    {
        lock_guard<mutex> lock(mtx_);
        response["state"] = redis_.IsOnline(friend_id) ? "online" : "offline";
    }
    response["msg"] = "Friend added successfully";
    Send(conn, response);
}
//接受其他服务器转发的消息，并进行ack检查
void Service::SubscribeCallback(int user_id, const string &message) {
    nlohmann::json msg(nlohmann::json::parse(message));
    Connection *conn = nullptr;
    {
        lock_guard<mutex> lock(mtx_);
        auto iter = user_2_conn_.find(user_id);
        if (iter != user_2_conn_.end()) {
            conn = iter->second;
        }
    }
    MsgType msg_type = msg["msg_type"];
    switch (msg_type) {
    case MsgType::chat_res:
        ChatRes(conn, msg);
        break;
    case MsgType::chat:
        SendMsg(msg);
        break;
    default:
        break;
    }
}

void Service::CreateGroup(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"];
    string group_name = msg["group_name"];
    string group_desc = msg["group_desc"];
    Group group(group_name, group_desc);

    nlohmann::json response;
    response["msg_type"] = MsgType::create_group_res;

    bool insert_res = this->group_model_.InsertGroup(group);
    if (!insert_res) {
        LOG_DEBUG << user_id << " create group failed";
        response["err_msg"] =
            "Create group failed. Change the group name may work.";
        Send(conn, response);
        return;
    }
    insert_res = this->group_model_.InsertGroupUser(group.GetGroupId(), user_id,
                                                    "creator");
    if (!insert_res) {
        LOG_DEBUG << user_id << " create group failed";
        response["err_msg"] =
            "Create group failed. Change the group name may work";
        Send(conn, response);
        return;
    }
    response["group_id"] = group.GetGroupId();
    response["msg"] = "Create group successfully";
    Send(conn, response);
}

void Service::JoinInGroup(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"];
    int group_id = msg["group_id"];

    nlohmann::json response;
    response["msg_type"] = MsgType::join_in_group_res;
    response["group_id"] = group_id;
    bool insert_res = this->group_model_.InsertGroupUser(group_id, user_id);
    if (!insert_res) {
        LOG_DEBUG << user_id << " join in group failed";
        response["err_msg"] =
            "Join in group failed. Change the group id may work";
        Send(conn, response);
        return;
    }

    auto users_ptr = this->group_model_.QueryGroupUser(group_id);
    if (!users_ptr) {
        LOG_DEBUG << user_id << " join in group failed";
        response["err_msg"] =
            "Join in group failed. Changing the group id may work";
        Send(conn, response);
        return;
    }

    //告诉群里其他人新用户加入
    {
        lock_guard<mutex> lock(mtx_);
        //朋友在线
        nlohmann::json response;
        response["group_id"] = group_id;
        response["user_id"] = user_id;
        response["msg_type"] = MsgType::new_group_user;
        // id_role.first 是群友的id
        for (auto &id_role : *users_ptr) {
            if (user_2_conn_.find(id_role.first) != user_2_conn_.end()) {
                LOG_DEBUG << id_role.first << " online , Send message";
                Send(user_2_conn_[id_role.first], response);
            }
            //朋友在线,在别的服务器登录
            else if (redis_.IsOnline(id_role.first)) {
                LOG_DEBUG
                    << id_role.first
                    << " online, but login in other server , Send message";
                redis_.Publish(id_role.first, response.dump());
            }
        }
    }

    //把群成员返回给加入者
    vector<string> group_users_string;
    nlohmann::json group_user_json;
    for (const auto &id_role : *users_ptr) {
        group_user_json["user_id"] = id_role.first;
        // group_user_json["nickname"] = group_user.GetNickname();
        // group_user_json["role"] = group_user.GetRole();
        group_users_string.push_back(group_user_json.dump());
    }
    response["group_user"] = group_users_string;
    response["msg"] = "Join in group successfully";
    Send(conn, response);
}

void Service::QueryGroup(Connection *conn, const nlohmann::json &msg) {
    int user_id = msg["user_id"];

    nlohmann::json response;
    response["msg_type"] = MsgType::query_group_res;

    auto groups_ptr = this->group_model_.QueryGroup(user_id);
    if (!groups_ptr) {
        LOG_DEBUG << user_id << " query group failed";
        response["err_msg"] = "Query group failed";
        Send(conn, response);
        return;
    }
    response["msg"] = "Query group successfully";
    vector<string> groups_string;
    for (auto &group : *groups_ptr) {
        nlohmann::json group_json;
        group_json["group_id"] = group.GetGroupId();
        group_json["group_name"] = group.GetGroupName();
        group_json["group_desc"] = group.GetGroupDesc();

        nlohmann::json group_user_json;
        vector<string> group_users_string;
        for (const auto &group_user : group.GetGroupUser()) {
            group_user_json["user_id"] = group_user.GetUserId();
            group_user_json["nickname"] = group_user.GetNickname();
            group_user_json["role"] = group_user.GetRole();
            group_users_string.push_back(group_user_json.dump());
        }
        group_json["group_user"] = group_users_string;
        groups_string.push_back(group_json.dump());
    }
    response["groups"] = groups_string;
    Send(conn, response);
}
