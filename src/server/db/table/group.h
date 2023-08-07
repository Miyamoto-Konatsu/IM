#ifndef GROUP_TABLE_H
#define GROUP_TABLE_H
#include <odb/core.hxx>
#include <string>
#include <memory>
#include "user.h"
#include <vector>
using namespace odb::core;

#pragma db object table("Group")
class ChatGroup {
public:
    ChatGroup() {
    }

    ChatGroup(const ChatGroup &group) = default;
    ChatGroup(ChatGroup &&group) = default;
    ChatGroup &operator=(const ChatGroup &group) = default;
    ChatGroup &operator=(ChatGroup &&group) = default;
    //  getter 和 setter 函数
    const std::string &groupName() const {
        return groupName_;
    }

    void groupName(const std::string &groupName) {
        groupName_ = groupName;
    }

    const std::string &groupId() const {
        return groupId_;
    }

    void groupId(const std::string &groupId) {
        groupId_ = groupId;
    }

    const unsigned long &id() const {
        return id_;
    }

public:
    friend class odb::access;

#pragma db id auto
    unsigned long id_;
#pragma db index unique member(groupId_, "(32)")
    std::string groupId_;
#pragma db not_null
    std::string groupName_;
};

#pragma db object table("GroupMember")
class GroupMember {
public:
    enum GroupMemberRoler { owner, member };

public:
    GroupMember() {
    }

    GroupMember(std::shared_ptr<User> user, std::shared_ptr<ChatGroup> group) :
        user_(user), group_(group) {
    }

    GroupMember(const GroupMember &groupMember) = default;

    GroupMember(GroupMember &&groupMember) = default;

    GroupMember &operator=(const GroupMember &groupMember) = default;

    GroupMember &operator=(GroupMember &&groupMember) = default;

    const unsigned long &id() const {
        return id_;
    }

    std::shared_ptr<User> user() const {
        return user_;
    }

    void user(std::shared_ptr<User> user) {
        user_ = user;
    }

    const GroupMemberRoler &roler() const {
        return roler_;
    }

    void roler(const GroupMemberRoler &roler) {
        roler_ = roler;
    }

    std::shared_ptr<ChatGroup> group() const {
        return group_;
    }

    void group(std::shared_ptr<ChatGroup> group) {
        group_ = group;
    }

public:
    friend class odb::access;

#pragma db id auto
    unsigned long id_;

    GroupMemberRoler roler_;

#pragma db not_null index
    std::shared_ptr<User> user_;

#pragma db not_null index
    std::shared_ptr<ChatGroup> group_;
};

#endif