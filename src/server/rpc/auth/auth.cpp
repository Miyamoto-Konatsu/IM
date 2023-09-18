#include "auth.h"
#include "grpcpp/server_builder.h"
#include "jwt_token.h"
#include "constant.h"
#include <grpcpp/support/status.h>
#include "cache/auth.h"
#include "user.pb.h"
#include <muduo/base/Logging.h>

using grpc::ServerBuilder;
using grpc::Server;

Status AuthServiceImp::parseToken(ServerContext *context,
                                  const parseTokenReq *request,
                                  parseTokenResp *response) {
    std::string token = request->token();
    LOG_DEBUG << "start parse token: " << token.substr(0, 10);
    TokenInfo tokenInfo;
    // 判断token的合法性
    try {
        tokenInfo = ::parseToken(token);
    } catch (...) {
        LOG_DEBUG << "token: " << token.substr(0, 10) << " is invalid";

        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "token is invalid");
    }

    // 从redis获取该token，判断该token是否被踢出
    std::string tokenInRedis =
        authCache.getToken(getKey(tokenInfo.userID, tokenInfo.platform));
    if (tokenInRedis.empty() || tokenInRedis == "ERROR") {
        LOG_DEBUG << "token: " << token.substr(0, 10)
                  << " is invalid, not in redis";

        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "token is invalid");
    }

    response->set_userid(tokenInfo.userID);
    response->set_platformid(tokenInfo.platform);
    response->set_expiretimeseconds(tokenInfo.expireTimeSeconds);
    LOG_DEBUG << "parse token: " << token.substr(0, 10) << " success,"
              << " userID: " << tokenInfo.userID
              << " platform: " << tokenInfo.platform
              << " expireTimeSeconds: " << tokenInfo.expireTimeSeconds;
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
    LOG_DEBUG << "start userToken, userID: " << userID
              << " password: " << password << " platform: " << platform
              << " secret: " << secret;
    if (userID.empty() || password.empty() || platform < 0) {
        return Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            "invalid parameter, userID or password or platform is invalid");
    }
    ServerRpc::user::checkUserReq checkUserReq;
    checkUserReq.set_userid(userID);
    checkUserReq.set_password(password);
    ServerRpc::user::checkUserResp checkUserResp;
    auto status = userClient.checkUser(&checkUserReq, &checkUserResp);
    if (!status.ok() || !checkUserResp.issuccess()) {
        return Status(grpc::StatusCode::INVALID_ARGUMENT,
                      " userID or password is uncorrect");
    }
    // 从redis删除之前已经存在的token
    auto key = getKey(userID, platform);
    authCache.delToken(key);

    // 生成token
    std::string token =
        createToken(userID, platform, TOKEN_EXPIRE_TIME_SECONDS);
    auto set = authCache.setToken(key, token, int(TOKEN_EXPIRE_TIME_SECONDS));
    if (set != "OK") {
        LOG_DEBUG << "set token to redis error: userID: " << userID
                  << " platform: " << platform
                  << " token: " << token.substr(0, 10);
        return grpc::Status(grpc::StatusCode::INTERNAL, "set token error");
    }
    LOG_DEBUG << "set token to redis success: userID: " << userID
              << " platform: " << platform << " token: " << token.substr(0, 10);
    response->set_token(token);
    response->set_expiretimeseconds(TOKEN_EXPIRE_TIME_SECONDS);
    return Status::OK;
}

int main() {
    muduo::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
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