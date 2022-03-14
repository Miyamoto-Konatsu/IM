#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;

class Server {
  public:
    Server(EventLoop *, const InetAddress &, const string &);

    void start();

  private:
    void onConnection(const TcpConnectionPtr &conn); 

    void onMessage(const TcpConnectionPtr &conn, Buffer *buf,
                   Timestamp time); 

    EventLoop* loop_;
    TcpServer server_;
};

#endif