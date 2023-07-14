#include "auth.h"
#include "jwt_token.h"

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
    return Status::OK;
}
