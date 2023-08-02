#ifndef MSGHASNDLER_GATEWAY_H
#define MSGHASNDLER_GATEWAY_H
#include <memory>
#include "msg/msg.h"
#include "json.hpp"
using nlohmann::json;
class GateMsgHandler {
public:
    GateMsgHandler();

    GateMsgHandler(const GateMsgHandler &) = delete;

    GateMsgHandler &operator=(const GateMsgHandler &) = delete;

    ~GateMsgHandler() = default;

    json sendMsg(const std::string &msg);

private:
    MsgClient msgClient_;
};

#endif