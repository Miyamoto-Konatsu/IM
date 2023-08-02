#include "msg/msg.h"
#include "gateMsghandler.h"
#include <grpcpp/channel.h>
#include "google/protobuf/util/json_util.h"
#include <muduo/base/Logging.h>
#include "constant/msg.h"
using MsgData = ServerRpc::msg::msg;
using google::protobuf::util::JsonParseOptions;
using google::protobuf::util::JsonStringToMessage;
using google::protobuf::util::MessageToJsonString;

GateMsgHandler::GateMsgHandler() : msgClient_(MsgClient::getMsgClient()) {
}

json GateMsgHandler::sendMsg(const std::string &msg) {
    LOG_DEBUG << msg;

    MsgData *data = new MsgData();
    json retData;
    auto parseStatus = google::protobuf::util::JsonStringToMessage(msg, data);
    if (!parseStatus.ok()) {
        retData["code"] = TCP_MSG_CODE_ERROR;
        retData["error_message"] = "invalid data format";
        LOG_ERROR << "failed to parse json data to protobuf,"
                  << " json data: " << msg;
        return retData;
    }

    if (data->msgtype() == TCP_MSG_SINGLE_CHAT_TYPE) {
        LOG_DEBUG << "fromuserid: " << data->fromuserid()
                  << " touserid: " << data->touserid()
                  << " content: " << data->content() << " msgtype: "
                  << "single chat";
    } else {
        LOG_DEBUG << "fromuserid: " << data->fromuserid()
                  << "groupid: " << data->groupid()
                  << " content: " << data->content() << " msgtype: "
                  << "group chat";
    }

    sendMsgReq req;
    sendMsgResp resp;
    req.set_allocated_msg_data(data);

    auto rpcStatus = msgClient_.sendMsg(&req, &resp);
    if (!rpcStatus.ok()) {
        retData["code"] = TCP_MSG_CODE_ERROR;
        retData["error_message"] = rpcStatus.error_message();
        LOG_ERROR << "rpc error:" << rpcStatus.error_message();
        return retData;
    }

    retData["code"] = TCP_MSG_CODE_SUCCESS;
    std::string rpcDataStr;
    parseStatus = MessageToJsonString(resp, &rpcDataStr);
    if (!parseStatus.ok()) {
        retData["code"] = TCP_MSG_CODE_ERROR;
        retData["error_message"] = "internal error";
        LOG_ERROR << "rpc succeeded , but failed parse protobuf data to json";
        return retData;
    }
    retData["data"] = rpcDataStr;
    return retData;
}