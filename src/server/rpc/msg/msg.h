#ifndef MSG_SERVER_H
#define MSG_SERVER_H

#include "msg.pb.h"
#include "msg.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <memory>

#include "producer.h"

using grpc::ServerContext;
using grpc::Status;
using ServerRpc::msg::sendMsgReq;
using ServerRpc::msg::sendMsgResp;
using ServerRpc::msg::Msg;
using ServerRpc::msg::msg;

class MsgServiceImpl : public Msg::Service {
public:
    Status sendMsg(ServerContext *context, const sendMsgReq *request,
                   sendMsgResp *response) override;
    MsgServiceImpl();

private:
    Status produce(const sendMsgReq *request);
    std::string getKey(const msg &request);
    std::unique_ptr<ProducerMQ> producer;
};

#endif