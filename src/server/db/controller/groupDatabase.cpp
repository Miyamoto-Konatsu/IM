#include "groupDatabase.h"
#include "table/group.h"

GroupDatabase::GroupDatabase() {
    groupModel_ = std::make_shared<GroupModel>();
    groupCache_ = std::make_shared<GroupCache>(groupModel_);
}

void GroupDatabase::createGroup(
    const ServerRpc::group::createGroupReq &createGroupReq) {
    ChatGroup group;
    group.groupName(createGroupReq.groupname());
    group.groupId(createGroupReq.groupid());
    groupModel_->createGroup(group, createGroupReq.groupownerid());

    // 需要删除该用户的群列表缓存
    groupCache_->deleteGroupList(createGroupReq.groupownerid());
}

void GroupDatabase::joinGroup(const ServerRpc::group::joinGroupReq &joinReq) {
    auto groupId = joinReq.groupid();
    auto userId = joinReq.userid();
    groupModel_->joinGroup(groupId, userId);

    // 需要删除该用户的群列表缓存
    groupCache_->deleteGroupList(userId);

    // 需要删除该群的群成员缓存
    groupCache_->deleteGroupInfo(groupId);
}

GroupInfoStruct GroupDatabase::getGroupInfo(const std::string &groupId) {
    return groupCache_->getGroup(groupId);
}

std::vector<ChatGroup> GroupDatabase::getGroupList(const std::string &userId) {
    return groupCache_->getGroupList(userId);
}