#include "auth.h"
#include "grpcpp/server_builder.h"
#include "jwt_token.h"

using grpc::ServerBuilder;
using grpc::Server;

Status AuthServiceImp::parseToken(ServerContext *context,
                                  const parseTokenReq *request,
                                  parseTokenResp *response) {
    std::string token = request->token();
    std::cout << "token: " << token << std::endl;
    TokenInfo tokenInfo = ::parseToken(token);
    response->set_userid("userid");
    response->set_platform("platform");
    response->set_expiretimeseconds(1000);
    return Status::OK;
}

Status AuthServiceImp::userToken(ServerContext *context,
                                 const userTokenReq *request,
                                 userTokenResp *response) {
    std::string userID = request->userid();
    std::string password = request->password();
    std::cout << "username: " << userID << std::endl;
    std::cout << "password: " << password << std::endl;
    response->set_token("token");
    response->set_expiretimeseconds(1000);
    return Status::OK;
}

int main() {
    std::string server_address("0.0.0.0:50051");
    AuthServiceImp service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}