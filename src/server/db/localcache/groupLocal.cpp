#include "groupLocal.h"
#include "group.pb.h"
#include "table/conversation.h"
#include <grpcpp/support/status.h>
#include <memory>
#include <mutex>
#include <resolv.h>
#include <vector>

std::vector<std::string>
GroupLocalCache::getGroupMemberIds(const std::string &groupId) {
    ServerRpc::group::getGroupMemberIdHashReq req;
    req.set_groupid(groupId);
    ServerRpc::group::getGroupMemberIdHashResp resp;
    grpc::Status status = groupClient_.getGroupMemberIdHash(&req, &resp);
    if (!status.ok()) { throw std::runtime_error("getGroupMemberIds failed"); }
    std::unique_lock<std::mutex> lock(mtx_);
    if (this->groupMemberIdMap_.find(groupId) != this->groupMemberIdMap_.end()
        && this->groupMemberIdMap_[groupId].hash == resp.groupmemberidhash()) {
        return this->groupMemberIdMap_[groupId].memberIds;
    }
    ServerRpc::group::getGroupMemberIdReq req2;
    req2.set_groupid(groupId);
    ServerRpc::group::getGroupMemberIdResp resp2;
    status = groupClient_.getGroupMemberId(&req2, &resp2);
    if (!status.ok()) {
        lock.unlock();
        throw std::runtime_error("getGroupMemberIds failed");
    }
    this->groupMemberIdMap_[groupId].memberIds.clear();
    this->groupMemberIdMap_[groupId].memberIds.reserve(resp2.groupmemberids_size());
    for (auto &id : resp2.groupmemberids()) {
        this->groupMemberIdMap_[groupId].memberIds.push_back(id);
    }
    this->groupMemberIdMap_[groupId].hash = resp.groupmemberidhash();
    return this->groupMemberIdMap_[groupId].memberIds;
}