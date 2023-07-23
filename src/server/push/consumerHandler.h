#ifndef CONSUMER_HANDLER_H
#define CONSUMER_HANDLER_H
#include "pusher.h"
#include "consumer.h"
#include <memory>
#include "msgHandler.h"
class ConsumerHandler : public MsgHandler {
public:
    ConsumerHandler();
    ~ConsumerHandler();
    ConsumerHandler(const ConsumerHandler &) = delete;
    ConsumerHandler &operator=(const ConsumerHandler &) = delete;

    void run() override;

private:
    void stop() override;
    void pushMsg(ConsumerMQ::MsgVector &&msgs);

private:
    Pusher pusher;
    std::unique_ptr<ConsumerMQ> consumer;
};
#endif