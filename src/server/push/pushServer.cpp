
#include "consumerHandler.h"
#include "commonServer.h"
#include <csignal>

volatile int g_terminate = 0;
void stop(int sig) {
    g_terminate = 1;
}

int main() {
    CommonServer server(std::make_unique<ConsumerHandler>());

    server.run();
    signal(SIGINT, stop);
    signal(SIGTERM, stop);
    while (!g_terminate) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // 终止 server
    server.stop();
    return 0;
}
