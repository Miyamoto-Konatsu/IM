#ifndef GROUP_CLIENT_H
#define GROUP_CLIENT_H
#include "group.grpc.pb.h"
#include "group.pb.h"
#include "grpcpp/grpcpp.h"
#include <grpcpp/client_context.h>
#include <grpcpp/support/status.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using ServerRpc::group::createGroupReq;
using ServerRpc::group::createGroupResp;
using ServerRpc::group::Group;
using ServerRpc::group::joinGroupReq;
using ServerRpc::group::joinGroupResp;
using ServerRpc::group::getGroupInfoResp;
using ServerRpc::group::getGroupInfoReq;
using ServerRpc::group::getGroupListReq;
using ServerRpc::group::getGroupListResp;
using ServerRpc::group::getGroupMemberReq;
using ServerRpc::group::getGroupMemberResp;

class GroupClient {
public:
    GroupClient(std::shared_ptr<Channel> channel) :
        stub_(Group::NewStub(channel)) {
    }
    ~GroupClient(){}
    GroupClient(const GroupClient &) = delete;
    GroupClient &operator=(const GroupClient &) = delete;

    Status createGroup(const createGroupReq &request,
                       createGroupResp &response) {
        ClientContext context;
        return stub_->createGroup(&context, request, &response);
    }

    Status joinGroup(const joinGroupReq &request, joinGroupResp &response) {
        ClientContext context;
        return stub_->joinGroup(&context, request, &response);
    }

    Status getGroupInfo(const getGroupInfoReq &request,
                        getGroupInfoResp &response) {
        ClientContext context;
        return stub_->getGroupInfo(&context, request, &response);
    }

    Status getGroupList(const getGroupListReq &request,
                        getGroupListResp &response) {
        ClientContext context;
        return stub_->getGroupList(&context, request, &response);
    }

    Status getGroupMember(const getGroupMemberReq &request,
                          getGroupMemberResp &response) {
        ClientContext context;
        return stub_->getGroupMember(&context, request, &response);
    }
private:
    std::unique_ptr<Group::Stub> stub_;
};
#endif