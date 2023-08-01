#ifndef AUTH_API_H
#define AUTH_API_H

#include "api2rpc.h"
#include "auth.pb.h"
#include "auth/auth.h"
#include <functional>
#include <grpcpp/support/status.h>
#include <memory>
#include "apiserver.h"

class AuthApi : public std::enable_shared_from_this<AuthApi> {
public:
    AuthApi() :
        authClient_(grpc::CreateChannel("localhost:50052",
                                        grpc::InsecureChannelCredentials())) {
    }

    ~AuthApi() {
        std::cout << "AuthApi destructor" << std::endl;
    }

    void userToken(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::auth::userTokenReq, ServerRpc::auth::userTokenResp>(
            std::bind(&AuthClient::userToken, &authClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void parseToken(const HttpRequest &req, HttpResponse &resp) {
        // api2rpc<ServerRpc::auth::parseTokenReq,
        //         ServerRpc::auth::parseTokenResp>(
        //     std::bind(&AuthClient::parseToken, &authClient_,
        //               std::placeholders::_1, std::placeholders::_2),
        //     req, resp);
    }

    Status parseToken(const ServerRpc::auth::parseTokenReq &req,
                      ServerRpc::auth::parseTokenResp &resp) {
        auto status = authClient_.parseToken(&req, &resp);
        return status;
    }

private:
    AuthClient authClient_;
};

#endif