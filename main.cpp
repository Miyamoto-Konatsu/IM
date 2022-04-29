#include "server/Server.h"
#include "server/myserver/MyServer.h"
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please input port you chosen!\n");
        exit(-1);
    }

    Server server;
    server.start();
    return 0;
}