#include "conversation.h"

Status
ConversationServiceImp::setConversation(ServerContext *context,
                                        const setConversationReq *request,
                                        setConversationResp *response) {
    
    return Status::OK;
}

Status ConversationServiceImp::getConversation(ServerContext *context,
                                               const getConversationReq *request,
                                               getConversationResp *response) {
    return Status::OK;
}

Status ConversationServiceImp::getConversations(ServerContext *context,
                                                const getConversationsReq *request,
                                                getConversationsResp *response) {
    return Status::OK;
}

Status ConversationServiceImp::getAllConversations(ServerContext *context,
                                                   const getAllConversationsReq *request,
                                                   getAllConversationsResp *response) {
    return Status::OK;
}

Status ConversationServiceImp::batchSetConversations(ServerContext *context,
                                                     const batchSetConversationsReq *request,
                                                     batchSetConversationsResp *response) {
    return Status::OK;
}

Status ConversationServiceImp::createGroupChatConversations(ServerContext *context,
                                                            const createGroupChatConversationsReq *request,
                                                            createGroupChatConversationsResp *response) {
    return Status::OK;
}

Status ConversationServiceImp::createSingleChatConversation(
    ServerContext *context, const createSingleChatConversationsReq *request,
    createSingleChatConversationsResp *response) {
    return Status::OK;
}
Status ConversationServiceImp::setConversationMaxSeq(ServerContext *context,
                                                     const setConversationMaxSeqReq *request,
                                                     setConversationMaxSeqResp *response) {
    return Status::OK;
}


Status ConversationServiceImp::getConversationIDs(ServerContext *context,
                                                  const getConversationIDsReq *request,
                                                  getConversationIDsResp *response) {
    return Status::OK;
}


Status ConversationServiceImp::getUserConversationIDsHash(ServerContext *context,
                                                          const getUserConversationIDsHashReq *request,
                                                          getUserConversationIDsHashResp *response) {
    return Status::OK;
}

