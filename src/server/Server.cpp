#include "server/Server.h"
#include "Common.h"
#include "MessageType.h"
#include "json.hpp"
#include "server/Service.h"
#include <functional>
#include <iostream>
Server::Server(EventLoop *loop, const InetAddress &inet_addr,
               const string &name)
    : server_(loop, inet_addr, name), loop_(loop) {
    server_.setConnectionCallback(
        std::bind(&Server::onConnection, this, std::placeholders::_1));
    server_.setMessageCallback(
        std::bind(&Server::onMessage, this, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
}

void Server::start() { server_.start(); }

void Server::onConnection(const TcpConnectionPtr &conn) {
    if (conn->disconnected()) {
        LOG_DEBUG << conn->peerAddress().toIpPort() << " closed";
        Service::GetInstance()->HandleClientException(conn);
        conn->shutdown();
    }
}

void Server::onMessage(const TcpConnectionPtr &conn, Buffer *buf,
                       Timestamp time) {
    Service *service = Service::GetInstance();
    /* muduo::string msg(buf->retrieveAllAsString());
    try {
        nlohmann::json msg_json = nlohmann::json::parse(msg.c_str());
        MsgType msg_type = msg_json["msg_type"].get<MsgType>();
        MsgHandler handler = service->GetHandler(msg_type);
        handler(conn, msg_json, time);
    } catch (...) {
        LOG_ERROR << "数据包错误";
    }
 */
    while (buf->readableBytes() >= PACKET_HEADER_LENGTH) {
        // FIXME: use Buffer::peekInt32()
        const void *data = buf->peek(); //偷看一下readable的当前首地址
        int32_t be32 =
            *static_cast<const int32_t *>(data); // SIGBUS   //转化成32位
        const int32_t len =
            muduo::net::sockets::networkToHost32(be32); //转换成主机字节序
        if (len > MAX_DATA_LENGTH ||
            len < 0) //如果消息超过4K，或者长度小于0，不合法，干掉它。
        {
            LOG_ERROR << "Invalid length " << len;
            Service::GetInstance()->HandleClientException(conn);
            conn->shutdown(); 
            break;
        } else if (
            buf->readableBytes() >=
            len +
                PACKET_HEADER_LENGTH) //如果缓冲区可读的数据是否>=len+head，说明是一条完整的消息，取走
        {                             // len是头部规定的体部长度
            buf->retrieve(PACKET_HEADER_LENGTH); //取头部
            muduo::string msg(buf->peek(), len); //取包体
            //取出包体后就可以处理回调了 /* muduo::string
            nlohmann::json msg_json = nlohmann::json::parse(msg.c_str());
            MsgType msg_type = msg_json["msg_type"].get<MsgType>();
            MsgHandler handler = service->GetHandler(msg_type);
            handler(conn, msg_json, time);
            buf->retrieve(len); //然后把字节取走
        }

        else //未达到一条完整的消息
        {
            break;
        }
    }
}
