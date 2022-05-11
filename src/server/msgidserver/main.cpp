#include "server/msgidserver/Server.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please input port you chosen!\n");
        exit(-1);
    }
    EventLoop *loop = new EventLoop;
    InetAddress inet_addr("127.0.0.1", atoi(argv[1]));
    MsgIdServer server(loop, inet_addr, "MsgIdServer");
    server.Start();
    loop->loop();
    return 0;
}