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
#include "json.hpp"
int main() {
    nlohmann::json j;
    //   string secret = 1;
    // int32 platformID = 2;
    // string userID = 3;
    // string password = 4;
    j["secret"] = "www";
    j["platformID"] = 1;
    j["userID"] = "wwdddw";
    j["password"] = "wdfsdfww";
    std::cout << j.dump() << std::endl;
}