#pragma once
#include "relation/chatlog_model.h"

class ChatLogController {
public:
    ChatLogController();
    ~ChatLogController() = default;

    ChatLogController(const ChatLogController &) = delete;
    ChatLogController &operator=(const ChatLogController &) = delete;

    int64_t createChatLog(ChatLog &chatLog);

    void createChatLog(std::vector<ChatLog> &chatLogs);

    std::vector<ChatLog> findChatLog(const std::string &fromUserId,
                                     const std::string &toUserId,
                                     const std::string &groupId,
                                     const int64_t seqStart,
                                     const int64_t seqEnd, const int msgType);

private:
    std::shared_ptr<ChatLogModel> db;
};