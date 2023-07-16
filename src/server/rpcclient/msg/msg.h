#ifndef MSG_CLIENT_H
#define MSG_CLIENT_H

#include "msg.grpc.pb.h"
#include "msg.pb.h"
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using ServerRpc::msg::sendMsgReq;
using ServerRpc::msg::sendMsgResp;
using ServerRpc::msg::Msg;

class MsgClient {
public:
    MsgClient(std::shared_ptr<grpc::Channel> channel) :
        stub_(Msg::NewStub(channel)) {
    }

    Status sendMsg(const sendMsgReq *request, sendMsgResp *response) {
        ClientContext context;
        return stub_->sendMsg(&context, *request, response);
    }

private:
    std::unique_ptr<Msg::Stub> stub_;
};
#endif // MSG_CLIENT_H