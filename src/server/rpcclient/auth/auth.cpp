#include "auth.h"
#include "auth.pb.h"
#include <thread>

int main() {
    AuthClient authClient(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));

    userTokenResp userTokenResp;
    userTokenReq userTokenReq;
    userTokenReq.set_userid(std::string("77443343"));
    userTokenReq.set_password(std::string("password"));
    userTokenReq.set_platformid(1);
    userTokenReq.set_secret(std::string("1234567"));

    auto status = authClient.userToken(&userTokenReq, &userTokenResp);
    if (!status.ok()) {
        std::cout << "userToken rpc failed." << std::endl;
        return -1;
    }
    std::cout << "userTokenResp: " << userTokenResp.token() << std::endl;
    std::cout << "userTokenResp: " << userTokenResp.expiretimeseconds()
              << std::endl;

    parseTokenResp parseTokenResp;
    parseTokenReq parseTokenReq;
    parseTokenReq.set_token(userTokenResp.token());
    std::this_thread::sleep_for(std::chrono::seconds(3));
    status = authClient.parseToken(&parseTokenReq, &parseTokenResp);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        std::cout << "parseToken rpc failed." << std::endl;
        return -1;
    }
    std::cout << "parseTokenResp: " << parseTokenResp.userid() << std::endl;
    std::cout << "parseTokenResp: " << parseTokenResp.platformid() << std::endl;
    std::cout << "parseTokenResp: " << parseTokenResp.expiretimeseconds()
              << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));
    status = authClient.parseToken(&parseTokenReq, &parseTokenResp);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        std::cout << "parseToken rpc failed." << std::endl;
        return -1;
    }
    std::cout << "parseTokenResp: " << parseTokenResp.userid() << std::endl;
    std::cout << "parseTokenResp: " << parseTokenResp.platformid() << std::endl;
    std::cout << "parseTokenResp: " << parseTokenResp.expiretimeseconds()
              << std::endl;
    return 0;
}