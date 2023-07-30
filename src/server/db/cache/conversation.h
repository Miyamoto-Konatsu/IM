#ifndef CONVERSATIOND_CACHE_H
#define CONVERSATIOND_CACHE_H

#include <memory>
#include <string>
#include <vector>
#include "common.h"
#include "relation/conversation_model.h"
#include "table/conversation.h"
// rpc SetConversation(SetConversationReq) returns(SetConversationResp) {
// }
// rpc GetConversation(GetConversationReq) returns(GetConversationResp) {
// }
// rpc GetConversations(GetConversationsReq) returns(GetConversationsResp) {
// }
// rpc GetAllConversations(GetAllConversationsReq)
//     returns(GetAllConversationsResp) {
// }
// rpc BatchSetConversations(BatchSetConversationsReq)
//     returns(BatchSetConversationsResp) {
// }
// rpc CreateSingleChatConversations(CreateSingleChatConversationsReq)
//     returns(CreateSingleChatConversationsResp) {
// }
// rpc CreateGroupChatConversations(CreateGroupChatConversationsReq)
//     returns(CreateGroupChatConversationsResp) {
// }
// rpc SetConversationMaxSeq(SetConversationMaxSeqReq)
//     returns(SetConversationMaxSeqResp) {
// }
// rpc GetConversationIDs(GetConversationIDsReq) returns(GetConversationIDsResp)
// {
// }
// rpc GetUserConversationIDsHash(GetUserConversationIDsHashReq)
//     returns(GetUserConversationIDsHashResp) {
// }
// rpc GetConversationsByConversationID(GetConversationsByConversationIDReq)
//     returns(GetConversationsByConversationIDResp) {
// }

class ConversationCache : public Cache {
public:
    static const std::string CONVERSATION_PREFIX;
    static const std::string CONVERSATION_IDS_PREFIX;
    static const std::string CONVERSATION_IDS_HASH_PREFIX;
    static const std::string CONVERSATION_HAS_READ_PREFIX;

    ConversationCache(std::shared_ptr<ConversationModel>);

    virtual ~ConversationCache() = default;

    Conversation getConversation(const std::string &ownerId,
                                 const std::string &conversationId);

    std::vector<Conversation> getConversations(const std::string &ownerId);

    std::vector<std::string> getConversationIds(const std::string &ownerId);

    std::string getConversationKey(const std::string &ownerId,
                                   const std::string &conversationId) {
        return CONVERSATION_PREFIX + ownerId + ":" + conversationId;
    }

    std::string getConversationIdsKey(const std::string &ownerId) {
        return CONVERSATION_IDS_PREFIX + ownerId;
    }

    std::string getConversationIdsHashKey(const std::string &ownerId) {
        return CONVERSATION_IDS_HASH_PREFIX + ownerId;
    }

    std::string getConversationHasReadKey(const std::string &ownerId,
                                          const std::string &conversationId) {
        return CONVERSATION_HAS_READ_PREFIX + ownerId + ":" + conversationId;
    }

    uint64_t getConversationIdsHash(const std::string &ownerId);

    std::vector<std::string>
    getConversationIdsKey(const std::vector<std::string> &users);

    std::vector<std::string>
    getConversationIdsHashKey(const std::vector<std::string> &users);

    int getKey(const Conversation &conversation,
               const std::vector<std::string> &keys);

private:
    std::shared_ptr<ConversationModel> db;
};
#endif // CONVERSATIOND_CACHE_H