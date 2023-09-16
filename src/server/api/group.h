#ifndef GROUP_API_H
#define GROUP_API_H
#include "api2rpc.h"
#include "group/group.h"
#include "group.pb.h"

class GroupApi : public std::enable_shared_from_this<GroupApi> {
public:
    GroupApi() : groupClient_(GroupClient::getGroupClient()) {
    }

    ~GroupApi() {
    }

    GroupApi(const GroupApi &) = delete;
    GroupApi &operator=(const GroupApi &) = delete;

    void createGroup(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::group::createGroupReq,
                ServerRpc::group::createGroupResp>(
            std::bind(&GroupClient::createGroup, &groupClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void joinGroup(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::group::joinGroupReq,
                ServerRpc::group::joinGroupResp>(
            std::bind(&GroupClient::joinGroup, &groupClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    // void getGroupMember(const HttpRequest &req, HttpResponse &resp) {
    //     api2rpc<ServerRpc::group::getGroupMemberReq,
    //             ServerRpc::group::getGroupMemberResp>(
    //         std::bind(&GroupClient::getGroupMember, &groupClient_,
    //                   std::placeholders::_1, std::placeholders::_2),
    //         req, resp);
    // }

    void getGroupInfo(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::group::getGroupInfoReq,
                ServerRpc::group::getGroupInfoResp>(
            std::bind(&GroupClient::getGroupInfo, &groupClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }

    void getGroupList(const HttpRequest &req, HttpResponse &resp) {
        api2rpc<ServerRpc::group::getGroupListReq,
                ServerRpc::group::getGroupListResp>(
            std::bind(&GroupClient::getGroupList, &groupClient_,
                      std::placeholders::_1, std::placeholders::_2),
            req, resp);
    }
private:
    GroupClient groupClient_;
};

#endif