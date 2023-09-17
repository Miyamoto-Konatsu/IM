#pragma once
#include "table/chatlog.h"
#include <cstdint>
#include <memory>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>
#include <odb/mysql/database.hxx>
#include <vector>
#include "table/chatlog-odb.hxx"
#include "utils.h"
#include "common.h"
#include <cstring>

class ChatLogModel {
public:
    ChatLogModel() : db(getDB()) {
    }

    int64_t createChatLog(ChatLog &chatLog) {
        odb::transaction t(db->begin());
        int id = db->persist(chatLog); // 将对象插入数据库
        t.commit();                    // 提交事务
        return id;
    }

    void createChatLog(std::vector<ChatLog> &chatLogs) {
        odb::transaction t(db->begin());
        for (auto &chatLog : chatLogs) {
            db->persist(chatLog); // 将对象插入数据库
        }
        t.commit(); // 提交事务
    }

    std::vector<ChatLog> findChatLog(const std::string &conversaionId,
                                     const int64_t seqStart,
                                     const int64_t seqEnd) {
        odb::transaction t(db->begin());
        odb::query<ChatLog> query(odb::query<ChatLog>::conversaionId
                                      == conversaionId.data()
                                  && odb::query<ChatLog>::seq <= seqEnd
                                  && odb::query<ChatLog>::seq >= seqStart
                                  );
        auto findResult = db->query(query);
        std::vector<ChatLog> result;
        for (auto &chatLog : findResult) { result.push_back(chatLog); }
        t.commit(); // 提交事务
        return result;
    }

private:
    std::shared_ptr<odb::database> db;
};