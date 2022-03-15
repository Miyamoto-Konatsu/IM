#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include "MessageType.h"
#include "json.hpp"
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
    MsgHandler GetHandler(MsgType);

  private:
    Service();
    unordered_map<MsgType, MsgHandler> handler_map_;

    UserModel user_model_;
};
#endif