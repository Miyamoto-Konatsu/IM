
#include "commonServer.h"
#include "kafka.h"
#include "msgHandler.h"
#include "toMysqlHandler.h"
#include <csignal>


static void stop(int sig) {
    CommonServer::stop();
}

int main() {
    CommonServer serverTransfer(std::make_unique<ToMysqlHandler>());

    serverTransfer.run();
    //注册信号处理函数
    signal(SIGINT, stop);
    signal(SIGTERM, stop);
    serverTransfer.loop();
    return 0;
}