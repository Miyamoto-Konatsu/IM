#include "server/Service.h"
#include "MessageType.h"
#include "unordered_map"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;
Service::Service() {
    handler_map_[MsgType::sign_up] =
        std::bind(&Service::Register, this, _1, _2, _3);
    handler_map_[MsgType::sign_in] =
        std::bind(&Service::SignIn, this, _1, _2, _3);
    handler_map_[MsgType::sign_out] =
        std::bind(&Service::SignOut, this, _1, _2, _3);
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

    if (insert_res) {
        response["msg_type"] = MsgType::sign_up_res;
        response["user_id"] = new_user.GetUserId();
        conn->send(response.dump());
    } else {
        response["err_msg"] = "Register failed";
        response["msg_type"] = MsgType::sign_up_res;
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
    if (!query_res || user.GetPassword() != password) {
        response["err_msg"] = "Invalid user id or password is wrong";
        LOG_DEBUG << "Invalid user id or password is wrong";
        response["msg_type"] = MsgType::sign_in_res;
        conn->send(response.dump());
    }

    if (user.GetState() == string("online")) {
        response["err_msg"] = "The user is online, sign in failed";
        LOG_DEBUG << "The user is online, sign in failed";

        response["msg_type"] = MsgType::sign_in_res;
        conn->send(response.dump());
    }

    //登录成功
    user.SetState("online");
    this->user_model_.UpdateState(user);

    response["nickname"] = user.GetNickname();
    response["user_id"] = user.GetUserId();
    response["state"] = user.GetState();

    //获取朋友列表
    /*  vector<User> friends = this->friend_model_.GetFriend(user.GetUserId());
     vector<string> friends_json;
     for (const auto &my_friend : friends) {
         nlohmann::json f;
         f["user_id"] = my_friend.GetUserId();
         f["nickname"] = my_friend.GetNickname();
         f["state"] = my_friend.GetState();
         friends_json.push_back(f.dump());
     }
     response["friends"] = friends_json; */
    LOG_DEBUG << user.GetNickname() << " sign in success";
    conn->send(response.dump());
    //获取历史消息
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
    if (user.GetState() == "offline") {
        LOG_DEBUG << "The account is offline, so nothing occurs";
        return;
    }
    user.SetState("offline");
    this->user_model_.UpdateState(user);
}