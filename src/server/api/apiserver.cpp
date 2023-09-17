#include "apiserver.h"
#include <httplib.h>
#include <memory>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include "conversation.h"
#include "user.h"
#include "auth.h"
#include "group.h"
#include "msg.h"

ApiServer::ApiServer(unsigned short port, int threadNum) :
    port_(port), server_(new httplib::Server()), numThreads_(threadNum) {
    // server_->setHttpCallback(std::bind(&ApiServer::onRequest, this,
    //                                    std::placeholders::_1,
    //                                    std::placeholders::_2));
    server_->set_logger(
        [](const httplib::Request &req, const httplib::Response &res) {
            std::cout << req.method << " " << req.path << " -> " << res.status
                      << std::endl;
        });
    server_->set_keep_alive_max_count(100);
    server_->set_keep_alive_timeout(5);

    std::shared_ptr<AuthApi> authApi(new AuthApi());

    std::function<void(const HttpRequest &, HttpResponse &)> userTokenFunc =
        std::bind(&AuthApi::userToken, authApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/auth/userToken", userTokenFunc);

    // std::function<void(const HttpRequest &, HttpResponse &)> parseTokenFunc =
    //     std::bind(&AuthApi::parseToken, authApi, std::placeholders::_1,
    //               std::placeholders::_2);

    // server_->Post("/auth/parseToken", parseTokenFunc);

    server_->set_pre_routing_handler(
        [authApi](const httplib::Request &req,
                  httplib::Response &res) -> httplib::Server::HandlerResponse {
            if (req.path != "/auth/userToken"
                && req.path != "/user/createUser") {
                std::string token = req.get_header_value("token");
                if (token.empty()) {
                    LOG_DEBUG << "ip: " << req.remote_addr
                              << " port: " << req.remote_port << " error: "
                              << " token is empty, unauthorized";
                    res.status = 401;
                    res.set_content("Unauthorized", "text/plain");
                    return httplib::Server::HandlerResponse::Handled;
                }
                ServerRpc::auth::parseTokenReq reqRpc;
                reqRpc.set_token(token);
                ServerRpc::auth::parseTokenResp respRpc;
                auto status = authApi->parseToken(reqRpc, respRpc);
                if (!status.ok()) {
                    LOG_DEBUG << "ip: " << req.remote_addr
                              << " port: " << req.remote_port
                              << " error: " << status.error_message();
                    res.status = 401;
                    res.set_content("Unauthorized", "text/plain");
                    return httplib::Server::HandlerResponse::Handled;
                }
            }
            return httplib::Server::HandlerResponse::Unhandled;
        });

    // server_->set_error_handler(
    //     [](const httplib::Request & /*req*/, httplib::Response &res) {
    //         const char *fmt = "<p>Error Status: <span
    //         style='color:red;'>%d</span></p>"; char buf[BUFSIZ];
    //         snprintf(buf, sizeof(buf), fmt, res.status);
    //         res.set_content(buf, "text/html");
    //     });

    // ********* conversation api register *********

    std::shared_ptr<ConversationApi> conversationApi =
        std::make_shared<ConversationApi>();
    std::function<void(const HttpRequest &, HttpResponse &)>
        setConversationFunc =
            std::bind(&ConversationApi::setConversation, conversationApi,
                      std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/setConversation", setConversationFunc);

    std::function<void(const HttpRequest &, HttpResponse &)>
        getConversationFunc =
            std::bind(&ConversationApi::getConversation, conversationApi,
                      std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/getConversation", getConversationFunc);

    std::function<void(const HttpRequest &, HttpResponse &)>
        getAllConversationsFunc =
            std::bind(&ConversationApi::getAllConversations, conversationApi,
                      std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/getAllConversations", getAllConversationsFunc);

    using funcBind = std::function<void(const HttpRequest &, HttpResponse &)>;
    funcBind createSingleChatConversationsFunc = std::bind(
        &ConversationApi::createSingleChatConversations, conversationApi,
        std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/createSingleChatConversations",
                  createSingleChatConversationsFunc);

    funcBind getConversationIDsFunc =
        std::bind(&ConversationApi::getConversationIDs, conversationApi,
                  std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/getConversationIDs", getConversationIDsFunc);

    funcBind getUserConversationIDsHashFunc =
        std::bind(&ConversationApi::getUserConversationIDsHash, conversationApi,
                  std::placeholders::_1, std::placeholders::_2);
    server_->Post("/conversation/getUserConversationIDsHash",
                  getUserConversationIDsHashFunc);

    // ********* user api register *********
    std::shared_ptr<UserApi> userApi = std::make_shared<UserApi>();

    funcBind getUserFunc =
        std::bind(&UserApi::getUser, userApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/user/getUser", getUserFunc);

    funcBind createUserFunc =
        std::bind(&UserApi::createUser, userApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/user/createUser", createUserFunc);

    funcBind checkUserFunc =
        std::bind(&UserApi::checkUser, userApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/user/checkUser", checkUserFunc);

    // ********* group api register *********
    std::shared_ptr<GroupApi> groupApi = std::make_shared<GroupApi>();
    funcBind createGroupFunc =
        std::bind(&GroupApi::createGroup, groupApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/group/createGroup", createGroupFunc);

    funcBind joinGroupFunc =
        std::bind(&GroupApi::joinGroup, groupApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/group/joinGroup", joinGroupFunc);

    funcBind getGroupInfoFunc =
        std::bind(&GroupApi::getGroupInfo, groupApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/group/getGroupInfo", getGroupInfoFunc);

    // funcBind getGroupMemberFunc =
    //     std::bind(&GroupApi::getGroupMember, groupApi, std::placeholders::_1,
    //               std::placeholders::_2);
    // server_->Post("/group/getGroupMember", getGroupMemberFunc);

    funcBind getGroupListFunc =
        std::bind(&GroupApi::getGroupList, groupApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/group/getGroupList", getGroupListFunc);


    // ********* msg api register *********
    std::shared_ptr<MsgApi> msgApi = std::make_shared<MsgApi>();
    funcBind syncMsgsFunc =
        std::bind(&MsgApi::syncMsgs, msgApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/msg/syncMsgs", syncMsgsFunc);

    funcBind sendMsgFunc = std::bind(
        &MsgApi::sendMsg, msgApi, std::placeholders::_1, std::placeholders::_2);
    server_->Post("/msg/sendMsg", sendMsgFunc);

    funcBind setHasReadSeqFunc =
        std::bind(&MsgApi::setHasReadSeq, msgApi, std::placeholders::_1,
                  std::placeholders::_2);
    server_->Post("/msg/setHasReadSeq", setHasReadSeqFunc);

    funcBind getHasReadSeqAndMaxSeqFunc =
        std::bind(&MsgApi::getHasReadSeqAndMaxSeq, msgApi,
                  std::placeholders::_1, std::placeholders::_2);
    server_->Post("/msg/getHasReadSeqAndMaxSeq", getHasReadSeqAndMaxSeqFunc);
}

ApiServer::~ApiServer() {
    server_->stop();
}

void ApiServer::resigterApi(
    const std::string &path, const std::string &method,
    const std::function<void(const HttpRequest &, HttpResponse &)> &callback) {
    apiMap_[std::make_pair(path, method)] = callback;
}

void ApiServer::start() {
    server_->listen("0.0.0.0", port_);
}

int main(int argc, char *argv[]) {
    muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
    std::cout << "ApiServer listening on 0.0.0.0:8080" << std::endl;
    ApiServer server(8080, 4);
    server.start();
    return 0;
}