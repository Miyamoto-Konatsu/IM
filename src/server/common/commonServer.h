#ifndef COMMONSERVER_COMMON_H
#define COMMONSERVER_COMMON_H
#include "msgHandler.h"
#include <memory>

class CommonServer {
public:
    CommonServer(std::unique_ptr<MsgHandler> handler);
    virtual ~CommonServer();
    CommonServer(const CommonServer &) = delete;
    CommonServer &operator=(const CommonServer &) = delete;
    void run();
    void loop();
    static void stop();

private:
    volatile static int running;
    std::unique_ptr<MsgHandler> msgHandler;
};
#endif