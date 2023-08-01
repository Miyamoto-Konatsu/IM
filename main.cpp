// #include "server/Server.h"
// #include "server/myserver/MyServer.h"
// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         printf("Please input port you chosen!\n");
//         exit(-1);
//     }

//     Server server("127.0.0.1", argv[1]);
//     server.start();
//     return 0;
// }
#include <iostream>
#include <thread>
void f() {
    std::thread t([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "hello" << std::endl;
    });
    t.detach();
    std::cout << "f end" << std::endl;
}
int main() {
    //   string secret = 1;
    // int32 platformID = 2;
    // string userID = 3;
    // string password = 4;
    f();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "world" << std::endl;
    return 0;
}