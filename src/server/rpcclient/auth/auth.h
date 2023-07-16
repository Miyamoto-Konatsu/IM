#ifndef AUTH_CLIENT_H
#define AUTH_CLIENT_H
#include "auth.grpc.pb.h"
#include "auth.pb.h"
#include "grpcpp/grpcpp.h"
#include <grpcpp/client_context.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using ServerRpc::auth::parseTokenResp;
using ServerRpc::auth::parseTokenReq;
using ServerRpc::auth::userTokenReq;
using ServerRpc::auth::userTokenResp;

class AuthClient {
public:
    AuthClient(std::shared_ptr<grpc::Channel> channel) :
        stub_(ServerRpc::auth::Auth::NewStub(channel)) {
    }

    Status parseToken(const parseTokenReq *request, parseTokenResp *response) {
        ClientContext context;
        return stub_->parseToken(&context, *request, response);
    }

    Status userToken(const userTokenReq *request, userTokenResp *response) {
        ClientContext context;
        return stub_->userToken(&context, *request, response);
    }

private:
    std::unique_ptr<ServerRpc::auth::Auth::Stub> stub_;
};

#endif