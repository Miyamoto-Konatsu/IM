#include "auth.h"
#include "auth.pb.h"

int main() {
    AuthClient authClient(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));

    userTokenResp userTokenResp;
    userTokenReq userTokenReq;
    userTokenReq.set_userid(std::string("userid"));
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
    return 0;
}