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
#include "table/user.h"
#include "user.pb.h"
#include "group.pb.h"
#include "table/conversation.h"
#include "table/group.h"
#include <google/protobuf/util/json_util.h>

using google::protobuf::util::JsonStringToMessage;
using google::protobuf::util::MessageToJsonString;
using google::protobuf::util::JsonPrintOptions;

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

using UserRpc = ServerRpc::user::user;
void copyField(User &user, const UserRpc &other);
void copyField(UserRpc &user, const User &other);

using json = nlohmann::json;

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

inline void to_json(nlohmann::json &j, const ChatGroup &s) {
    j["id"] = s.id();
    j["groupName"] = s.groupName();
}

inline void from_json(const json &j, ChatGroup &s) {
    s.groupName(j.at("groupName").get<std::string>());
    s.id_ = (j.at("id").get<unsigned long>());
}

inline void to_json(nlohmann::json &j, const UserRpc &s) {
    j["userId"] = s.userid();
    j["nickname"] = s.nickname();
    j["password"] = s.password();
}

inline void from_json(const nlohmann::json &j, UserRpc &s) {
    s.set_userid(j.at("userId").get<std::string>());
    s.set_nickname(j.at("nickname").get<std::string>());
    s.set_password(j.at("password").get<std::string>());
}

using GroupMemberRpc = ServerRpc::group::groupMember;
inline void to_json(nlohmann::json &j, const GroupMemberRpc &s) {
    // std::string str;
    // static JsonPrintOptions options;
    // options.always_print_primitive_fields = true;
    // auto status = MessageToJsonString(s, &str, options);
    // if (!status.ok()) { throw std::runtime_error("parse json error"); }
    // j = json::parse(str);
}

inline void from_json(const nlohmann::json &j, GroupMemberRpc &s) {
    // std::string str = j.dump();
    // auto status = JsonStringToMessage(str, &s);
    // if (!status.ok()) { throw std::runtime_error("parse json error"); }
}

inline void to_json(nlohmann::json &j, const User &s) {
    j["userId"] = s.userId();
    j["nickname"] = s.nickname();
    j["password"] = s.password();
    j["id"] = s.id();
}

inline void from_json(const nlohmann::json &j, User &s) {
    s.userId(j.at("userId").get<std::string>());
    s.nickname(j.at("nickname").get<std::string>());
    s.password(j.at("password").get<std::string>());
    s.id_ = (j.at("id").get<unsigned long>());
}

inline void to_json(nlohmann::json &j, const GroupMember &s) {
    j["id"] = s.id();
    j["user"] = *s.user();
    j["group"] = *s.group();
    j["role"] = s.roler();
}

inline void from_json(const nlohmann::json &j, GroupMember &s) {
    s.id_ = (j.at("id").get<unsigned long>());
    s.roler(j.at("role").get<GroupMember::GroupMemberRoler>());
    s.user(std::make_shared<User>(j.at("user").get<User>()));
    s.group(std::make_shared<ChatGroup>(j.at("group").get<ChatGroup>()));
}
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