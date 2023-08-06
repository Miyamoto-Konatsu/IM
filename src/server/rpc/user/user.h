#ifndef USER_RPC_H
#define USER_RPC_H
#include "grpcpp/server.h"
#include "user.grpc.pb.h"
#include "user.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <iostream>
#include <memory>
#include <string>

#include "controller/userDatabase.h"

using grpc::Status;


class UserServiceImpl : public ServerRpc::user::User::Service {
public:
    UserServiceImpl() :
        userDatabase_(std::make_shared<UserDatabase>()) {
    }
    Status getUser(::grpc::ServerContext *context,
                   const ::ServerRpc::user::getUserReq *request,
                   ::ServerRpc::user::getUserResp *response) override;

    Status createUser(::grpc::ServerContext *context,
                      const ::ServerRpc::user::createUserReq *request,
                      ::ServerRpc::user::createUserResp *response) override;

    Status checkUser(::grpc::ServerContext *context,
                     const ::ServerRpc::user::checkUserReq *request,
                     ::ServerRpc::user::checkUserResp *response) override;
private:
    std::shared_ptr<UserDatabase> userDatabase_;
};
#endif