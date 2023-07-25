#include "conversationDatabase.h"
#include <cstdint>
#include <picojson/picojson.h>
#include <string>

bool ConversationDatabase::createConversations(
    const std::vector<Conversation> &conversations) {
    for (auto &conversation : conversations) {
        db->createConversations(conversation);
    }

    std::vector<std::string> keys;
    std::set<std::string> users;
    for (auto &conversation : conversations) {
        keys.push_back(cache->getConversationKey(
            conversation.ownerId(), conversation.conversationId()));
        users.insert(conversation.ownerId());
    }

    auto idsKey = cache->getConversationIdsKey(
        std::vector<std::string>{users.begin(), users.end()});
    keys.insert(keys.end(), idsKey.begin(), idsKey.end());

    auto hashKey = cache->getConversationIdsHashKey(
        std::vector<std::string>{users.begin(), users.end()});
    keys.insert(keys.end(), hashKey.begin(), hashKey.end());

    auto reply = cache->batchDel(keys);
    if (reply.ok())
        return true;
    else
        return false;
}

bool ConversationDatabase::setConversations(
    const std::vector<Conversation> &conversations) {
    db->updateConversation(conversations);
    std::vector<std::string> keys;
    std::set<std::string> users;
    for (auto &conversation : conversations) {
        keys.push_back(cache->getConversationKey(
            conversation.ownerId(), conversation.conversationId()));
        users.insert(conversation.ownerId());
    }
    auto idsKey = cache->getConversationIdsKey(
        std::vector<std::string>{users.begin(), users.end()});

    keys.insert(keys.end(), idsKey.begin(), idsKey.end());

    auto idsHashKey = cache->getConversationIdsHashKey(
        std::vector<std::string>{users.begin(), users.end()});
    keys.insert(keys.end(), idsHashKey.begin(), idsHashKey.end());

    auto reply = cache->batchDel(keys);
    return true;
}

std::vector<Conversation>
ConversationDatabase::getConversations(const std::string &ownerId) {
    return cache->getConversations(ownerId);
}

Conversation
ConversationDatabase::getConversation(const std::string &ownerId,
                                      const std::string &conversaionId) {
    return cache->getConversation(ownerId, conversaionId);
}

std::vector<std::string>
ConversationDatabase::getConversationIds(const std::string &ownerId) {
    return cache->getConversationIds(ownerId);
}

uint64_t
ConversationDatabase::getConversationIdsHash(const std::string &ownerId) {
    return cache->getConversationIdsHash(ownerId);
}
