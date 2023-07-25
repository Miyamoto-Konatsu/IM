#ifndef CONVERSION_TABLE_H
#define CONVERSION_TABLE_H

#include "odb/core.hxx"
#include <string>
using namespace odb::core;

typedef unsigned long long uint64;
#pragma db value
struct ConversationKey {
    std::string ownerId_;
    std::string conversationId_;
};
#pragma db object table("relation")
class Conversation {
public:
    Conversation() {
    } // 补全构造函数

    // 补全 getter 和 setter 函数
    const ConversationKey &conversationKey() const {
        return conversationKey_;
    }
    void conversationKey(const ConversationKey &conversationKey) {
        conversationKey_ = conversationKey;
    }
    const std::string &ownerId() const {
        return conversationKey_.ownerId_;
    }
    void ownerId(const std::string &ownerId) {
        conversationKey_.ownerId_ = ownerId;
    }

    const std::string &conversationId() const {
        return conversationKey_.conversationId_;
    }
    void conversationId(const std::string &conversationId) {
        conversationKey_.conversationId_ = conversationId;
    }

    const std::string &conversationType() const {
        return conversationType_;
    }
    void conversationType(const std::string &conversationType) {
        conversationType_ = conversationType;
    }

    const std::string &groupId() const {
        return groupId_;
    }
    void groupId(const std::string &groupId) {
        groupId_ = groupId;
    }

    const std::string &toUserId() const {
        return toUserId_;
    }
    void toUserId(const std::string &toUserId) {
        toUserId_ = toUserId;
    }

    uint64 maxSeq() const {
        return maxSeq_;
    }
    void maxSeq(uint64 maxSeq) {
        maxSeq_ = maxSeq;
    }

    uint64 minSeq() const {
        return minSeq_;
    }
    void minSeq(uint64 minSeq) {
        minSeq_ = minSeq;
    }

private:
    friend class odb::access;

#pragma db id
    ConversationKey conversationKey_;

    std::string conversationType_;
    std::string groupId_;  // for group conversation
    std::string toUserId_; // for private conversation
    uint64 maxSeq_;
    uint64 minSeq_;
};

#endif