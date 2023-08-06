#ifndef GROUP_CACHE_H
#define GROUP_CACHE_H

#include <cstdint>
#include <memory>
#include "common.h"
#include "relation/group_model.h"
#include "table/group.h"

class GroupCache : public Cache {
public:
    static const std::string GROUP_PREFIX;
    static const std::string GROUP_MEMBER_IDS_PREFIX;
    static const std::string GROUP_MEMBER_IDS_HASH_PREFIX;
    static const std::string GROUP_MEMBER_PREFIX;
    static const std::string GROUP_OWNER_PREFIX;

    GroupCache(std::shared_ptr<GroupModel>);

    virtual ~GroupCache() = default;

    ChatGroup getGroup(const unsigned long &groupId);

    std::vector<GroupMember> getGroupMembers(const unsigned long &groupId);

    std::vector<std::string> getGroupMemberIds(const unsigned long &groupId);

    GroupMember getGroupOwner(const unsigned long &groupId);

    uint64_t getGroupMemberIdsHash(const unsigned long &groupId);

    std::string getGroupKey(const unsigned long &groupId) {
        return GROUP_PREFIX + std::to_string(groupId);
    }

    std::string getGroupMemberIdsKey(const unsigned long &groupId) {
        return GROUP_MEMBER_IDS_PREFIX + std::to_string(groupId);
    }

    std::string getGroupMemberIdsHashKey(const unsigned long &groupId) {
        return GROUP_MEMBER_IDS_HASH_PREFIX + std::to_string(groupId);
    }

    std::string getGroupMemberKey(const unsigned long &groupId,
                                  const std::string &userId) {
        return GROUP_MEMBER_PREFIX + std::to_string(groupId) + ":" + userId;
    }

    std::string getGroupOwnerKey(const unsigned long &groupId) {
        return GROUP_OWNER_PREFIX + std::to_string(groupId);
    }

private:
    std::shared_ptr<GroupModel> db;
};

#endif