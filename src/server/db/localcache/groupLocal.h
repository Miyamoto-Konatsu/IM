#pragma once

#include "group/group.h"
#include "table/conversation.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
struct GroupMemberIDsHash {
    uint64_t hash;
    std::vector<std::string> memberIds;
};
class GroupLocalCache {
public:
    std::vector<std::string> getGroupMemberIds(const std::string &groupId);

    GroupLocalCache() : groupClient_(GroupClient::getGroupClient()) {
    }
    ~GroupLocalCache() = default;
private:
    GroupClient groupClient_;
    std::unordered_map<std::string, GroupMemberIDsHash> groupMemberIdMap_;
    std::mutex mtx_;
};