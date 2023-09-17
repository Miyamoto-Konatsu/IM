#include "msgutils.h"
#include "constant.h"
#include "constant/msg.h"
std::string getSingleChatKey(const std::string &from, const std::string &to) {
    if (from > to) return "mq_sc:" + to + "_" + from;
    return "mq_sc:" + from + "_" + to;
}

std::string getGroupChatKey(const std::string &groupId) {
    return "mq_gc:" + groupId;
}

std::string getConversationIdForSingle(const std::string &from,
                                       const std::string &to) {
    static const std::string prefix = "conid_sc:";
    if (from > to) return prefix + to + "_" + from;
    return prefix + from + "_" + to;
}

std::string getConversationIdForGroup(const std::string &groupId) {
    return "conid_gc:" + groupId;
}

std::string getConversationId(const ServerRpc::msg::msg &msg) {
    if (msg.msgtype() == SINGLE_CHAT_TYPE) {
        return getConversationIdForSingle(msg.fromuserid(), msg.touserid());
    } else if (msg.msgtype() == GROUP_CHAT_TYPE) {
        return "conid_gc:" + msg.groupid();
    } else {
        throw std::invalid_argument("invalid msg type");
    }
}