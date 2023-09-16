#include "commonServer.h"
#include <memory>
#include <thread>

volatile int CommonServer::running = 0;

CommonServer::CommonServer(std::unique_ptr<MsgHandler> handler) :
    msgHandler(std::move(handler)) {
}

CommonServer::~CommonServer() {
}

void CommonServer::run() {
    running = 1;
    msgHandler->run();
}

void CommonServer::loop() {
    while (running) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
}

// stop之后不能再run
void CommonServer::stop() {
    running = 0;
}
