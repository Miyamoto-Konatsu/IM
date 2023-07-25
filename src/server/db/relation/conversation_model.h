#ifndef CONVERSION_MODEL_RELATION_H
#define CONVERSION_MODEL_RELATION_H

#include "table/conversation.h"
#include <memory>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>
#include <odb/mysql/database.hxx>
#include <vector>
#include "table/conversation-odb.hxx"
#include "utils.h"
#include "common.h"

class ConversationModel {
public:
    ConversationModel() : db(getDB()) {
    }

    void createConversations(const Conversation &conversation) {
        odb::transaction t(db->begin());
        db->persist(conversation); // 将对象插入数据库
        t.commit();                // 提交事务
    }

    // 查询 Conversation 对象
    Conversation findConversation(const std::string &ownerId,
                                  const std::string &conversationId) {
        odb::transaction t(db->begin());
        odb::query<Conversation> query(
            odb::query<Conversation>::conversationKey.conversationId
                == conversationId
            && odb::query<Conversation>::conversationKey.ownerId == ownerId);
        Conversation result;
        auto isFound = db->query_one(query, result);
        t.commit();
        if (isFound) {
            return result;
        } else {
            throw DatabaseLookupError("Conversation not found");
        }
    }

    std::vector<Conversation> findConversations(const std::string &ownerId) {
        odb::transaction t(db->begin());
        odb::query<Conversation> query(
            odb::query<Conversation>::conversationKey.ownerId == ownerId);
        std::vector<Conversation> result;
        auto queryResult = db->query(query);
        t.commit();
        for (auto &item : queryResult) { result.push_back(std::move(item)); }
        return result;
    }

    // 更新 Conversation 对象
    void updateConversation(const std::vector<Conversation> &conversations) {
        odb::transaction t(db->begin());
        for (auto &conversation : conversations) {
            try {
                auto existingConversation =
                    db->load<Conversation>(conversation.conversationKey());
                db->update(conversation);
            } catch (odb::object_not_persistent &e) {
                db->persist(conversation);
            }
        }
        t.commit(); // 提交事务
    }

    std::vector<std::string> findConversationIds(const std::string &ownerId) {
        odb::transaction t(db->begin());
        odb::query<Conversation> query(
            odb::query<Conversation>::conversationKey.ownerId == ownerId);
        std::vector<std::string> result;
        auto queryResult = db->query(query);
        t.commit();
        for (auto &item : queryResult) {
            result.push_back(item.conversationKey().conversationId_);
        }
        return result;
    }

private:
    std::shared_ptr<database> db;
};
#endif