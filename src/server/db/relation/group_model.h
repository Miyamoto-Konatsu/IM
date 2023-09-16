#ifndef GROUP_RELATION_H
#define GROUP_RELATION_H
#include <memory>
#include <odb/database.hxx>
#include <odb/query.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>
#include <odb/mysql/database.hxx>
#include <string>
#include <vector>

#include "table/group-odb.hxx"
#include "table/group.h"
#include "table/user.h"
#include "utils.h"
#include "common.h"
#include "json.hpp"
#include "cache/common.h"

using json = nlohmann::json;
struct GroupInfoStruct {
    ChatGroup group;
    std::vector<GroupMember> members;
};

class GroupModel {
public:
    GroupModel() : db(getDB()) {
    }

    // 创建 Group 对象
    void createGroup(ChatGroup &group, const std::string &ownerId) {
        odb::session s;
        odb::transaction t(db->begin());
        auto existingGroup = db->query_one(odb::query<ChatGroup>(
            odb::query<ChatGroup>::groupId == group.groupId()));
        if (existingGroup) {
            throw DatabaseLookupError("Group already exists");
        }
        auto id = db->persist(group); // 将对象插入数据库
        std::shared_ptr<ChatGroup> groupPtr(db->load<ChatGroup>(id));

        std::shared_ptr<User> existingUser(db->query_one(
            odb::query<User>(odb::query<User>::userId == ownerId)));
        if (!existingUser) { throw DatabaseLookupError("User not found"); }

        GroupMember member(existingUser, groupPtr);
        member.roler(GroupMember::GroupMemberRoler::owner);
        db->persist(member);
        t.commit(); // 提交事务
    }

    void joinGroup(const std::string &groupId, const std::string &userId) {
        odb::session s;
        odb::transaction t(db->begin());

        std::shared_ptr<ChatGroup> existingGroup(db->query_one(
            odb::query<ChatGroup>(odb::query<ChatGroup>::groupId == groupId)));
        if (!existingGroup) { throw DatabaseLookupError("Group not exists"); }

        std::shared_ptr<User> existingUser(db->query_one(
            odb::query<User>(odb::query<User>::userId == userId)));
        if (!existingUser) { throw DatabaseLookupError("User not found"); }

        std::shared_ptr<GroupMember> existingGroupMember(
            db->query_one(odb::query<GroupMember>(
                odb::query<GroupMember>::user->userId == userId
                && odb::query<GroupMember>::group->groupId == groupId)));
        if (existingGroupMember) {
            throw DatabaseLookupError("User already in group");
        }
        GroupMember member(existingUser, existingGroup);
        member.roler(GroupMember::GroupMemberRoler::member);
        db->persist(member);
        t.commit(); // 提交事务
    }
    // 查询 Group 对象
    GroupInfoStruct findGroup(const std::string &groupId) {
        odb::session s;
        odb::transaction t(db->begin());
        odb::query<ChatGroup> query(odb::query<ChatGroup>::groupId == groupId);
        ChatGroup group;

        auto isFound = db->query_one(query, group);
        if (!isFound) { throw DatabaseLookupError("Group not found"); }

        auto queryMember = odb::query<GroupMember>(
            odb::query<GroupMember>::group->id == group.id());
        std::vector<GroupMember> members;
        auto queryResult = db->query(queryMember);
        for (auto &item : queryResult) { members.push_back(std::move(item)); }
        t.commit(); // 提交事务
        return {group, members};
    }

    std::vector<std::string> findGroupMemberIds(const std::string &groupId) {
        odb::transaction t(db->begin());
        odb::query<ChatGroup> queryGroup(odb::query<ChatGroup>::groupId
                                         == groupId);
        ChatGroup group;

        auto isFound = db->query_one(queryGroup, group);
        if (!isFound) { throw DatabaseLookupError("Group not found"); }

        odb::query<GroupMember> queryMember(odb::query<GroupMember>::group
                                            == group.id());
        std::vector<std::string> result;

        auto queryGroupResult = db->query(queryMember);
        for (auto &item : queryGroupResult) {
            result.push_back(item.user()->userId());
        }
        t.commit();
        return result;
    }

    // return group id list
    std::vector<std::string> findGroupIdList(const std::string &userId) {
        odb::session s;
        odb::transaction t(db->begin());
        std::shared_ptr<User> existingUser(db->query_one(
            odb::query<User>(odb::query<User>::userId == userId)));
        if (!existingUser) { throw DatabaseLookupError("User not found"); }
        auto groupMembers = db->query<GroupMember>(
            odb::query<GroupMember>::user->id == existingUser->id());
        std::vector<std::string> result;
        for (auto &item : groupMembers) {
            result.push_back(item.group()->groupId());
        }
        t.commit();
        return result;
    }

    std::vector<ChatGroup> findGroupList(const std::string &userId) {
        odb::session s;
        odb::transaction t(db->begin());
        std::shared_ptr<User> existingUser(db->query_one(
            odb::query<User>(odb::query<User>::userId == userId)));
        if (!existingUser) { throw DatabaseLookupError("User not found"); }
        auto groupMembers = db->query<GroupMember>(
            odb::query<GroupMember>::user->id == existingUser->id());
        std::vector<ChatGroup> result;
        for (auto &item : groupMembers) { result.push_back(*item.group()); }
        t.commit();
        return result;
    }

private:
    std::shared_ptr<odb::database> db;
};
#endif