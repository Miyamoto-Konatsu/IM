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
using ServerRpc::group::getGroupMemberIdReq;
using ServerRpc::group::getGroupMemberIdResp;
using ServerRpc::group::getGroupMemberIdHashReq;
using ServerRpc::group::getGroupMemberIdHashResp;
class GroupClient {
public:
    GroupClient(std::shared_ptr<Channel> channel) :
        stub_(Group::NewStub(channel)) {
    }
    
    ~GroupClient() {
    }

    Status createGroup(const createGroupReq *request,
                       createGroupResp *response) {
        ClientContext context;
        return stub_->createGroup(&context, *request, response);
    }

    Status joinGroup(const joinGroupReq *request, joinGroupResp *response) {
        ClientContext context;
        return stub_->joinGroup(&context, *request, response);
    }

    Status getGroupInfo(const getGroupInfoReq *request,
                        getGroupInfoResp *response) {
        ClientContext context;
        return stub_->getGroupInfo(&context, *request, response);
    }

    Status getGroupList(const getGroupListReq *request,
                        getGroupListResp *response) {
        ClientContext context;
        return stub_->getGroupList(&context, *request, response);
    }

    Status getGroupMemberId(const getGroupMemberIdReq *request,
                          getGroupMemberIdResp *response) {
        ClientContext context;
        return stub_->getGroupMemberId(&context, *request, response);
    }

    Status getGroupMemberIdHash(const getGroupMemberIdHashReq *request,
                              getGroupMemberIdHashResp *response) {
        ClientContext context;
        return stub_->getGroupMemberIdHash(&context, *request, response);
    }

    static GroupClient getGroupClient() {
        return GroupClient(grpc::CreateChannel(
            "localhost:50056", grpc::InsecureChannelCredentials()));
    }

private:
    std::unique_ptr<Group::Stub> stub_;
};
#endif