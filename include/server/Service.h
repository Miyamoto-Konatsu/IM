#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include "MessageType.h"
#include "json.hpp"
#include "server/db/Redis.h"
#include "server/model/FriendModel.h"
#include "server/model/GroupModel.h"
#include "server/model/OfflineMessageModel.h"
#include "server/model/UserModel.h"
#include <functional>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <muduo/net/TimerQueue.h>
#include "TimerHeap.h"
//#include <muduo/base/.h>
#include "Common.h"
#include "server/msgidserver/MsgCommon.h"
#include "server/myserver/MyServer.h"
#include <unordered_map>
#include <unordered_set>
/* #include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>*/
#include <mutex>
using namespace std;
using namespace muduo;
using namespace muduo::net;

using MsgHandler =
    std::function<void(gp::Connection *, const nlohmann::json &)>;

const int RetryTimes = 2;
const int RetryInterval = 2;
using gp::Connection;

class Service {

  public:
    static Service *GetInstance();

    void Register(Connection *, const nlohmann::json &);
    void SignIn(Connection *, const nlohmann::json &);
    void SignOut(Connection *, const nlohmann::json &);
    /*转发消息，进行消息去重，并返回ack*/
    void Chat(Connection *, const nlohmann::json &);
    /* 消息成功转发到接受者，处理接受者返回的ack */
    void ChatRes(Connection *, const nlohmann::json &);
    void AddFriend(Connection *, const nlohmann::json &);

    void CreateGroup(Connection *, const nlohmann::json &);
    void JoinInGroup(Connection *, const nlohmann::json &);
    void ChatGroup(Connection *, const nlohmann::json &);
    void QueryGroup(Connection *, const nlohmann::json &);
    void HandleClientException(Connection *);

    MsgHandler GetHandler(MsgType);
    void SubscribeCallback(int, const string &);
    /*
        首先检测是否收到ack，收到则不重发
        未收到则重发，并延迟一段时间后再次检测ack
        @param msg  消息
        */
    void AddAckCheckTimer(const nlohmann::json &msg);
    

  private:
    Service();
    void StartTimer() {
        gp::EventLoop *loop = new gp::EventLoop;
        timer_queue_ = new gp::TimerHeap(loop);
        loop->Loop();
    }
    /*
    接受者在线时转发消息，并加入ack check timer。
    不在线是把消息插入数据库。
    @return true 接收者在线, false 接收者不在线
     */
    bool SendMsg(const nlohmann::json &);
    /*
    检查该信息是否接受到ack，check不成功要再发送，
    发送后继续加入ack check timer
    @param msg json 需要检查是否收到ack的信息
     */
    void AckCheck(const nlohmann::json &msg);

    mutex mtx_;
    unordered_map<MsgType, MsgHandler> handler_map_;
    unordered_map<int, Connection *> user_2_conn_;

    Redis redis_;
    UserModel user_model_;
    FriendModel friend_model_;
    OfflineMessageModel offline_message_model_;
    GroupModel group_model_;

    gp::TimerHeap *timer_queue_;
    mutex timer_queue_mutex_;

    unordered_map<UserIdType, unordered_set<MsgIdType>>
        message_recv_; //服务器接受到的消息
    mutex message_recv_mutex_;

    unordered_map<UserIdType, unordered_set<MsgIdType>>
        message_ack_; //服务器转发的消息，以收到ack
    mutex message_ack_mutex_;
};
#endif