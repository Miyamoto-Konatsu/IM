#include "conversation.h"
#include "cache/common.h"
#include "constant.h"
#include "table/conversation.h"
#include "utils/msgutils.h"
#include <stdexcept>
Status
ConversationServiceImp::setConversation(ServerContext *context,
                                        const setConversationReq *request,
                                        setConversationResp *response) {
    auto conversationRpc = request->conversation();
    Conversation conversation;
    db.createConversations({conversation});
    return Status::OK;
}

Status
ConversationServiceImp::getConversation(ServerContext *context,
                                        const getConversationReq *request,
                                        getConversationResp *response) {
    auto conversationId = request->conversationid();
    auto ownerUserId = request->owneruserid();
    auto conversation = db.getConversation(ownerUserId, conversationId);
    response->mutable_conversation()->set_ownerid(conversation.ownerId());
    response->mutable_conversation()->set_touserid(conversation.toUserId());
    response->mutable_conversation()->set_conversationid(
        conversation.conversationId());
    response->mutable_conversation()->set_conversationtype(
        conversation.conversationType());
    response->mutable_conversation()->set_maxseq(conversation.maxSeq());
    response->mutable_conversation()->set_minseq(conversation.minSeq());
    response->mutable_conversation()->set_groupid(conversation.groupId());
    return Status::OK;
}

//获取一个用户的某些conversation
Status
ConversationServiceImp::getConversations(ServerContext *context,
                                         const getConversationsReq *request,
                                         getConversationsResp *response) {
    auto ownerId = request->owneruserid();
    // auto conversations = db.getConversations(ownerId);
    // for (auto &item : conversations) {
    //     auto conversationRpc = response->add_conversations();
    //     conversationRpc->set_ownerid(item.ownerId());
    //     conversationRpc->set_touserid(item.toUserId());
    //     conversationRpc->set_conversationid(item.conversationId());
    //     conversationRpc->set_conversationtype(item.conversationType());
    //     conversationRpc->set_maxseq(item.maxSeq());
    //     conversationRpc->set_minseq(item.minSeq());
    //     conversationRpc->set_groupid(item.groupId());
    // }
    throw std::runtime_error("not implemented");
    return Status::OK;
}

Status ConversationServiceImp::getAllConversations(
    ServerContext *context, const getAllConversationsReq *request,
    getAllConversationsResp *response) {
    auto ownerId = request->owneruserid();
    auto conversations = db.getConversations(ownerId);
    for (auto &item : conversations) {
        auto conversationRpc = response->add_conversations();
        conversationRpc->set_ownerid(item.ownerId());
        conversationRpc->set_touserid(item.toUserId());
        conversationRpc->set_conversationid(item.conversationId());
        conversationRpc->set_conversationtype(item.conversationType());
        conversationRpc->set_maxseq(item.maxSeq());
        conversationRpc->set_minseq(item.minSeq());
        conversationRpc->set_groupid(item.groupId());
    }
    return Status::OK;
}

Status ConversationServiceImp::batchSetConversations(
    ServerContext *context, const batchSetConversationsReq *request,
    batchSetConversationsResp *response) {
    std::vector<Conversation> conversations;
    for (const auto &conversationRpc : request->conversations()) {
        Conversation conversation;
        copyField(conversation, conversationRpc);
        conversations.push_back(conversation);
    }
    db.setConversations(conversations);
    return Status::OK;
}

Status ConversationServiceImp::createGroupChatConversations(
    ServerContext *context, const createGroupChatConversationsReq *request,
    createGroupChatConversationsResp *response) {
    throw std::runtime_error("not implemented");
    return Status::OK;
}

Status ConversationServiceImp::createSingleChatConversation(
    ServerContext *context, const createSingleChatConversationsReq *request,
    createSingleChatConversationsResp *response) {
    auto sendid = request->sendid();
    auto recvid = request->recvid();

    Conversation conversation1;
    conversation1.ownerId(sendid);
    conversation1.toUserId(recvid);
    std::string conversationId = getConversationIdForSingle(sendid, recvid);
    conversation1.conversationId(conversationId);
    conversation1.conversationType(SINGLE_CHAT_TYPE);

    Conversation conversation2;
    conversation2.ownerId(recvid);
    conversation2.toUserId(sendid);
    conversation2.conversationId(conversationId);
    conversation2.conversationType(SINGLE_CHAT_TYPE);

    db.createConversations({conversation1, conversation2});
    return Status::OK;
}
Status ConversationServiceImp::setConversationMaxSeq(
    ServerContext *context, const setConversationMaxSeqReq *request,
    setConversationMaxSeqResp *response) {
    throw std::runtime_error("not implemented");
    return Status::OK;
}

Status
ConversationServiceImp::getConversationIDs(ServerContext *context,
                                           const getConversationIDsReq *request,
                                           getConversationIDsResp *response) {
    auto ownerId = request->userid();
    auto conversationIds = db.getConversationIds(ownerId);
    for (auto &item : conversationIds) { response->add_conversationids(item); }
    return Status::OK;
}

Status ConversationServiceImp::getUserConversationIDsHash(
    ServerContext *context, const getUserConversationIDsHashReq *request,
    getUserConversationIDsHashResp *response) {
    auto ownerId = request->owneruserid();
    auto hash = db.getConversationIdsHash(ownerId);
    response->set_hash(hash);
    return Status::OK;
}
