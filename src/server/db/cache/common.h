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

    ~Cache();

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



template <typename NS, typename S>
NS getCache(const std::string &key, std::shared_ptr<Cache> redisClient,
            int expire, const std::function<NS()> fn) {
    bool write = false;
    auto reply = redisClient->get(key);
    if (reply.ok() && reply.is_string()) {
        S s;
        NS ns;
        s.ParseFromString(reply.as_string());
        copyField(ns, s);
        return ns;
    }
    NS ns = fn();
    S s;
    copyField(s, ns);
    redisClient->set(key, s.SerializeAsString());
    return ns;
}

template <typename NS, typename S>
std::vector<NS>
batchGetCache(const std::vector<std::string> &keys,
              std::shared_ptr<Cache> redisClient, int expire,
              const std::function<std::string(const NS &)> keyFn,
              const std::function<std::vector<NS>()> fn) {
    auto reply = redisClient->batchGet(keys);
    std::vector<NS> result;
    if (reply.ok() && reply.is_array()) {
        bool isFound = true;
        for (auto &item : reply.as_array()) {
            if (item.is_string()) {
                S s;
                s.ParseFromString(item.as_string());
                NS ns;
                copyField(ns, s);
                result.push_back(ns);
            } else {
                isFound = false;
                break;
            }
        }
        if (isFound) { return result; }
        result.clear();
    }

    result = fn();
    std::vector<std::pair<std::string, std::string>> keyValues;
    for (auto &item : result) {
        S s;
        copyField(s, item);
        keyValues.push_back(std::make_pair(keyFn(item), s.SerializeAsString()));
    }
    auto setReply = redisClient->batchSet(keyValues);
    if (setReply.ko()) {
        std::cout << "batchSet error: " << setReply.error() << std::endl;
    }
    return result;
}

#endif