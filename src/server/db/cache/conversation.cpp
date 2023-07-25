#include "conversation.h"
#include "cache/common.h"
#include "table/conversation.h"
#include <exception>
#include <functional>
#include "relation/common.h"

const std::string ConversationCache::CONVERSATION_PREFIX = "conversation:";
const std::string ConversationCache::CONVERSATION_ID_PREFIX = "conversaion_id:";
const std::string ConversationCache::CONVERSATION_ID_HASH_PREFIX =
    "conversation_id_hash:";
const std::string ConversationCache::CONVERSATION_HAS_READ_PREFIX =
    "conversation_has_read:";

Conversation
ConversationCache::getConversation(const std::string &ownerId,
                                   const std::string &conversationId) {
    std::string key = getConversationKey(ownerId, conversationId);
    std::function<Conversation()> fn = [&, this]() {
        auto conversation = this->db->findConversation(ownerId, conversationId);
        return conversation;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

std::vector<Conversation>
ConversationCache::getConversations(const std::string &ownerId) {
    
}