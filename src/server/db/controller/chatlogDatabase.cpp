#include "chatlogDatabase.h"
#include "constant.h"
#include "utils/msgutils.h"
#include <stdexcept>

ChatLogController::ChatLogController() {
    db = std::make_shared<ChatLogModel>();
}

int64_t ChatLogController::createChatLog( ChatLog &chatLog) {
    return db->createChatLog(chatLog);
}

void ChatLogController::createChatLog( std::vector<ChatLog> &chatLogs) {
    db->createChatLog(chatLogs);
}

std::vector<ChatLog> ChatLogController::findChatLog(
    const std::string &fromUserId, const std::string &toUserId,
    const std::string &groupId, const int64_t seqStart, const int64_t seqEnd,
    const int msgType) {
    if (msgType == SINGLE_CHAT_TYPE) {
        auto conversaionId = getConversationIdForSingle(fromUserId, toUserId);
        return db->findChatLog(conversaionId, seqStart, seqEnd);
    } else {
        auto conversaionId = getConversationIdForGroup(groupId);
        return db->findChatLog(conversaionId, seqStart, seqEnd);
    }
    throw std::invalid_argument("msgType is invalid");
}