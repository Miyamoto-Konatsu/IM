#ifndef PUSHSERVER_PUSH_H
#define PUSHSERVER_PUSH_H
#include <iostream>
#include <memory>
#include "protobuf/message.h"
#include "utils/commonUtils.h"
#include "msg.pb.h"
using ServerRpc::msg::msg;

class Pusher {
public:
    Pusher();
    ~Pusher();
    Pusher(const Pusher &) = delete;
    Pusher &operator=(const Pusher &) = delete;

    bool pushMsg2User(const msg &msg);

    bool pushMsg2Group(const msg &msg);
};
#endif