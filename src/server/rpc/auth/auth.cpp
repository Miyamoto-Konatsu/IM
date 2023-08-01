#include "auth.h"
#include "grpcpp/server_builder.h"
#include "jwt_token.h"
#include "constant.h"
#include <grpcpp/support/status.h>
#include "cache/auth.h"

using grpc::ServerBuilder;
using grpc::Server;

Status AuthServiceImp::parseToken(ServerContext *context,
                                  const parseTokenReq *request,
                                  parseTokenResp *response) {
    std::string token = request->token();
    std::cout << "token: " << token << std::endl;
    TokenInfo tokenInfo;
    // 判断token的合法性
    try {
        tokenInfo = ::parseToken(token);
    } catch (...) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "token is invalid");
    }

    // 从redis获取该token，判断该token是否被踢出
    std::string tokenInRedis =
        authCache.getToken(getKey(tokenInfo.userID, tokenInfo.platform));
    if (tokenInRedis.empty() || tokenInRedis == "ERROR") {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "token is invalid");
    }

    response->set_userid(tokenInfo.userID);
    response->set_platformid(tokenInfo.platform);
    response->set_expiretimeseconds(tokenInfo.expireTimeSeconds);
    std::cout << "userID: " << tokenInfo.userID << std::endl;
    std::cout << "platform: " << tokenInfo.platform << std::endl;
    std::cout << "expireTimeSeconds: " << tokenInfo.expireTimeSeconds
              << std::endl;
    return Status::OK;
}

Status AuthServiceImp::userToken(ServerContext *context,
                                 const userTokenReq *request,
                                 userTokenResp *response) {
    std::string userID = request->userid();
    std::string password = request->password();
    auto platform = request->platformid();
    auto secret = request->secret();
    // 判断用户名和密码的合法性

    // 从redis删除之前已经存在的token
    auto key = getKey(userID, platform);
    authCache.delToken(key);

    // 生成token
    std::string token =
        createToken(userID, platform, TOKEN_EXPIRE_TIME_SECONDS);
    auto set = authCache.setToken(key, token, int(TOKEN_EXPIRE_TIME_SECONDS));
    if(set != "OK") {
        return grpc::Status(grpc::StatusCode::INTERNAL,
                            "set token error");
    }
    
    std::cout << "username: " << userID << std::endl;
    std::cout << "password: " << password << std::endl;
    response->set_token(token);
    response->set_expiretimeseconds(TOKEN_EXPIRE_TIME_SECONDS);
    return Status::OK;
}

int main() {
    std::string server_address("0.0.0.0:50052");
    AuthServiceImp service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "AuthServer listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}