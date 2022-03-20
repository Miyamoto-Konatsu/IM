#include "server/Service.h"
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
        conn->send(response.dump());
    } else {
        response["err_msg"] = "Register failed";
        conn->send(response.dump());
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
        conn->send(response.dump());
        return;
    }

    {
        lock_guard<mutex> lock(mtx_);

        if (redis_.IsOnline(user.GetUserId())) {
            response["err_msg"] = "The user is online, sign in failed";
            LOG_DEBUG << "The user is online, sign in failed";
            conn->send(response.dump());
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

    conn->send(response.dump());
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
        user_2_conn_[friend_id]->send(msg.dump());
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
        conn->send(response.dump());
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
    conn->send(response.dump());
}

void Service::SubscribeCallback(int user_id, const string &message) {
    lock_guard<mutex> lock(mtx_);
    if (user_2_conn_.find(user_id) != user_2_conn_.end()) {
        user_2_conn_[user_id]->send(message);
        return;
    }
    this->offline_message_model_.Insert(user_id, message);
}