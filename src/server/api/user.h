#ifndef USER_API_H
#define USER_API_H

#include "api2rpc.h"
#include "user.pb.h"
#include "user/user.h"
#include <functional>
#include <grpcpp/support/status.h>
#include <memory>
#include "apiserver.h"

class UserApi : public std::enable_shared_from_this<UserApi> {
public:
    UserApi() : userClient_(UserClient::getUserClient()) {
    }

    ~UserApi() {
        std::cout << "UserApi destructor" << std::endl;
    }

    void createUser(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::user::createUserReq, ServerRpc::user::createUserResp>(
            std::bind(&UserClient::createUser, &userClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void getUser(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::user::getUserReq, ServerRpc::user::getUserResp>(
            std::bind(&UserClient::getUser, &userClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void checkUser(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::user::checkUserReq, ServerRpc::user::checkUserResp>(
            std::bind(&UserClient::checkUser, &userClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

private:
    UserClient userClient_;
};

#endif