#include "conversationDatabase.h"
#include <string>

bool ConversationDatabase::createConversation(
    const std::vector<Conversation> &conversations) {
    for (auto &conversation : conversations) {
        db->createConversation(conversation);
    }

    std::vector<std::string> keys;
    std::set<std::string> users;
    for (auto &conversation : conversations) {
        keys.push_back(cache->getConversationKey(
            conversation.ownerId(), conversation.conversationId()));
        users.insert(conversation.ownerId());
    }
    keys.insert(keys.end(), users.begin(), users.end());
    auto reply = cache->batchDel(keys);
    if (reply.ok())
        return true;
    else
        return false;
}

std::vector<Conversation>
ConversationDatabase::getConversations(const std::string &ownerId) {
    return cache->getConversations(ownerId);
}