#include "group.h"

Status GroupServiceImpl::createGroup(ServerContext *context,
                                     const createGroupReq *request,
                                     createGroupResp *response) {
    std::string groupname = request->groupname();
    std::string groupownerId = request->groupownerid();
    
    return Status::OK;
}

Status GroupServiceImpl::joinGroup(ServerContext *context,
                                   const joinGroupReq *request,
                                   joinGroupResp *response) {
    return Status::OK;
}

Status GroupServiceImpl::getGroupInfo(ServerContext *context,
                                      const getGroupInfoReq *request,
                                      getGroupInfoResp *response) {
    return Status::OK;
}

Status GroupServiceImpl::getGroupList(ServerContext *context,
                                      const getGroupListReq *request,
                                      getGroupListResp *response) {
    return Status::OK;
}

Status GroupServiceImpl::getGroupMember(ServerContext *context,
                                        const getGroupMemberReq *request,
                                        getGroupMemberResp *response) {
    return Status::OK;
}

GroupServiceImpl::GroupServiceImpl() {
}

GroupServiceImpl::~GroupServiceImpl() {
}

int main() {
    return 0;
}