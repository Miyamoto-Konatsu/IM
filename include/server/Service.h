#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include "json.hpp"
#include <functional>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

#include "server/model/UserModel.h"

using namespace std;
using namespace muduo;
using namespace muduo::net;

class Service {
    using MsgHandler = std::function<void(const TcpConnectionPtr &,
                                          const nlohmann::json &, Timestamp)>;

  public:
    void Register(const TcpConnectionPtr &, const nlohmann::json &, Timestamp);

  private:
    UserModel user_model_;
};
#endif