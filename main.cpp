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
#include <muduo/base/Logging.h>
void f() {
    std::thread t([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "hello" << std::endl;
    });
    t.detach();
    std::cout << "f end" << std::endl;
}

template <typename T, int n>
struct Pointer {
    using type = typename Pointer<T, n - 1>::type *;
};

template <typename T>
struct Pointer<T, 0> {
    using type = T;
};

// template <typename T>
// void fun(T t) {
//     std::cout << T << std::endl;
//     std::cout << t << std::endl;
// }
int main() {
}