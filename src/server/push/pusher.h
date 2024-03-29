#ifndef PUSHSERVER_PUSH_H
#define PUSHSERVER_PUSH_H
#include <iostream>
#include <memory>
#include "utils/commonUtils.h"
#include "msg.pb.h"
#include "gateway/gateway.h"
#include "localcache/groupLocal.h"

using ServerRpc::msg::msg;

class Pusher {
public:
    Pusher();
    ~Pusher();
    Pusher(const Pusher &) = delete;
    Pusher &operator=(const Pusher &) = delete;

    bool pushMsg2User(const msg &msg);

    bool pushMsg2Group(const msg &msg);

    void getConnsAndOnlinePush(const std::vector<std::string> &userIds,
                               const msg &msg);

private:
    GatewayClient gatewayClient_;
    GroupLocalCache groupLocalCache_;
};
#endif