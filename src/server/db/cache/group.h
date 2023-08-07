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
    static const std::string GROUP_LIST_PREFIX;
    static const std::string GROUP_ID_LIST_PREFIX;
    GroupCache(std::shared_ptr<GroupModel>);

    virtual ~GroupCache() = default;

    GroupInfoStruct getGroup(const std::string &groupId);

    std::vector<GroupMember> getGroupMember(const std::string &groupId);

    std::vector<unsigned long> getGroupMemberIds(const std::string &groupId);

    GroupMember getGroupOwner(const std::string &groupId);

    uint64_t getGroupMemberIdsHash(const std::string &groupId);

    std::vector<std::string> getGroupIdList(const std::string &userId);

    std::vector<ChatGroup> getGroupList(const std::string &userId);

    void deleteGroupList(const std::string &userId);

    void deleteGroupInfo(const std::string &groupId);

    std::string getGroupKey(const std::string &groupId) {
        return GROUP_PREFIX + (groupId);
    }

    std::string getGroupMemberIdsKey(const std::string &groupId) {
        return GROUP_MEMBER_IDS_PREFIX + groupId;
    }

    std::string getGroupMemberIdsHashKey(const std::string &groupId) {
        return GROUP_MEMBER_IDS_HASH_PREFIX + groupId;
    }

    std::string getGroupMemberKey(const std::string &groupId,
                                  const std::string &userId) {
        return GROUP_MEMBER_PREFIX + groupId + ":" + userId;
    }

    std::string getGroupOwnerKey(const std::string &groupId) {
        return GROUP_OWNER_PREFIX + groupId;
    }
    std::string getGroupListKey(const std::string &userId) {
        return GROUP_LIST_PREFIX + userId;
    }

    std::string getGroupIdListKey(const std::string &userId) {
        return GROUP_ID_LIST_PREFIX + userId;
    }

private:
    std::shared_ptr<GroupModel> db;
};

#endif