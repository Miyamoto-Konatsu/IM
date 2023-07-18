#include "server.h"
#include "kafka.h"
#include <csignal>

ServerTransfer::ServerTransfer() {
    newMsgConsumer = std::make_unique<NewMsgHandler>();
}

ServerTransfer::~ServerTransfer() {
    newMsgConsumer.reset();
}

void ServerTransfer::start() {
    running = 1;
    newMsgConsumer->start();
}

void ServerTransfer::loop() {
    while (running) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
}

void ServerTransfer::stop() {
    running = 0;
}

ServerTransfer serverTransfer;

static void stop(int sig) {
    serverTransfer.stop();
}

int main() {
    serverTransfer.start();
    //注册信号处理函数
    signal(SIGINT, stop);
    signal(SIGTERM, stop);
    serverTransfer.loop();
    return 0;
}