#ifndef MSG_SERVER_H
#define MSG_SERVER_H

#include "msg.pb.h"
#include "msg.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>

#include "producer.h"

using grpc::ServerContext;
using grpc::Status;
using ServerRpc::msg::sendMsgReq;
using ServerRpc::msg::sendMsgResp;
using ServerRpc::msg::Msg;

class MsgServiceImpl : public Msg::Service {
public:
    Status sendMsg(ServerContext *context, const sendMsgReq *request,
                   sendMsgResp *response) override;

private:
    Status produce();
    ProducerMQ producer;
};

#endif