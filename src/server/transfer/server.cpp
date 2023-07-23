
#include "commonServer.h"
#include "kafka.h"
#include "msgHandler.h"
#include "newMsgHandler.h"
#include <csignal>

CommonServer
    serverTransfer(std::make_unique<NewMsgHandler>());

static void stop(int sig) {
    serverTransfer.stop();
}

int main() {
    serverTransfer.run();
    //注册信号处理函数
    signal(SIGINT, stop);
    signal(SIGTERM, stop);
    serverTransfer.loop();
    return 0;
}