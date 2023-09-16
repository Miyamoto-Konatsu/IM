#ifndef GROUPDATABASE_H
#define GROUPDATABASE_H

#include "group.pb.h"
#include "cache/group.h"
#include "relation/group_model.h"
#include "table/group.h"
#include <cstdint>
#include <memory>
#include <vector>

class GroupDatabase {
public:
    GroupDatabase();

    virtual ~GroupDatabase() = default;

    // * throw exception if group already exists
    void createGroup(const ServerRpc::group::createGroupReq &createGroupReq);

    // * throw exception if group not exists or user not exists
    void joinGroup(const ServerRpc::group::joinGroupReq &joinReq);

    // std::vector<GroupMember> getGroupMember(const std::string &groupId);

    GroupInfoStruct getGroupInfo(const std::string &groupId);

    std::vector<ChatGroup> getGroupList(const std::string &userId);

    std::vector<std::string> getGroupMemberId(const std::string &groupId);

    uint64_t getGroupMemberIdHash(const std::string &groupId);
private:
    std::shared_ptr<GroupCache> groupCache_;
    std::shared_ptr<GroupModel> groupModel_;
};

#endif