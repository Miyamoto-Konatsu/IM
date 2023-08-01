#ifndef CONVERSATION_API_H
#define CONVERSATION_API_H

#include "api2rpc.h"
#include "conversation.pb.h"
#include "conversation/conversation.h"
#include <functional>

class ConversationApi {
public:
    ConversationApi() :
        conversationClient_(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials())) {
    }

    ~ConversationApi() {
        std::cout << "ConversationApi destructor" << std::endl;
    }

    void setConversation(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::setConversationReq,
                ServerRpc::conversation::setConversationResp>(
            std::bind(&ConversationClient::setConversation,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void getConversation(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getConversationReq,
                ServerRpc::conversation::getConversationResp>(
            std::bind(&ConversationClient::getConversation,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void getConversations(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getConversationsReq,
                ServerRpc::conversation::getConversationsResp>(
            std::bind(&ConversationClient::getConversations,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void getAllConversations(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getAllConversationsReq,
                ServerRpc::conversation::getAllConversationsResp>(
            std::bind(&ConversationClient::getAllConversations,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void batchSetConversations(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::batchSetConversationsReq,
                ServerRpc::conversation::batchSetConversationsResp>(
            std::bind(&ConversationClient::batchSetConversations,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void createSingleChatConversations(const HttpRequest &req,
                                       HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::createSingleChatConversationsReq,
                ServerRpc::conversation::createSingleChatConversationsResp>(
            std::bind(&ConversationClient::createSingleChatConversations,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void getConversationIDs(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getConversationIDsReq,
                ServerRpc::conversation::getConversationIDsResp>(
            std::bind(&ConversationClient::getConversationIDs,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

    void getUserConversationIDsHash(const HttpRequest &req,
                                    HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getUserConversationIDsHashReq,
                ServerRpc::conversation::getUserConversationIDsHashResp>(
            std::bind(&ConversationClient::getUserConversationIDsHash,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }
    void getConversationsByConversationID(const HttpRequest &req,
                                          HttpResponse &resp) {
        api2rpc<ServerRpc::conversation::getConversationsByConversationIDReq,
                ServerRpc::conversation::getConversationsByConversationIDResp>(
            std::bind(&ConversationClient::getConversationsByConversationID,
                      &conversationClient_, std::placeholders::_1,
                      std::placeholders::_2),
            req, resp);
    }

private:
    ConversationClient conversationClient_;
};

#endif