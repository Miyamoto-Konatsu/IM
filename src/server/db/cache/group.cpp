#include "group.h"
#include "cache/common.h"
#include "table/group.h"
#include <cstdint>
#include <functional>
#include <vector>

const std::string GroupCache::GROUP_PREFIX = "group:";
const std::string GroupCache::GROUP_MEMBER_IDS_PREFIX = "group_member_ids:";
const std::string GroupCache::GROUP_MEMBER_IDS_HASH_PREFIX =
    "group_member_ids_hash:";
const std::string GroupCache::GROUP_MEMBER_PREFIX = "group_member:";
const std::string GroupCache::GROUP_OWNER_PREFIX = "group_owner:";

GroupCache::GroupCache(std::shared_ptr<GroupModel> db) : db(db) {
}

ChatGroup GroupCache::getGroup(const unsigned long &groupId) {
    std::string key = getGroupKey(groupId);
    std::function<ChatGroup()> fn = [&, this]() {
        auto group = this->db->findGroup(groupId);
        return group;
    };
    return getCache(key, shared_from_this(), 10, std::move(fn));
}

std::vector<GroupMember>
GroupCache::getGroupMembers(const unsigned long &groupId) {
    auto ids = getGroupMemberIds(groupId);

    std::function<std::vector<GroupMember>()> fn = [&, this]() {
        auto members = this->db->findGroupMembers(groupId);
        return members;
        // std::vector<GroupMemberRpc> membersRpc;
        // for (auto &member : members) {
        //     GroupMemberRpc memberRpc;
        //     copyField(*memberRpc.mutable_user(), *member.user());
        //     memberRpc.set_groupid(member.group()->id());
        //     if (member.roler() == GroupMember::GroupMemberRoler::owner) {
        //         memberRpc.groupMemberRole_Name(
        //             GroupMemberRpc::groupMemberRole::
        //                 groupMember_groupMemberRole_owner);
        //     } else if (member.roler()
        //                == GroupMember::GroupMemberRoler::member) {
        //         memberRpc.groupMemberRole_Name(
        //             GroupMemberRpc::groupMemberRole::
        //                 groupMember_groupMemberRole_member);
        //     }
        // }
        // return membersRpc;
    };

    std::function<std::string(const GroupMember &)> keyFn =
        [this](const GroupMember &groupMember) {
            return getGroupMemberKey(groupMember.id(),
                                     groupMember.user()->userId());
        };

    std::function<int(const GroupMember &, const std::vector<std::string>)>
        indexFn = [this](const GroupMember &groupMember,
                         const std::vector<std::string> keys) {
            for (int i = 0; i < keys.size(); i++) {
                if (keys[i]
                    == getGroupMemberKey(groupMember.id(),
                                         groupMember.user()->userId())) {
                    return i;
                }
            }
            return -1;
        };

    return batchGetCache(ids, shared_from_this(), 100, keyFn, indexFn,
                         std::move(fn));
}

std::vector<std::string>
GroupCache::getGroupMemberIds(const unsigned long &groupId) {
    std::string key = getGroupMemberIdsKey(groupId);
    std::function<std::vector<std::string>()> fn = [&, this]() {
        auto members = this->db->findGroupMemberIds(groupId);
        return members;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

uint64_t GroupCache::getGroupMemberIdsHash(const unsigned long &groupId) {
    std::string key = getGroupMemberIdsHashKey(groupId);
    std::function<uint64_t()> fn = [&, this]() {
        auto userIds = this->getGroupMemberIds(groupId);
        uint64_t hash = 0;
        for (auto &userId : userIds) {
            hash += std::hash<std::string>{}(userId);
        }
        return hash;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}

GroupMember GroupCache::getGroupOwner(const unsigned long &groupId) {
    std::string key = getGroupOwnerKey(groupId);
    std::function<GroupMember()> fn = [&, this]() {
        auto owner = this->db->findGroupOwner(groupId);
        return owner;
        // GroupMemberRpc ownerRpc;
        // copyField(*ownerRpc.mutable_user(), *owner.user());
        // ownerRpc.set_groupid(owner.group()->id());
        // if (owner.roler() == GroupMember::GroupMemberRoler::owner) {
        //     ownerRpc.groupMemberRole_Name(
        //         GroupMemberRpc::groupMemberRole::
        //             groupMember_groupMemberRole_owner);
        // } else if (owner.roler() == GroupMember::GroupMemberRoler::member) {
        //     ownerRpc.groupMemberRole_Name(
        //         GroupMemberRpc::groupMemberRole::
        //             groupMember_groupMemberRole_member);
        // }
        // return ownerRpc;
    };
    return getCache(key, shared_from_this(), 100, std::move(fn));
}