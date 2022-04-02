#include "server/Service.h"
#include "Common.h"
#include "MessageType.h"
#include "unordered_map"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

Service::Service() {
    redis_.SetSubscribeCallback(
        std::bind(&Service::SubscribeCallback, this, _1, _2));
    handler_map_[MsgType::sign_up] =
        std::bind(&Service::Register, this, _1, _2, _3);
    handler_map_[MsgType::sign_in] =
        std::bind(&Service::SignIn, this, _1, _2, _3);
    handler_map_[MsgType::sign_out] =
        std::bind(&Service::SignOut, this, _1, _2, _3);
    handler_map_[MsgType::chat_send] =
        std::bind(&Service::Chat, this, _1, _2, _3);
    handler_map_[MsgType::add_friend] =
        std::bind(&Service::AddFriend, this, _1, _2, _3);
    handler_map_[MsgType::create_group] =
        std::bind(&Service::CreateGroup, this, _1, _2, _3);
    handler_map_[MsgType::join_in_group] =
        std::bind(&Service::JoinInGroup, this, _1, _2, _3);
    handler_map_[MsgType::query_group] =
        std::bind(&Service::QueryGroup, this, _1, _2, _3);
}

Service *Service::GetInstance() {
    static Service service;
    return &service;
}

MsgHandler Service::GetHandler(MsgType msg_type) {
    return handler_map_[msg_type];
}

void Service::Register(const TcpConnectionPtr &conn, const nlohmann::json &msg,
                       Timestamp time) {
    muduo::string nickname = msg["nickname"];
    muduo::string password = msg["password"];
    User new_user(nickname, password);
    bool insert_res = this->user_model_.Insert(new_user);

    nlohmann::json response;
    response["msg_type"] = MsgType::sign_up_res;

    if (insert_res) {
        response["user_id"] = new_user.GetUserId();
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
    } else {
        response["err_msg"] = "Register failed";
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
    }
}

void Service::SignIn(const TcpConnectionPtr &conn, const nlohmann::json &msg,
                     Timestamp time) {
    int user_id = msg["user_id"].get<int>();
    muduo::string password = msg["password"].get<string>();
    User user;
    bool query_res = this->user_model_.QueryUser(user_id, user);
    nlohmann::json response;
    response["msg_type"] = MsgType::sign_in_res;

    if (!query_res || user.GetPassword() != password) {
        response["err_msg"] = "Invalid user id or password is wrong";
        LOG_DEBUG << "Invalid user id or password is wrong";
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
        return;
    }

    {
        lock_guard<mutex> lock(mtx_);

        if (redis_.IsOnline(user.GetUserId())) {
            response["err_msg"] = "The user is online, sign in failed";
            LOG_DEBUG << "The user is online, sign in failed";
            conn->send(GeneratePacket(response.dump()),
                       PacketLength(response.dump()));
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

    conn->send(GeneratePacket(response.dump()), PacketLength(response.dump()));
}

void Service::SignOut(const TcpConnectionPtr &conn, const nlohmann::json &msg,
                      Timestamp time) {
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

void Service::Chat(const TcpConnectionPtr &conn, const nlohmann::json &msg,
                   Timestamp time) {
    int user_id = msg["user_id"].get<int>();
    int friend_id = msg["friend_id"].get<int>();
    LOG_DEBUG << user_id << " send message to " << friend_id;

    lock_guard<mutex> lock(mtx_);
    //朋友在线
    if (user_2_conn_.find(friend_id) != user_2_conn_.end()) {
        LOG_DEBUG << friend_id << " online , send message";
        user_2_conn_[friend_id]->send(GeneratePacket(msg.dump()),
                                      PacketLength(msg.dump()));
        return;
    }
    //朋友在线,在别的服务器登录
    if (redis_.IsOnline(friend_id)) {
        LOG_DEBUG << friend_id
                  << " online, but login in other server , send message";
        redis_.Publish(friend_id, msg.dump());
        return;
    }
    //不在线
    LOG_DEBUG << friend_id << " offline , send message to database";

    this->offline_message_model_.Insert(friend_id, msg.dump());
    // this->user_model_.UpdateState(user);
}

void Service::HandleClientException(const TcpConnectionPtr &conn) {

    User user;
    lock_guard<mutex> lock(mtx_);
    for (const auto &p : user_2_conn_) {
        if (p.second.get() == conn.get()) {
            user.SetUserId(p.first);
            redis_.SignOut(user.GetUserId());
            redis_.Unsubscribe(user.GetUserId());
            user_2_conn_.erase(user.GetUserId());
            // this->user_model_.UpdateState(user);
            break;
        }
    }
}

void Service::AddFriend(const TcpConnectionPtr &conn, const nlohmann::json &msg,
                        Timestamp time) {
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
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
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
    conn->send(GeneratePacket(response.dump()), PacketLength(response.dump()));
}

void Service::SubscribeCallback(int user_id, const string &message) {
    lock_guard<mutex> lock(mtx_);
    if (user_2_conn_.find(user_id) != user_2_conn_.end()) {
        user_2_conn_[user_id]->send(GeneratePacket(message),
                                    PacketLength(message));
        return;
    }
    this->offline_message_model_.Insert(user_id, message);
}

void Service::CreateGroup(const TcpConnectionPtr &conn,
                          const nlohmann::json &msg, Timestamp time) {
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
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
        return;
    }
    insert_res = this->group_model_.InsertGroupUser(group.GetGroupId(), user_id,
                                                    "creator");
    if (!insert_res) {
        LOG_DEBUG << user_id << " create group failed";
        response["err_msg"] =
            "Create group failed. Change the group name may work";
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
        return;
    }
    response["group_id"] = group.GetGroupId();
    response["msg"] = "Create group successfully";
    conn->send(GeneratePacket(response.dump()), PacketLength(response.dump()));
}

void Service::JoinInGroup(const TcpConnectionPtr &conn,
                          const nlohmann::json &msg, Timestamp time) {
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
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
        return;
    }

    auto users_ptr = this->group_model_.QueryGroupUser(group_id);
    if (!users_ptr) {
        LOG_DEBUG << user_id << " join in group failed";
        response["err_msg"] =
            "Join in group failed. Change the group id may work";
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
        return;
    }

    //告诉群里其他人新用户加入
    {
        lock_guard<mutex> lock(mtx_);
        //朋友在线
        nlohmann::json new_group_user;
        new_group_user["group_id"] = group_id;
        new_group_user["user_id"] = user_id;
        new_group_user["msg_type"] = MsgType::new_group_user;
        // id_role.first 是群友的id
        for (auto &id_role : *users_ptr) {
            if (user_2_conn_.find(id_role.first) != user_2_conn_.end()) {
                LOG_DEBUG << id_role.first << " online , send message";
                user_2_conn_[id_role.first]->send(
                    GeneratePacket(new_group_user.dump()),
                    PacketLength(new_group_user.dump()));
            }
            //朋友在线,在别的服务器登录
            else if (redis_.IsOnline(id_role.first)) {
                LOG_DEBUG
                    << id_role.first
                    << " online, but login in other server , send message";
                redis_.Publish(id_role.first, new_group_user.dump());
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
    conn->send(GeneratePacket(response.dump()), PacketLength(response.dump()));
}

void Service::QueryGroup(const TcpConnectionPtr &conn,
                         const nlohmann::json &msg, Timestamp time) {
    int user_id = msg["user_id"];

    nlohmann::json response;
    response["msg_type"] = MsgType::query_group_res;

    auto groups_ptr = this->group_model_.QueryGroup(user_id);
    if (!groups_ptr) {
        LOG_DEBUG << user_id << " query group failed";
        response["err_msg"] = "Query group failed";
        conn->send(GeneratePacket(response.dump()),
                   PacketLength(response.dump()));
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
    conn->send(GeneratePacket(response.dump()), PacketLength(response.dump()));
}