#ifndef MSG_DATABASE_H
#define MSG_DATABASE_H
#include "cache/msg.h"
#include "msg.pb.h"
#include <iostream>
#include <memory>
#include "protobuf/message.h"
#include "utils/commonUtils.h"
#include "cache/common.h"
#include "utils/msgutils.h"
#include <atomic>
using ServerRpc::msg::sendMsgReq;

class MsgDatabase {
public:
    MsgDatabase();
    ~MsgDatabase();
    MsgDatabase(const MsgDatabase &) = delete;
    MsgDatabase &operator=(const MsgDatabase &) = delete;
    int64_t getConversationMaxId(const std::string &key);
    bool setConversationMaxId(const std::string &key, int64_t id);

    bool batchInsertMsg(std::vector<sendMsgReq> &msgReqs);

private:
    MsgCache msgCache;
};

#endif