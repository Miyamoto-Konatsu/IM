#ifndef SERVER_TRANSFER_H
#define SERVER_TRANSFER_H

#include <functional>
#include "consumer.h"
#include "msgHandler.h"
#include "newMsgHandler.h"
class ServerTransfer {
public:
    ServerTransfer();

    ServerTransfer(const ServerTransfer &) = delete;
    ServerTransfer &operator=(const ServerTransfer &) = delete;
    ~ServerTransfer();
    void start();
    void loop();
    void stop();

private:
private:
    volatile int running = 0;
    std::unique_ptr<MsgHandler> newMsgConsumer;
};
#endif // SERVER_TRANSFER_H