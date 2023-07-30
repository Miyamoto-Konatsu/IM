#ifndef COMMON_CACHE_H
#define COMMON_CACHE_H

#include "cpp_redis/cpp_redis"
#include <cpp_redis/core/client.hpp>
#include <memory>
#include <string>
#include "config/config.h"
#include <json.hpp>
#include <vector>
#include "conversation.pb.h"
#include "table/conversation.h"

class Cache : public std::enable_shared_from_this<Cache> {
public:
    Cache();

    virtual ~Cache();

    cpp_redis::reply set(const std::string &key, const std::string &value);

    cpp_redis::reply get(const std::string &key);

    cpp_redis::reply del(const std::string &key);

    cpp_redis::reply
    batchSet(std::vector<std::pair<std::string, std::string>> &keyValues);

    cpp_redis::reply batchDel(const std::vector<std::string> &keys);

    cpp_redis::reply batchGet(const std::vector<std::string> &keys);

protected:
    cpp_redis::client client;
};

using ConversationRpc = ServerRpc::conversation::conversation;
void copyField(Conversation &conversion, const ConversationRpc &other);
void copyField(ConversationRpc &conversion, const Conversation &other);

// Conversation serialization
inline void to_json(nlohmann::json &j, const Conversation &s) {
    j["conversaionId"] = s.conversationId();
    j["conversationType"] = s.conversationType();
    j["groupId"] = s.groupId();
    j["maxSeq"] = s.maxSeq();
    j["minSeq"] = s.minSeq();
    j["ownerId"] = s.ownerId();
    j["toUserId"] = s.toUserId();
}

inline void from_json(const nlohmann::json &j, Conversation &s) {
    s.conversationId(j.at("conversaionId").get<std::string>());
    s.conversationType(j.at("conversationType").get<u_short>());
    s.groupId(j.at("groupId").get<std::string>());
    s.maxSeq(j.at("maxSeq").get<uint64>());
    s.minSeq(j.at("minSeq").get<uint64>());
    s.ownerId(j.at("ownerId").get<std::string>());
    s.toUserId(j.at("toUserId").get<std::string>());
}
using json = nlohmann::json;

template <typename T>
T getCache(const std::string &key, std::shared_ptr<Cache> redisClient,
           int expire, const std::function<T()> fn) {
    auto reply = redisClient->get(key);
    if (reply.ok() && reply.is_string()) {
        T t = json::parse(reply.as_string());
        return t;
    }
    T t = fn();
    json j = t;
    redisClient->set(key, j.dump());
    return t;
}

template <typename T>
std::vector<T> batchGetCache(
    const std::vector<std::string> &keys, std::shared_ptr<Cache> redisClient,
    int expire, const std::function<std::string(const T &)> &keyFn,
    const std::function<int(const T &, const std::vector<std::string>)>
        &indexFn,
    const std::function<std::vector<T>()> &fn) {
    auto reply = redisClient->batchGet(keys);
    std::vector<T> result;
    if (reply.ok() && reply.is_array()) {
        bool isFound = true;
        if (reply.as_array().size() != keys.size()) {
            isFound = false;
        } else {
            result.reserve(keys.size());
            result.resize(keys.size());
            for (auto &item : reply.as_array()) {
                if (item.is_string()) {
                    T t = json::parse(item.as_string());
                    int index = indexFn(t, keys);
                    result[index] = t;
                } else {
                    isFound = false;
                    break;
                }
            }
            if (isFound) { return result; }
            result.clear();
        }
    }

    result = fn();

    std::vector<std::pair<std::string, std::string>> keyValues;
    for (auto &item : result) {
        json j = item;
        keyValues.push_back(std::make_pair(keyFn(item), j.dump()));
    }
    auto setReply = redisClient->batchSet(keyValues);
    if (setReply.ko()) {
        std::cout << "batchSet error: " << setReply.error() << std::endl;
    }
    return result;
}

#endif