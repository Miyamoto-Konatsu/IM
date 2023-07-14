#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include "auth.grpc.pb.h"
#include "auth.pb.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server.h>

using grpc::ServerContext;
using grpc::Status;

using ServerRpc::auth::parseTokenResp;
using ServerRpc::auth::parseTokenReq;
using ServerRpc::auth::userTokenReq;
using ServerRpc::auth::userTokenResp;

using ServerRpc::auth::Auth;

class AuthServiceImp : public Auth::Service {
    Status parseToken(ServerContext *context, const parseTokenReq *request, parseTokenResp *response) override;

    Status userToken(ServerContext *context, const userTokenReq *request, userTokenResp *response) override;
};

#endif