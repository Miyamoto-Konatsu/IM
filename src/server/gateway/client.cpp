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
    std::cout << type << std::endl;
    std::string resDataStr;
    json retData;
    switch (type) {
    case TCP_MSG_OP_TYPE_SEND_MSG: {
        retData = server_->getMsgHandler().sendMsg(data.dump());
        break;
    }
    default: break;
    }
    writeMsg(retData.dump());
}

void Client::pushMsg(const msg *msg) {
    pushMessage pushMsg;
    pullMsgs pullMsg;
    pullMsg.add_msgs()->CopyFrom(*msg);

    auto conversationId = getConversationId(*msg);
    auto p = std::make_pair(conversationId, pullMsg);
    pushMsg.mutable_msgs()->insert(p);
    static JsonPrintOptions options;
    options.always_print_primitive_fields = true;
    std::string msgStr;
    auto status = MessageToJsonString(pushMsg, &msgStr, options);
    if (!status.ok()) { LOG_DEBUG << "MessageToJsonString failed: "; }
    writeMsg(msgStr);
}

void Client::writeMsg(const std::string &msg) {
    server_->send(conn_.get(), msg);
}