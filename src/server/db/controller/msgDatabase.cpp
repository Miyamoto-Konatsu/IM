#include "msgDatabase.h"
#include "msg.pb.h"
#include "utils/msgutils.h"
#include <protobuf/message.h>
#include "msg.grpc.pb.h"

MsgDatabase::MsgDatabase() {
}

MsgDatabase::~MsgDatabase() {
}

int64_t MsgDatabase::getConversationMaxId(const std::string &key) {
    return msgCache.getConversationMaxId(key);
}

bool MsgDatabase::setConversationMaxId(const std::string &key, int64_t id) {
    return msgCache.setConversationMaxId(key, id);
}

bool MsgDatabase::batchInsertMsg(std::vector<sendMsgReq> &msgReqs) {
    auto &msg = msgReqs[0].msg_data();
    bool isNewConversation = false;

    auto conversationId = getConversationId(msg);
    int64_t maxId = getConversationMaxId(conversationId);

    if (maxId == -1) {
        isNewConversation = true;
        maxId = 0;
    }

    for (auto &msgReq : msgReqs) {
        auto &msg = *msgReq.mutable_msg_data();
        msg.set_seq(++maxId);
    }

    if (!msgCache.setConversationMaxId(conversationId, maxId)) {
        std::cerr << "setConversationMaxId failed" << std::endl;
    } else {
        std::cerr << "setConversationMaxId success" << std::endl;
    }

    return isNewConversation;
}