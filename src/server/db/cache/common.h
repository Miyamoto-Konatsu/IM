#ifndef COMMON_CACHE_H
#define COMMON_CACHE_H

#include "cpp_redis/cpp_redis"
#include <cpp_redis/core/client.hpp>
#include <memory>
#include <string>
#include "config/config.h"
#include <json.hpp>
#include <vector>

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

using json = nlohmann::json;

template <typename T>
T getCache(const std::string &key, std::shared_ptr<Cache> redisClient,
           int expire, const std::function<T()> fn) {
    bool write = false;
    auto reply = redisClient->get(key);
    if (reply.ok() && reply.is_string()) {
        return json::parse(reply.as_string()).get<T>();
    }
    T t = fn();
    std::string v = json(t).dump();
    redisClient->set(key, v);
    return t;
}

template <typename T>
std::vector<T> batchGetCache(
    const std::vector<std::string> &keys, std::shared_ptr<Cache> redisClient,
    int expire,
    const std::function<std::string(T, const std::vector<std::string>)>
        keyIndexFn,
    const std::function<std::shared_ptr<T>()> fn) {
    auto reply = redisClient->batchGet(keys);
    std::vector<T> result;
    if (reply.ok() && reply.is_bulk_string()) {
        bool isFound = true;
        for (auto &item : reply.as_array()) {
            if (item.is_string()) {
                result.push_back(json::parse(reply.as_string()).get<T>());
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
        keyValues.push_back(
            std::make_pair(keyIndexFn(item, keys), json(item).dump()));
    }
    auto setReply = redisClient->batchSet(keyValues);
    if (setReply.ko()) {
        std::cout << "batchSet error: " << setReply.error() << std::endl;
    }
    return result;
}

#endif