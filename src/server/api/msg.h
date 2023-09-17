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
private:
    MsgClient msgClient_;
};