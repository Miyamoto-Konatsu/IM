#include "Common.h"
#include <muduo/net/TimerQueue.h>
#include <server/msgidserver/MsgCommon.h>
using namespace muduo::net;

class MsgTimer {
  public:
    MsgTimer() {}
    /*
    服务器转发消息后需要检测是否收到ack，
    此函数加入ack检测timer。
    @param msg_id  MsgIdType
    @param sender_id  UserIdType
    */
    void AddAckCheckTimer(MsgIdType, UserIdType);
    /*
    检查
    @param msg_id  MsgIdType
    @param sender_id  UserIdType
    */
    void AddResendTimer(MsgIdType, UserIdType);

  private:
    TimerQueue timer_queue_;
};