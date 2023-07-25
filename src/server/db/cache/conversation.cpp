#include "conversation.h"
#include "cache/common.h"
#include "table/conversation.h"
#include <exception>
#include <functional>
#include "relation/common.h"
#include "conversation.pb.h"

using ConversationRpc = ServerRpc::conversation::conversation;

const std::string ConversationCache::CONVERSATION_PREFIX = "conversation:";
const std::string ConversationCache::CONVERSATION_IDS_PREFIX =
    "conversaion_id:";
const std::string ConversationCache::CONVERSATION_IDS_HASH_PREFIX =
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
    return getCache<Conversation, ConversationRpc>(key, shared_from_this(), 100,
                                                   std::move(fn));
}

std::vector<Conversation>
ConversationCache::getConversations(const std::string &ownerId) {
    auto conversaionIds = getConversationIds(ownerId);
    std::vector<std::string> keys;
    for (auto &item : conversaionIds) {
        keys.push_back(getConversationKey(ownerId, item));
    }
    std::function<std::vector<Conversation>()> fn = [&, this]() {
        auto conversations = this->db->findConversations(ownerId);
        return conversations;
    };

    std::function<std::string(const Conversation &)> keyFn =
        [this](const Conversation &conversation) {
            return this->getConversationKey(conversation.ownerId(),
                                            conversation.conversationId());
        };
    return batchGetCache<Conversation, ConversationRpc>(
        keys, shared_from_this(), 100, std::move(keyFn), std::move(fn));
}

std::vector<std::string>
ConversationCache::getConversationIds(const std::string &ownerId) {
    std::string key = getConversationIdsKey(ownerId);
    std::function<std::vector<std::string>()> fn = [&, this]() {
        auto conversationIds = this->db->findConversationIds(ownerId);
        return conversationIds;
    };

    return getCache<std::vector<std::string>, std::string>(
        key, shared_from_this(), 100, std::move(fn));
}

uint64_t ConversationCache::getConversationIdsHash(const std::string &ownerId) {
    std::string key = getConversationIdsHashKey(ownerId);
    std::function<uint64_t()> fn = [&, this]() {
        auto conversationIds = this->db->findConversationIds(ownerId);
        uint64_t hash = 0;
        for (auto &item : conversationIds) {
            hash = hash ^ std::hash<std::string>()(item);
        }
        return hash;
    };

    return getCache<Conversation, ConversationRpc>(key, shared_from_this(), 100,
                                                   std::move(fn));
}

std::vector<std::string> ConversationCache::getConversationIdsKey(
    const std::vector<std::string> &users) {
    std::vector<std::string> keys;
    for (auto &item : users) { keys.push_back(getConversationIdsKey(item)); }
    return keys;
}

std::vector<std::string> ConversationCache::getConversationIdsHashKey(
    const std::vector<std::string> &users) {
    std::vector<std::string> keys;
    for (auto &item : users) {
        keys.push_back(getConversationIdsHashKey(item));
    }
    return keys;
}