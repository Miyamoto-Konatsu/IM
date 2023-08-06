#ifndef USER_RPCCLIENT_H
#define USER_RPCCLIENT_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include "user.grpc.pb.h"
#include "user.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using UserRpc = ServerRpc::user::user;
using UserRpcService = ServerRpc::user::User;
using ServerRpc::user::createUserReq;
using ServerRpc::user::createUserResp;
using ServerRpc::user::getUserReq;
using ServerRpc::user::getUserResp;
using ServerRpc::user::checkUserReq;
using ServerRpc::user::checkUserResp;

class UserClient {
public:
    UserClient(std::shared_ptr<grpc::Channel> channel) :
        stub_(UserRpcService::NewStub(channel)) {
    }

    Status createUser(const createUserReq *request, createUserResp *response) {
        ClientContext context;
        return stub_->createUser(&context, *request, response);
    }

    Status getUser(const getUserReq *request, getUserResp *response) {
        ClientContext context;
        return stub_->getUser(&context, *request, response);
    }

    Status checkUser(const checkUserReq *request, checkUserResp *response) {
        ClientContext context;
        return stub_->checkUser(&context, *request, response);
    }

    static UserClient getUserClient() {
        return UserClient(grpc::CreateChannel(
            "0.0.0.0:50055", grpc::InsecureChannelCredentials()));
    }
private:
    std::unique_ptr<UserRpcService::Stub> stub_;
};
#endif