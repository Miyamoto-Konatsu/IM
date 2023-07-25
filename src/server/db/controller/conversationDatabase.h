#ifndef CONVERSATIONDATABASE_CONTROLLER_H
#define CONVERSATIONDATABASE_CONTROLLER_H

#include "relation/conversation_model.h"
#include "cache/conversation.h"
#include "table/conversation.h"
#include <memory>
#include <vector>

class ConversationDatabase {
public:
    ConversationDatabase() = default;
    ~ConversationDatabase() = default;

    bool createConversation(const std::vector<Conversation> &conversations);

    std::vector<Conversation> getConversations(const std::string &ownerId);

private:
    std::shared_ptr<ConversationCache> cache;
    std::shared_ptr<ConversationModel> db;
};
#endif // CONVERSATIONDATABASE_CONTROLLER_H