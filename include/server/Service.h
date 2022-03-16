#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include "MessageType.h"
#include "json.hpp"
#include "server/model/FriendModel.h"
#include "server/model/UserModel.h"
#include <functional>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

using namespace std;
using namespace muduo;
using namespace muduo::net;

using MsgHandler = std::function<void(const TcpConnectionPtr &,
                                      const nlohmann::json &, Timestamp)>;

class Service {

  public:
    static Service *GetInstance();

    void Register(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);
    void SignIn(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);
    void SignOut(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);
    void Chat(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);
    void AddFriend(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);

    void HandleClientException(const TcpConnectionPtr &);

    MsgHandler GetHandler(MsgType);

  private:
    Service();
    
    unordered_map<MsgType, MsgHandler> handler_map_;
    unordered_map<int, TcpConnectionPtr> user_2_conn_;

    UserModel user_model_;
    FriendModel friend_model_;
};
#endif