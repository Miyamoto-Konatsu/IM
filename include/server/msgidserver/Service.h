#ifndef MSGIDSERVICE_H
#define MSGIDSERVICE_H

#include "Common.h"
#include "MessageType.h"
#include <functional>
#include <muduo/net/TcpConnection.h>
#include <mutex>
#include <server/msgidserver/Redis.h>
#include <unordered_map>
using namespace std;
using namespace std::placeholders;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

using MsgHandler = std::function<int(json &js)>;

class MsgIdService {
  public:
    static MsgIdService *GetInstance();

    //根据消息类型获取响应的处理函数
    MsgHandler GetHandler(MsgType);

  private:
    MsgIdService();
    int GetMsgId(json &);
    DISABLE_COPY_AND_MOVE(MsgIdService);

    unordered_map<MsgType, MsgHandler> handler_map_;
    mutex redis_mutex_;
    Redis redis_;
};

#endif