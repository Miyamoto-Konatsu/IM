#pragma once

#include "msg.pb.h"
#include "msg/msg.h"
#include "api2rpc.h"

class MsgApi : public std::enable_shared_from_this<MsgApi> {
public:
    MsgApi(): msgClient_(MsgClient::getMsgClient()) {
    }

    ~MsgApi() = default;

    void syncMsgs(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::msg::syncMsgsReq, ServerRpc::msg::syncMsgsResp>(
            std::bind(&MsgClient::syncMsgs, &msgClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void sendMsg(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::msg::sendMsgReq, ServerRpc::msg::sendMsgResp>(
            std::bind(&MsgClient::sendMsg, &msgClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void setHasReadSeq(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::msg::setHasReadSeqReq, ServerRpc::msg::setHasReadSeqResp>(
            std::bind(&MsgClient::setHasReadSeq, &msgClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void getHasReadSeqAndMaxSeq(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::msg::getHasReadSeqAndMaxSeqReq, ServerRpc::msg::getHasReadSeqAndMaxSeqResp>(
            std::bind(&MsgClient::getHasReadSeqAndMaxSeq, &msgClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }
private:
    MsgClient msgClient_;
};