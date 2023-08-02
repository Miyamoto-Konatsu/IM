#include "client.h"

#include "json.hpp"
#include <string>
#include <string>
#include <iostream>
#include "constant/msg.h"
#include "server.h"
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
    server_->send(conn_.get(), retData.dump());
}
