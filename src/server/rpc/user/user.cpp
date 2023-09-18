#include "user.h"
#include "cache/common.h"
#include "table/user.h"
#include <grpcpp/support/status.h>
#include "openssl/evp.h"
#include "openssl/sha.h"
using grpc::Server;
using grpc::ServerBuilder;

static std::string encryptPasswd(const std::string &passwd) {
    // 创建一个哈希上下文
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    // 指定要使用的哈希算法，例如SHA-256
    const EVP_MD *md = EVP_sha256();

    // 初始化哈希上下文
    EVP_DigestInit_ex(mdctx, md, NULL);

    // 添加密码数据到哈希上下文
    EVP_DigestUpdate(mdctx, passwd.c_str(), passwd.size());

    // 获取哈希结果
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    unsigned char md_value_str[EVP_MAX_MD_SIZE];

    std::string hashResult;
    for (unsigned int i = 0; i < md_len; i++) {
        char hex[3] = {0};
        sprintf(hex, "%02x", md_value[i]);
        hashResult += hex;
    }

    // 清理哈希上下文
    EVP_MD_CTX_free(mdctx);
    return hashResult;
}
    Status UserServiceImpl::getUser(
        ::grpc::ServerContext * context,
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

    Status UserServiceImpl::createUser(
        ::grpc::ServerContext * context,
        const ::ServerRpc::user::createUserReq *request,
        ::ServerRpc::user::createUserResp *response) {
        auto userRpc = request->user();
        userRpc.set_password(encryptPasswd(userRpc.password()));
        auto result = userDatabase_->createUser(userRpc);
        response->set_issuccess(result);
        return Status::OK;
    }

    Status UserServiceImpl::checkUser(
        ::grpc::ServerContext * context,
        const ::ServerRpc::user::checkUserReq *request,
        ::ServerRpc::user::checkUserResp *response) {
        auto userId = request->userid();
        auto password = request->password();
        password = encryptPasswd(password);
        auto result = userDatabase_->checkUser(userId, password);
        response->set_issuccess(result);
        return Status::OK;
    }

    int main() {
        std::string server_address("0.0.0.0:50055");
        UserServiceImpl service;
        ServerBuilder builder;
        builder.AddListeningPort(server_address,
                                 grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;
        server->Wait();
        return 0;
    }