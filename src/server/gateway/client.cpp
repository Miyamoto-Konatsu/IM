#include "client.h"

#include "json.hpp"
#include <string>
#include <string>
#include <iostream>
#include <utility>
#include "constant/msg.h"
#include "msg.pb.h"
#include "server.h"
#include "gateway.pb.h"
#include <google/protobuf/util/json_util.h>
#include "utils/msgutils.h"
using google::protobuf::util::JsonPrintOptions;
using google::protobuf::util::MessageToJsonString;
using ServerRpc::gateway::pushMessage;
using ServerRpc::msg::pullMsgs;
using nlohmann::json;

void Client::handlerMsg(const std::string &msg) {
    json msgData = json::parse(msg);
    if (!msgData.contains("type")) return;
    if (!msgData.contains("data")) return;
    json data = msgData["data"];

    int type = msgData["type"];
    std::string resDataStr;
    json retData;
    switch (type) {
    case TCP_MSG_OP_TYPE_SEND_MSG: {
        retData["type"] = TCP_MSG_OP_TYPE_SEND_MSG_REPLY;
        retData["data"] = server_->getMsgHandler().sendMsg(data.dump());
        break;
    }
    default: break;
    }
    writeMsg(retData.dump());
}

void Client::pushMsg(const msg *msg) {
    // pushMessage pushMsg;
    pullMsgs pullMsg;
    pullMsg.add_msgs()->CopyFrom(*msg);

    // auto conversationId = getConversationId(*msg);
    // auto p = std::make_pair(conversationId, pullMsg);
    // pushMsg.mutable_msgs()->insert(p);
    static JsonPrintOptions options;
    options.always_print_primitive_fields = true;
    std::string msgStr;
    auto status = MessageToJsonString(pullMsg, &msgStr, options);
    if (!status.ok()) { LOG_DEBUG << "MessageToJsonString failed: "; }
    json retData;
    retData["type"] = TCP_MSG_OP_TYPE_PUSH_MSG;
    retData["data"] = msgStr;
    writeMsg(retData.dump());
}

void Client::writeMsg(const std::string &msg) {
    server_->send(conn_.get(), msg);
}

void Client::kickUser() {
    json retData;
    retData["type"] = TCP_MSG_OP_KICK_USER;
    retData["data"] = "kick user";
    writeMsg(retData.dump());
    server_->getClientMap().erase(conn_);
    conn_->shutdown();
}