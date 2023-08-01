#ifndef CONVERSATION_RPC_H
#define CONVERSATION_RPC_H

#include <string>
#include "conversation.pb.h"
#include "conversation.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>
#include "controller/conversationDatabase.h"
using grpc::ServerContext;
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

class ConversationServiceImp : public RpcConversationService::Service {
public:
    Status setConversation(ServerContext *context,
                           const setConversationReq *request,
                           setConversationResp *response);
    Status getConversation(ServerContext *context,
                           const getConversationReq *request,
                           getConversationResp *response);
    Status getConversations(ServerContext *context,
                            const getConversationsReq *request,
                            getConversationsResp *response);
    Status getAllConversations(ServerContext *context,
                               const getAllConversationsReq *request,
                               getAllConversationsResp *response);
    Status batchSetConversations(ServerContext *context,
                                 const batchSetConversationsReq *request,
                                 batchSetConversationsResp *response);
    Status
    createGroupChatConversations(ServerContext *context,
                                 const createGroupChatConversationsReq *request,
                                 createGroupChatConversationsResp *response);
    Status createSingleChatConversations(
        ServerContext *context, const createSingleChatConversationsReq *request,
        createSingleChatConversationsResp *response);

    Status setConversationMaxSeq(ServerContext *context,
                                 const setConversationMaxSeqReq *request,
                                 setConversationMaxSeqResp *response);

    Status getConversationIDs(ServerContext *context,
                              const getConversationIDsReq *request,
                              getConversationIDsResp *response);
    Status
    getUserConversationIDsHash(ServerContext *context,
                               const getUserConversationIDsHashReq *request,
                               getUserConversationIDsHashResp *response);
    Status getConversationsByConversationID(
        ServerContext *context,
        const getConversationsByConversationIDReq *request,
        getConversationsByConversationIDResp *response);
    

private:
    ConversationDatabase db;
};
#endif // CONVERSATION_RPC_H
