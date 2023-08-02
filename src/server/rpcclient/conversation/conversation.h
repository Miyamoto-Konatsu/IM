#ifndef CONVERSATION_RPCCLINT_H
#define CONVERSATION_RPCCLINT_H

#include "conversation.pb.h"
#include "conversation.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>

using grpc::Status;

// using ServerRpc::conversation里的全部成员
using RpcConversationData = ServerRpc::conversation::conversation;
using ServerRpc::conversation::setConversationReq;
using ServerRpc::conversation::setConversationResp;
using ServerRpc::conversation::getConversationReq;
using ServerRpc::conversation::getConversationResp;
using ServerRpc::conversation::getConversationsReq;
using ServerRpc::conversation::getConversationsResp;
using ServerRpc::conversation::getAllConversationsReq;
using ServerRpc::conversation::getAllConversationsResp;
using ServerRpc::conversation::batchSetConversationsReq;
using ServerRpc::conversation::batchSetConversationsResp;
using ServerRpc::conversation::createSingleChatConversationsReq;
using ServerRpc::conversation::createSingleChatConversationsResp;
using ServerRpc::conversation::createGroupChatConversationsReq;
using ServerRpc::conversation::createGroupChatConversationsResp;
using ServerRpc::conversation::setConversationMaxSeqReq;
using ServerRpc::conversation::setConversationMaxSeqResp;

using ServerRpc::conversation::getConversationIDsReq;
using ServerRpc::conversation::getConversationIDsResp;
using ServerRpc::conversation::getUserConversationIDsHashReq;
using ServerRpc::conversation::getUserConversationIDsHashResp;
using ServerRpc::conversation::getConversationsByConversationIDReq;
using ServerRpc::conversation::getConversationsByConversationIDResp;
using RpcConversationService = ServerRpc::conversation::Conversation;
class ConversationClient {
public:
    ConversationClient(std::shared_ptr<grpc::Channel> channel) :
        stub_(RpcConversationService::NewStub(channel)) {
    }

    Status setConversation(const setConversationReq *request,
                           setConversationResp *response) {
        grpc::ClientContext context;
        return stub_->setConversation(&context, *request, response);
    }

    Status getConversation(const getConversationReq *request,
                           getConversationResp *response) {
        grpc::ClientContext context;
        return stub_->getConversation(&context, *request, response);
    }

    Status getConversations(const getConversationsReq *request,
                            getConversationsResp *response) {
        grpc::ClientContext context;
        return stub_->getConversations(&context, *request, response);
    }

    Status getAllConversations(const getAllConversationsReq *request,
                               getAllConversationsResp *response) {
        grpc::ClientContext context;
        return stub_->getAllConversations(&context, *request, response);
    }

    Status batchSetConversations(const batchSetConversationsReq *request,
                                 batchSetConversationsResp *response) {
        grpc::ClientContext context;
        return stub_->batchSetConversations(&context, *request, response);
    }

    Status
    createGroupChatConversations(const createGroupChatConversationsReq *request,
                                 createGroupChatConversationsResp *response) {
        grpc::ClientContext context;
        return stub_->createGroupChatConversations(&context, *request,
                                                   response);
    }

    Status createSingleChatConversations(
        const createSingleChatConversationsReq *request,
        createSingleChatConversationsResp *response) {
        grpc::ClientContext context;
        return stub_->createSingleChatConversations(&context, *request,
                                                    response);
    }

    Status setConversationMaxSeq(const setConversationMaxSeqReq *request,
                                 setConversationMaxSeqResp *response) {
        grpc::ClientContext context;
        return stub_->setConversationMaxSeq(&context, *request, response);
    }

    Status getConversationIDs(const getConversationIDsReq *request,
                              getConversationIDsResp *response) {
        grpc::ClientContext context;
        return stub_->getConversationIDs(&context, *request, response);
    }

    Status
    getUserConversationIDsHash(const getUserConversationIDsHashReq *request,
                               getUserConversationIDsHashResp *response) {
        grpc::ClientContext context;
        return stub_->getUserConversationIDsHash(&context, *request, response);
    }

    Status getConversationsByConversationID(
        const getConversationsByConversationIDReq *request,
        getConversationsByConversationIDResp *response) {
        grpc::ClientContext context;
        return stub_->getConversationsByConversationID(&context, *request,
                                                       response);
    }

    static ConversationClient getConversationClient() {
        return ConversationClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    }

private:
    std::unique_ptr<RpcConversationService::Stub> stub_;
};
#endif // CONVERSATION_RPCCLINT_H