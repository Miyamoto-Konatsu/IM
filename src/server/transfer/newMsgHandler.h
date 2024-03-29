#ifndef NEWMSGHANDLER_TRANSFER_H
#define NEWMSGHANDLER_TRANSFER_H

#include "consumer.h"
#include "msgHandler.h"
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include "mutex"
#include "condition_variable"
#include "controller/msgDatabase.h"
#include "producer.h"
#include "conversation/conversation.h"

class NewMsgHandler : public MsgHandler {
public:
    NewMsgHandler();
    ~NewMsgHandler();
    NewMsgHandler(const NewMsgHandler &) = delete;
    NewMsgHandler &operator=(const NewMsgHandler &) = delete;
    void run() override;

private:
    void stop() override;
    void handleNewMsg(ConsumerMQ::MsgVector &&msgs);
    void msgDistribute(ConsumerMQ::MsgVector &&msgs);
    void msgHandler(int index);
    void msgToPush(const std::string key,
                   const std::vector<sendMsgReq> &msgReqs);

private:
    std::unique_ptr<ConsumerMQ> newMsgConsumer;
    std::vector<std::thread> msgHandlerThreads;
    std::vector<BlockChannel<ConsumerMQ::MsgVector>> channels;
    MsgDatabase msgDatabase;

    std::unique_ptr<ProducerMQ> msgToPushProducer;

    ConversationClient conversationClient;

};

#endif // NEWMSGHANDLER_TRANSFER_H