#pragma once
#include "consumer.h"
#include "msgHandler.h"
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include "mutex"
#include "condition_variable"
#include "msg/msg.h"
#include "controller/chatlogDatabase.h"
#include "table/chatlog.h"

class ToMysqlHandler : public MsgHandler {
public:
    ToMysqlHandler();
    ~ToMysqlHandler();

    ToMysqlHandler(const ToMysqlHandler &) = delete;
    ToMysqlHandler &operator=(const ToMysqlHandler &) = delete;

    void run() override;

private:
    void persistMsg(ConsumerMQ::MsgVector &&msgs);
    void stop() override;
    std::unique_ptr<ConsumerMQ> newMsgConsumer;
    ChatLogController chatLogController;
};