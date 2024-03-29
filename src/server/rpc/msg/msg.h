#ifndef MSG_SERVER_H
#define MSG_SERVER_H

#include "msg.pb.h"
#include "msg.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <memory>
#include "controller/chatlogDatabase.h"
#include "producer.h"
#include "controller/msgDatabase.h"

using grpc::ServerContext;
using grpc::Status;
using ServerRpc::msg::sendMsgReq;
using ServerRpc::msg::sendMsgResp;
using ServerRpc::msg::Msg;
using ServerRpc::msg::msg;
using ServerRpc::msg::syncMsgsReq;
using ServerRpc::msg::syncMsgsResp;
using ServerRpc::msg::setHasReadSeqReq;
using ServerRpc::msg::setHasReadSeqResp;
using ServerRpc::msg::getHasReadSeqAndMaxSeqReq;
using ServerRpc::msg::getHasReadSeqAndMaxSeqResp;

class MsgServiceImpl : public Msg::Service {
public:
    Status sendMsg(ServerContext *context, const sendMsgReq *request,
                   sendMsgResp *response) override;
    Status syncMsgs(ServerContext *context, const syncMsgsReq *request,
                    syncMsgsResp *response) override;

    Status setHasReadSeq(ServerContext *context,
                         const setHasReadSeqReq *request,
                         setHasReadSeqResp *response) override;

    Status
    getHasReadSeqAndMaxSeq(ServerContext *context,
                           const getHasReadSeqAndMaxSeqReq *request,
                           getHasReadSeqAndMaxSeqResp *response) override;


    MsgServiceImpl();

private:
    Status produce(const sendMsgReq *request);
    std::string getKey(const msg &request);
    std::unique_ptr<ProducerMQ> producer;
    std::shared_ptr<ChatLogController> chatLogDatabase;
    std::shared_ptr<MsgDatabase> msgDatabase;
};

#endif