#ifndef API2RPC_API_H
#define API2RPC_API_H
#include <httplib.h>
#include <functional>
#include <grpcpp/grpcpp.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/message.h>
#include <grpcpp/support/status.h>
#include "conversation.pb.h"
#include "auth.pb.h"
#include "json.hpp"
#include "msg.pb.h"
#include "protobuf/json/json.h"
#include "constant/msg.h"

using HttpRequest = httplib::Request;
using HttpResponse = httplib::Response;
using grpc::Status;
using google::protobuf::util::MessageToJsonString;
using google::protobuf::util::JsonStringToMessage;

template <typename T1, typename T2>
void api2rpc(std::function<Status(const T1 *, T2 *)> rpcFunc,
             const HttpRequest &reqHttp, HttpResponse &respHttp) {
    T1 request;
    T2 response;
    std::string jsonStr = reqHttp.body;
    auto convertStatus = JsonStringToMessage(jsonStr, &request);
    if (!convertStatus.ok()) {
        respHttp.status = 400;
        respHttp.set_content("invalid parameter", "text/plain");
        return;
    }
    Status status = rpcFunc(&request, &response);
    if (status.ok()) {
        std::string responseStr;
        google::protobuf::json::PrintOptions option;
        option.always_print_primitive_fields = true;
        MessageToJsonString(response, &responseStr, option);
        nlohmann::json res;
        res["code"] = MSG_CODE_SUCCESS;
        res["data"] = responseStr;
        respHttp.set_content(res.dump(), "application/json");
    } else {
        nlohmann::json res;
        res["code"] = MSG_CODE_ERROR;
        res["error_message"] = status.error_message();
        respHttp.set_content(status.error_message(), "application/json");
    }
}

#endif