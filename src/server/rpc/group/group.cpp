#include "group.h"
#include "muduo/base/Logging.h"
#include <grpcpp/server.h>
#include <math.h>
#include "group.grpc.pb.h"
#include "group.pb.h"

using ServerRpc::group::groupInfo;
using ServerRpc::group::groupMember;

Status GroupServiceImpl::createGroup(ServerContext *context,
                                     const createGroupReq *request,
                                     createGroupResp *response) {
    std::string groupname = request->groupname();
    std::string groupownerId = request->groupownerid();
    try {
        groupDatabase_->createGroup(*request);
    } catch (std::exception &e) {
        LOG_DEBUG << "create group failed. " << e.what()
                  << "groupname: " << groupname
                  << "grouId: " << request->groupid()
                  << "groupownerId: " << groupownerId
                  << request->groupownerid();
        return Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    LOG_DEBUG << "create group success. "
              << "groupname: " << groupname << "grouId: " << request->groupid()
              << "groupownerId: " << groupownerId;
    return Status::OK;
}

Status GroupServiceImpl::joinGroup(ServerContext *context,
                                   const joinGroupReq *request,
                                   joinGroupResp *response) {
    std::string groupid = request->groupid();
    std::string userid = request->userid();
    try {
        groupDatabase_->joinGroup(*request);
    } catch (std::exception &e) {
        LOG_DEBUG << "join group failed. " << e.what() << "groupid: " << groupid
                  << "userid: " << userid;
        return Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    LOG_DEBUG << "join group success. "
              << "groupid: " << groupid << "userid: " << userid;
    return Status::OK;
}
Status GroupServiceImpl::getGroupInfo(ServerContext *context,
                                      const getGroupInfoReq *request,
                                      getGroupInfoResp *response) {
    std::string groupid = request->groupid();
    try {
        auto groupInfoStruct = groupDatabase_->getGroupInfo(groupid);
        const auto &group = groupInfoStruct.group;
        const auto &groupMembers = groupInfoStruct.members;
        groupInfo *groupInfoPtr = new groupInfo();
        groupInfoPtr->set_groupname(group.groupName());
        groupInfoPtr->set_groupid(group.groupId());
        for (auto &member : groupMembers) {
            auto memberRpcPtr = groupInfoPtr->add_groupmembers();
            memberRpcPtr->set_groupid(group.groupId());
            if (member.roler() == GroupMember::GroupMemberRoler::owner) {
                memberRpcPtr->set_role(groupMember::owner);
                groupInfoPtr->set_groupownerid(member.user()->userId());
            } else {
                memberRpcPtr->set_role(groupMember::member);
            }
            memberRpcPtr->mutable_user()->set_userid(member.user()->userId());
            memberRpcPtr->mutable_user()->set_nickname(
                member.user()->nickname());
        }
        response->set_allocated_groupinfo(groupInfoPtr);
    } catch (std::exception &e) {
        LOG_DEBUG << "get group info failed. " << e.what()
                  << "groupid: " << groupid;
        return Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    return Status::OK;
}

Status GroupServiceImpl::getGroupList(ServerContext *context,
                                      const getGroupListReq *request,
                                      getGroupListResp *response) {
    auto userId = request->userid();
    try {
        auto chatGroups = groupDatabase_->getGroupList(userId);
        for (auto &chatGroup : chatGroups) {
            auto groupInfoPtr = response->add_groupinfo();
            groupInfoPtr->set_groupname(chatGroup.groupName());
            groupInfoPtr->set_groupid(chatGroup.groupId());
            // groupInfoPtr->set_groupownerid(chatGroup.groupOwnerId());
        }
    } catch (const exception &e) {
        LOG_DEBUG << "get group list failed. " << e.what()
                  << "userid: " << userId;
        return Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    return Status::OK;
}

// Status GroupServiceImpl::getGroupMember(ServerContext *context,
//                                         const getGroupMemberReq *request,
//                                         getGroupMemberResp *response) {
//     return Status::OK;
// }

GroupServiceImpl::GroupServiceImpl() :
    groupDatabase_(std::make_shared<GroupDatabase>()) {
}

GroupServiceImpl::~GroupServiceImpl() {
}

using grpc::Server;
using grpc::ServerBuilder;

int main() {
    std::string server_address("0.0.0.0:50056");
    GroupServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG_DEBUG << "Server listening on " << server_address;
    server->Wait();
    return 0;
}