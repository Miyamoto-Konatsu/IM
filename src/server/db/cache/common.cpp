#include "common.h"
#include "json.hpp"
#include <vector>

Cache::Cache() {
    auto config = getConfig();
    auto redis_config = config["redis"];
    auto host = redis_config["host"].as<std::string>();
    auto port = redis_config["port"].as<int>();
    client.connect(host, port,
                   [](const std::string &host, std::size_t port,
                      cpp_redis::client::connect_state status) {
                       if (status
                           == cpp_redis::client::connect_state::dropped) {
                           std::cout << "client disconnected from " << host
                                     << ":" << port << std::endl;
                       }
                   });
}

Cache::~Cache() {
    client.disconnect();
}

cpp_redis::reply Cache::set(const std::string &key, const std::string &value) {
    auto set = client.set(key, value);
    client.sync_commit();
    return set.get();
}

cpp_redis::reply Cache::get(const std::string &key) {
    auto get = client.get(key);
    client.sync_commit();
    return get.get();
}

cpp_redis::reply Cache::del(const std::string &key) {
    auto del = client.del({key});
    client.sync_commit();
    return del.get();
}

cpp_redis::reply
Cache::batchSet(std::vector<std::pair<std::string, std::string>> &keyValues) {
    auto mset = client.mset(keyValues);
    client.commit();
    return mset.get();
}

cpp_redis::reply Cache::batchDel(const std::vector<std::string> &keys) {
    auto del = client.del(keys);
    client.commit();
    return del.get();
}

cpp_redis::reply Cache::batchGet(const std::vector<std::string> &keys) {
    auto mget = client.mget(keys);
    client.commit();
    return mget.get();
}

void copyField(Conversation &conversion, const ConversationRpc &other) {
    conversion.conversationId(other.conversationid());
    conversion.conversationType(other.conversationtype());
    conversion.groupId(other.groupid());
    conversion.maxSeq(other.maxseq());
    conversion.minSeq(other.minseq());
    conversion.ownerId(other.ownerid());
    conversion.toUserId(other.touserid());
}

void copyField(ConversationRpc &conversion, const Conversation &other) {
    conversion.set_conversationid(other.conversationId());
    conversion.set_conversationtype(other.conversationType());
    conversion.set_groupid(other.groupId());
    conversion.set_maxseq(other.maxSeq());
    conversion.set_minseq(other.minSeq());
    conversion.set_ownerid(other.ownerId());
    conversion.set_touserid(other.toUserId());
}

void copyField(User &user, const UserRpc &other) {
    user.userId(other.userid());
    user.nickname(other.nickname());
    user.password(other.password());
}

void copyField(UserRpc &user, const User &other) {
    user.set_userid(other.userId());
    user.set_nickname(other.nickname());
    user.set_password(other.password());
}