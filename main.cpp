#include "server/Server.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please input port you chosen!\n");
        exit(-1);
    }
    EventLoop *loop = new EventLoop;
    InetAddress inet_addr("127.0.0.1", atoi(argv[1]));
    Server server(loop, inet_addr, "Server");
    server.start();
    
    loop->loop();
    return 0;
}