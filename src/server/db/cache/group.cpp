#include "group.h"
#include "cache/common.h"
#include "relation/group_model.h"
#include "table/group.h"
#include <cstdint>
#include <cstring>
#include <functional>
#include <vector>
#include <random>

const std::string GroupCache::GROUP_PREFIX = "group:";
const std::string GroupCache::GROUP_MEMBER_IDS_PREFIX = "group_member_ids:";
const std::string GroupCache::GROUP_MEMBER_IDS_HASH_PREFIX =
    "group_member_ids_hash:";
const std::string GroupCache::GROUP_MEMBER_PREFIX = "group_member:";
const std::string GroupCache::GROUP_OWNER_PREFIX = "group_owner:";
const std::string GroupCache::GROUP_LIST_PREFIX = "group_list:";
const std::string GroupCache::GROUP_ID_LIST_PREFIX = "group_id_list:";
inline void from_json(const json &j, ChatGroup &s) {
    s.groupName(j.at("groupName").get<std::string>());
    s.id_ = (j.at("id").get<unsigned long>());
    s.groupId(j.at("groupId").get<std::string>());
}

inline void to_json(nlohmann::json &j, const ChatGroup &s) {
    j["id"] = s.id();
    j["groupId"] = s.groupId();
    j["groupName"] = s.groupName();
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

inline void to_json(nlohmann::json &j, const GroupInfoStruct &groupInfo) {
    j["group"] = groupInfo.group;
    j["members"] = groupInfo.members;
}

inline void from_json(const nlohmann::json &j, GroupInfoStruct &groupInfo) {
    j.at("group").get_to(groupInfo.group);
    j.at("members").get_to(groupInfo.members);
}

GroupCache::GroupCache(std::shared_ptr<GroupModel> db) : db(db) {
}

GroupInfoStruct GroupCache::getGroup(const std::string &groupId) {
    std::string key = getGroupKey(groupId);
    std::function<GroupInfoStruct()> fn = [&, this]() {
        auto group = this->db->findGroup(groupId);
        return group;
    };
    return getCache(key, shared_from_this(), 10, std::move(fn));
}

std::vector<std::string>
GroupCache::getGroupMemberIds(const std::string &groupId) {
    std::string key = getGroupMemberIdsKey(groupId);
    std::function<std::vector<std::string>()> fn = [&, this]() {
        auto members = this->db->findGroupMemberIds(groupId);
        return members;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

uint64_t GroupCache::getGroupMemberIdsHash(const std::string &groupId) {
    std::string key = getGroupMemberIdsHashKey(groupId);
    std::function<uint64_t()> fn = [&, this]() {
        auto userIds = this->getGroupMemberIds(groupId);

        std::random_device rd;
        std::mt19937 generator(rd()); // 使用 Mersenne Twister 引擎
        // 定义随机数分布范围
        int min = 1;
        uint64_t max = UINT64_MAX;
        std::uniform_int_distribution<uint64_t> distribution(min, max);
        // 生成随机整数
        uint64_t hash = 0;
        auto hashfn = std::hash<std::string>{};
        for (auto &userId : userIds) {
            uint64_t randomValue = distribution(generator);
            hash += hashfn(userId) + randomValue;
        }
        return hash;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

std::vector<std::string> GroupCache::getGroupIdList(const std::string &userId) {
    std::string key = getGroupIdListKey(userId);
    std::function<std::vector<std::string>()> fn = [&, this]() {
        auto groups = this->db->findGroupIdList(userId);
        return groups;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

std::vector<ChatGroup> GroupCache::getGroupList(const std::string &userId) {
    std::string key = getGroupListKey(userId);
    std::function<std::vector<ChatGroup>()> fn = [&, this]() {
        auto groups = this->db->findGroupList(userId);
        return groups;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

void GroupCache::deleteGroupList(const std::string &userId) {
    std::string key = getGroupListKey(userId);
    del(key);
}

void GroupCache::deleteGroupInfo(const std::string &groupId) {
    std::string key = getGroupKey(groupId);
    del(key);
}

void GroupCache::deleteGroupMemberIds(const std::string &groupId) {
    std::string key = getGroupMemberIdsKey(groupId);
    del(key);
}

void GroupCache::deleteGroupMemberIdsHash(const std::string &groupId) {
    std::string key = getGroupMemberIdsHashKey(groupId);
    del(key);
}