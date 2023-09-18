#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include "auth.grpc.pb.h"
#include "auth.pb.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server.h>
#include "cache/auth.h"
#include "user/user.h"

using grpc::ServerContext;
using grpc::Status;

using ServerRpc::auth::parseTokenResp;
using ServerRpc::auth::parseTokenReq;
using ServerRpc::auth::userTokenReq;
using ServerRpc::auth::userTokenResp;

using ServerRpc::auth::Auth;

class AuthServiceImp : public Auth::Service {
public:
    Status parseToken(ServerContext *context, const parseTokenReq *request,
                      parseTokenResp *response) override;

    Status userToken(ServerContext *context, const userTokenReq *request,
                     userTokenResp *response) override;

    AuthServiceImp() : userClient(UserClient::getUserClient()) {
    }

    AuthServiceImp(AuthServiceImp const &) = delete;
    AuthServiceImp &operator=(AuthServiceImp const &) = delete;

    ~AuthServiceImp() = default;

private:
    std::string getKey(std::string userID, int32_t platform) {
        return "IM_RPC_SERVER_AUTH:" + userID + +":" + std::to_string(platform);
    }

private:
    AuthCache authCache;
    UserClient userClient;
};

#endif