#ifndef NEWMSGHANDLER_TRANSFER_H
#define NEWMSGHANDLER_TRANSFER_H

#include "consumer.h"
#include "msgHandler.h"
#include <mutex>
#include <thread>
#include <vector>
#include "mutex"
#include "condition_variable"

class NewMsgHandler : public MsgHandler {
public:
    NewMsgHandler();
    ~NewMsgHandler();
    NewMsgHandler(const NewMsgHandler &) = delete;
    NewMsgHandler &operator=(const NewMsgHandler &) = delete;
    void start() override;

private:
    void stop() override;
    void handleNewMsg(ConsumerMQ::MsgVector &&msgs);
    void msgDistribute(ConsumerMQ::MsgVector &&msgs);
    void msgHandler(int index);

private:
    int volatile running = 0;
    std::unique_ptr<ConsumerMQ> newMsgConsumer;
    std::vector<std::thread> msgHandlerThreads;
    std::vector<Channel<ConsumerMQ::MsgVector>> channels;
};

#endif // NEWMSGHANDLER_TRANSFER_H