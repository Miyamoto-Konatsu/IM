#ifndef GROUP_RPC_H
#define GROUP_RPC_H
#include "group.grpc.pb.h"
#include "group.pb.h"
#include "grpcpp/grpcpp.h"
#include <grpcpp/server.h>
#include <grpcpp/support/status.h>
#include <memory>
#include "controller/groupDatabase.h"
#include "conversation/conversation.h"
using grpc::ServerContext;
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

class GroupServiceImpl : public Group::Service {
public:
    Status createGroup(ServerContext *context, const createGroupReq *request,
                       createGroupResp *response) override;
    Status joinGroup(ServerContext *context, const joinGroupReq *request,
                     joinGroupResp *response) override;
    Status getGroupInfo(ServerContext *context, const getGroupInfoReq *request,
                        getGroupInfoResp *response) override;
    Status getGroupList(ServerContext *context, const getGroupListReq *request,
                        getGroupListResp *response) override;
    Status getGroupMemberId(ServerContext *context,
                            const getGroupMemberIdReq *request,
                            getGroupMemberIdResp *response) override;
    Status getGroupMemberIdHash(ServerContext *context,
                                const getGroupMemberIdHashReq *request,
                                getGroupMemberIdHashResp *response) override;
    GroupServiceImpl();
    ~GroupServiceImpl();

private:
    std::shared_ptr<GroupDatabase> groupDatabase_;
    ConversationClient conversationClient_;
};
#endif