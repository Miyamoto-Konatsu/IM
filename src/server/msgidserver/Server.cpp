#include "server/msgidserver/Server.h"
#include "Common.h"
#include "MessageType.h"
#include "json.hpp"
#include "server/msgidserver/Service.h"
#include <muduo/base/Logging.h>
using nlohmann::json;

MsgIdServer::MsgIdServer(EventLoop *loop, const InetAddress &listenAddr,
                         const string &nameArg = "msg_id_server")
    : server_(loop, listenAddr, nameArg), loop_(loop) {
    server_.setMessageCallback(
        std::bind(&MsgIdServer::OnMessage, this, _1, _2, _3));
}

void MsgIdServer::Start() { server_.start(); }

void MsgIdServer::OnMessage(const TcpConnectionPtr &conn, Buffer *buf,
                            Timestamp time_stamp) {
    MsgIdService *service = MsgIdService::GetInstance();
    while (buf->readableBytes() >= PACKET_HEADER_LENGTH) {
        // FIXME: use Buffer::peekInt32()
        const void *data = buf->peek(); //偷看一下readable的当前首地址
        int32_t be32 =
            *static_cast<const int32_t *>(data); // SIGBUS   //转化成32位
        const int32_t len = be32;
        //  muduo::net::sockets::networkToHost32(be32); //转换成主机字节序
        if (len > MAX_DATA_LENGTH ||
            len < 0) //如果消息超过64K，或者长度小于0，不合法，干掉它。
        {
            LOG_ERROR << "Invalid length " << len; // do nothing
            /*   Service::GetInstance()->HandleClientException(conn);
              conn->shutdown(); // FIXME: disable reading */
            break;
        } else if (
            buf->readableBytes() >=
            len +
                PACKET_HEADER_LENGTH) //如果缓冲区可读的数据是否>=len+head，说明是一条完整的消息，取走
        {                             // len是头部规定的体部长度
            buf->retrieve(PACKET_HEADER_LENGTH);           //取头部
            muduo::string msg_encrypted(buf->peek(), len); //取包体
            muduo::string msg(DecryptPacket(move(msg_encrypted)));
            buf->retrieve(len); //然后把字节取走
            //取出包体后就可以处理回调了 /* muduo::string
            try {
                nlohmann::json msg_json = nlohmann::json::parse(msg.c_str());
                MsgType msg_type = msg_json["msg_type"].get<MsgType>();
                MsgHandler handler = service->GetHandler(msg_type);
                handler(conn,msg_json); //处理
            } catch (const nlohmann::json::parse_error e) {
                LOG_ERROR << e.what();
            } catch (const std::invalid_argument &e) {
                LOG_ERROR << e.what();
            } catch (const nlohmann::json::other_error &e) {
                LOG_ERROR << e.what();
            } catch (...) {
                LOG_ERROR << "Unknown error";
            }

        }

        else //未达到一条完整的消息
        {
            break;
        }
    }
}