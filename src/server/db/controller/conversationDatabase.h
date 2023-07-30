#ifndef CONVERSATIONDATABASE_CONTROLLER_H
#define CONVERSATIONDATABASE_CONTROLLER_H

#include "relation/conversation_model.h"
#include "cache/conversation.h"
#include "table/conversation.h"
#include <memory>
#include <vector>

class ConversationDatabase {
public:
    ConversationDatabase();
    ~ConversationDatabase() = default;

    ConversationDatabase(const ConversationDatabase &) = delete;
    ConversationDatabase &operator=(const ConversationDatabase &) = delete;

    bool createConversations(const std::vector<Conversation> &conversations);

    bool setConversations(const std::vector<Conversation> &conversations);

    std::vector<Conversation> getConversations(const std::string &ownerId);

    Conversation getConversation(const std::string &ownerId,
                                 const std::string &conversationId);

    std::vector<std::string> getConversationIds(const std::string &ownerId);

    uint64_t getConversationIdsHash(const std::string &ownerId);

private:
    std::shared_ptr<ConversationCache> cache;
    std::shared_ptr<ConversationModel> db;
};
#endif // CONVERSATIONDATABASE_CONTROLLER_H