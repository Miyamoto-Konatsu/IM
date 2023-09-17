#include "msgDatabase.h"
#include "msg.pb.h"
#include "utils/msgutils.h"
#include <cstdint>
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
    std::unordered_map<std::string, int64_t> userHasRead;

    for (auto &msgReq : msgReqs) {
        auto &msg = *msgReq.mutable_msg_data();
        msg.set_seq(++maxId);
        userHasRead[msg.fromuserid()] = maxId;
    }

    if (!msgCache.setConversationMaxId(conversationId, maxId)) {
        std::cerr << "setConversationMaxId failed" << std::endl;
    } else {
        std::cerr << "setConversationMaxId success" << std::endl;
    }

    msgCache.setHasReadSeqs(conversationId, userHasRead);

    return isNewConversation;
}

void MsgDatabase::setHasReadSeq(const std::string &key,
                                const std::string &userid, int64_t seq) {
    msgCache.setHasReadSeqs(key, {{userid, seq}});
}

std::pair<int64_t, int64_t> MsgDatabase::getHasReadSeqAndMaxSeq(
    const std::string &conversationId, const std::string &userid) {
    return msgCache.getHasReadSeqAndMaxSeq(conversationId, userid);
}