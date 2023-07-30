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
    "conversaions_id:";
const std::string ConversationCache::CONVERSATION_IDS_HASH_PREFIX =
    "conversations_id_hash:";
const std::string ConversationCache::CONVERSATION_HAS_READ_PREFIX =
    "conversation_has_read:";

using std::vector;
using std::string;

ConversationCache::ConversationCache(std::shared_ptr<ConversationModel> db) :
    db(db) {
}

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
    auto conversaionIds = getConversationIds(ownerId);
    std::vector<std::string> keys;
    for (auto &item : conversaionIds) {
        keys.push_back(getConversationKey(ownerId, item));
    }
    std::function<std::vector<Conversation>()> fn = [&, this]() {
        auto conversations =
            this->db->findConversations(ownerId, conversaionIds);
        return conversations;
    };

    std::function<std::string(const Conversation &)> keyFn =
        [this](const Conversation &conversation) {
            return this->getConversationKey(conversation.ownerId(),
                                            conversation.conversationId());
        };

    std::function<int(const Conversation &, std::vector<std::string>)> indexFn =
        std::bind(&ConversationCache::getKey, this, std::placeholders::_1,
                  std::placeholders::_2);

    return batchGetCache<Conversation>(keys, shared_from_this(), 100,
                                       std::move(keyFn), std::move(indexFn),
                                       std::move(fn));
}

std::vector<std::string>
ConversationCache::getConversationIds(const std::string &ownerId) {
    std::string key = getConversationIdsKey(ownerId);
    std::function<std::vector<std::string>()> fn = [=, this]() {
        auto conversationIds = this->db->findConversationIds(ownerId);
        return conversationIds;
    };

    return getCache(key, shared_from_this(), 100, std::move(fn));
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

    return getCache(key, shared_from_this(), 100, std::move(fn));
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

int ConversationCache::getKey(const Conversation &conversation,
                              const std::vector<std::string> &keys) {
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i]
            == getConversationKey(conversation.ownerId(),
                                  conversation.conversationId())) {
            return i;
        }
    }
    return -1;
}