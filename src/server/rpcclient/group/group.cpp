#include "group.h"

int main() {
    GroupClient client(grpc::CreateChannel("localhost:50051",
                                           grpc::InsecureChannelCredentials()));
    createGroupReq req;
    createGroupResp resp;
    // req.set_groupname("test");
    // req.set_groupowner("test");
    // req.set_groupdesc("test");
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
    //std::cout << info.groupmembers() << std::endl;
    return 0;
}