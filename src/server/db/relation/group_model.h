#ifndef GROUP_RELATION_H
#define GROUP_RELATION_H
#include <memory>
#include <odb/database.hxx>
#include <odb/query.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>
#include <odb/mysql/database.hxx>
#include <vector>

#include "table/group-odb.hxx"
#include "table/group.h"
#include "table/user.h"
#include "utils.h"
#include "common.h"

class GroupModel {
public:
    GroupModel() : db(getDB()) {
    }

    // 创建 Group 对象
    void createGroup( ChatGroup &group, const std::string &ownerId) {
        odb::session s;
        odb::transaction t(db->begin());
        auto existingGroup = db->load<ChatGroup>(group.id());
        if (existingGroup) {
            throw DatabaseLookupError("Group already exists");
        }
        db->persist(group); // 将对象插入数据库

        auto groupPtr = std::make_shared<ChatGroup>(std::move(*existingGroup));

        auto existingUser = db->query_one(
            odb::query<User>(odb::query<User>::userId == ownerId));
        if (!existingUser) { throw DatabaseLookupError("User not found"); }
        std::shared_ptr<User> user =
            std::make_shared<User>(std::move(*existingUser));
        GroupMember member(user, groupPtr);
        member.roler(GroupMember::GroupMemberRoler::owner);
        db->persist(member);
        t.commit(); // 提交事务
    }

    // 查询 Group 对象
    ChatGroup findGroup(const unsigned long &groupId) {
        odb::transaction t(db->begin());
        odb::query<ChatGroup> query(odb::query<ChatGroup>::id == groupId);
        ChatGroup result;

        auto isFound = db->query_one(query, result);
        t.commit(); // 提交事务
        if (isFound) {
            return result;
        } else {
            throw DatabaseLookupError("Group not found");
        }
    }

    GroupMember findGroupOwner(const unsigned long &groupId) {
        odb::session s;
        odb::transaction t(db->begin());
        odb::query<GroupMember> query(
            odb::query<GroupMember>::id == groupId
            && odb::query<GroupMember>::roler
                   == GroupMember::GroupMemberRoler::owner);
        GroupMember result;

        auto isFound = db->query_one(query, result);
        t.commit(); // 提交事务
        if (isFound) {
            return result;
        } else {
            throw DatabaseLookupError("Group not found");
        }
    }

    std::vector<GroupMember> findGroupMembers(const unsigned long &groupId) {
        odb::transaction t(db->begin());
        odb::query<GroupMember> query(odb::query<GroupMember>::id == groupId);
        std::vector<GroupMember> result;

        auto queryResult = db->query(query);
        for (auto &item : queryResult) { result.push_back(std::move(item)); }
        t.commit();
        return result;
    }

    std::vector<std::string> findGroupMemberIds(const unsigned long &groupId) {
        odb::transaction t(db->begin());
        odb::query<GroupMember> query(odb::query<GroupMember>::id == groupId);
        std::vector<std::string> result;

        auto queryResult = db->query(query);
        for (auto &item : queryResult) {
            result.push_back(item.user()->userId());
        }
        t.commit();
        return result;
    }

private:
    std::shared_ptr<odb::database> db;
};
#endif