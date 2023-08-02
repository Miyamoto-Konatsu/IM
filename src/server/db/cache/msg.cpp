#include "msg.h"

MsgCache::MsgCache() {
}

MsgCache::~MsgCache() {
}

int64_t MsgCache::getConversationMaxId(const std::string &key) {
    auto get = client.get(getConversationIdSeqKey(key));
    client.commit();
    auto res = get.get();
    if (res.ko()) { throw std::runtime_error("getConversationMaxId failed"); }
    std::cout << key << ' ' << res << std::endl;
    if (res.is_null())
        return -1;
    else if (res.is_string())
        return stoi(res.as_string());
    else { throw std::runtime_error("getConversationMaxId failed"); }
}

bool MsgCache::setConversationMaxId(const std::string &key, int64_t id) {
    auto set = client.set(getConversationIdSeqKey(key), std::to_string(id));
    client.sync_commit();
    auto res = set.get();
    if (res.ko()) { throw std::runtime_error("setConversationMaxId failed"); }
    return res.ok();
}

std::string
MsgCache::getConversationIdSeqKey(const std::string &conversationId) {
    return conversationId + ":seq";
}