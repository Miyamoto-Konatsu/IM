#include "user.h"
#include "cache/common.h"
#include "table/user.h"
#include <grpcpp/support/status.h>
using grpc::Server;
using grpc::ServerBuilder;

Status UserServiceImpl::getUser(::grpc::ServerContext *context,
                                const ::ServerRpc::user::getUserReq *request,
                                ::ServerRpc::user::getUserResp *response) {
    try {
        auto user = userDatabase_->getUser(request->userid());
        auto userRpc = response->mutable_user();
        copyField(*userRpc, user);
        return Status::OK;
    } catch (const std::exception &e) {
        return Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
}

Status
UserServiceImpl::createUser(::grpc::ServerContext *context,
                            const ::ServerRpc::user::createUserReq *request,
                            ::ServerRpc::user::createUserResp *response) {
    auto userRpc = request->user();
    auto result = userDatabase_->createUser(userRpc);
    response->set_issuccess(result);
    return Status::OK;
}

Status
UserServiceImpl::checkUser(::grpc::ServerContext *context,
                           const ::ServerRpc::user::checkUserReq *request,
                           ::ServerRpc::user::checkUserResp *response) {
    auto userId = request->userid();
    auto password = request->password();
    auto result = userDatabase_->checkUser(userId, password);
    response->set_issuccess(result);
    return Status::OK;
}

int main() {
    std::string server_address("0.0.0.0:50055");
    UserServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}