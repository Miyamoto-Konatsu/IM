#include "apiserver.h"
#include "auth.h"
#include <httplib.h>
#include <memory>
#include <muduo/net/EventLoop.h>
#include <functional>
#include "conversation.h"
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
            if (req.path != "/auth/userToken") {
                std::string token = req.get_param_value("token");
                if (token.empty()) {
                    res.status = 401;
                    res.set_content("Unauthorized", "text/plain");
                    return httplib::Server::HandlerResponse::Handled;
                }
                ServerRpc::auth::parseTokenReq reqRpc;
                reqRpc.set_token(token);
                ServerRpc::auth::parseTokenResp respRpc;
                auto status = authApi->parseToken(reqRpc, respRpc);
                if (!status.ok()) {
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
    ApiServer server(8080, 4);
    server.start();
    return 0;
}