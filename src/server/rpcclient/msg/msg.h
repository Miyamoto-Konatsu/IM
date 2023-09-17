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
using ServerRpc::msg::setHasReadSeqReq;
using ServerRpc::msg::setHasReadSeqResp;
using ServerRpc::msg::getHasReadSeqAndMaxSeqReq;
using ServerRpc::msg::getHasReadSeqAndMaxSeqResp;

class MsgClient {
public:
    MsgClient(std::shared_ptr<grpc::Channel> channel) :
        stub_(Msg::NewStub(channel)) {
    }

    Status sendMsg(const sendMsgReq *request, sendMsgResp *response) {
        ClientContext context;
        return stub_->sendMsg(&context, *request, response);
    }

    Status syncMsgs(const ServerRpc::msg::syncMsgsReq *request,
                    ServerRpc::msg::syncMsgsResp *response) {
        ClientContext context;
        return stub_->syncMsgs(&context,* request, response);
    }

    Status setHasReadSeq(const setHasReadSeqReq *request,
                         setHasReadSeqResp *response) {
        ClientContext context;
        return stub_->setHasReadSeq(&context, *request, response);
    }

    Status getHasReadSeqAndMaxSeq(const getHasReadSeqAndMaxSeqReq *request,
                                  getHasReadSeqAndMaxSeqResp *response) {
        ClientContext context;
        return stub_->getHasReadSeqAndMaxSeq(&context, *request, response);
    }
    static MsgClient getMsgClient() {
        return MsgClient(grpc::CreateChannel(
            "localhost:50053", grpc::InsecureChannelCredentials()));
    }


private:
    std::unique_ptr<Msg::Stub> stub_;
};
#endif // MSG_CLIENT_H