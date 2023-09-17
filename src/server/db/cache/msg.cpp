#include "msg.h"
#include "cpp_redis/core/reply.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

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

void MsgCache::setHasReadSeqs(
    const std::string &conversationId,
    const std::unordered_map<std::string, int64_t> &userHasRead) {
    std::unordered_map<std::string, std::future<cpp_redis::reply>> hasReadSeqs;
    for (auto &user : userHasRead) {
        auto key = "HasReadSeq:" + conversationId + ":" + user.first;
        auto get = client.get(key);
        hasReadSeqs[key] = std::move(get);
    }
    client.commit();
    for (auto &p : hasReadSeqs) {
        auto reply = p.second.get();
        if (reply.ko()) { throw std::runtime_error("setHasReadSeqs failed"); }
        int64_t hasReadSeqOld = 0;
        if (reply.is_null()) {
        } else if (reply.is_string()) {
            hasReadSeqOld = stoi(reply.as_string());
        } else {
            // throw std::runtime_error("setHasReadSeqs failed");
        }
        if (hasReadSeqOld < userHasRead.at(p.first)) {
            client.set(p.first, std::to_string(userHasRead.at(p.first)));
        }
    }
    client.commit();
}

std::pair<int64_t, int64_t>
MsgCache::getHasReadSeqAndMaxSeq(const std::string &conversationId,
                                 const std::string &userid) {
    auto key = "HasReadSeq:" + conversationId + ":" + userid;
    auto get = client.get(key);
    client.commit();
    auto res = get.get();
    if (res.ko()) { throw std::runtime_error("getHasReadSeqAndMaxSeq failed"); }
    int64_t hasReadSeq = -1;
    if (res.is_null()) {
        hasReadSeq = 0;
    } else if (res.is_string()) {
        hasReadSeq = stoi(res.as_string());
    } else {
        throw std::runtime_error("getHasReadSeqAndMaxSeq failed");
    }
    auto maxSeq = getConversationMaxId(conversationId);
    return {hasReadSeq, maxSeq};
}