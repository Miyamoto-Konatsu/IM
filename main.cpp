#include "Server.h"

int main() {
    EventLoop *loop = new EventLoop;
    InetAddress inet_addr("127.0.0.1", 8899);
    Server server(loop, inet_addr, "Server");
    server.start();
    loop->loop();
    return 0;
}