
#include "consumerHandler.h"
#include "commonServer.h"
#include <csignal>

CommonServer server(std::make_unique<ConsumerHandler>());

void stop(int sig) {
    server.stop();
}

int main() {
    server.run();
    signal(SIGINT, stop);
    signal(SIGTERM, stop);
    server.loop();
    return 0;
}
