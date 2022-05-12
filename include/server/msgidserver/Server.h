#ifndef MSGIDSERVER_H
#define MSGIDSERVER_H

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;
//会送消息id的服务器
class MsgIdServer {
  public:
    MsgIdServer(EventLoop *loop, const InetAddress &listenAddr,
               const string &nameArg);

    void Start();

  private:
    void OnMessage(const TcpConnectionPtr &, Buffer *, Timestamp);

    TcpServer server_; 
    EventLoop *loop_;  
};

#endif
