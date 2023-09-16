#include "group.h"
#include "group.pb.h"

int main() {
    GroupClient client(grpc::CreateChannel("localhost:50051",
                                           grpc::InsecureChannelCredentials()));
    getGroupMemberIdHashReq req;
    getGroupMemberIdHashResp resp;
    // req.set_groupid("g123");
    
    // auto status = client.createGroup(req, resp);
    // if (!status.ok()) {
    //     std::cout << status.error_code() << ": " << status.error_message()
    //               << std::endl;
    // }
    // auto info = resp.groupinfo();
    // std::cout << info.groupid() << std::endl;
    // std::cout << info.groupname() << std::endl;
    // std::cout << info.groupowner() << std::endl;
    // std::cout << info.groupdesc() << std::endl;
    // std::cout << info.createtime() << std::endl;
    // std::cout << info.groupmembers() << std::endl;
    return 0;
}