#include "msg.h"
#include <grpcpp/channel.h>

using ServerRpc::msg::msg;
int main() {
    MsgClient msgClient(grpc::CreateChannel(
        "0.0.0.0:50051", grpc::InsecureChannelCredentials()));
    msg *msg_ = new msg;
    sendMsgResp sendMsgResp;
    sendMsgReq sendMsgReq;
    msg_->set_touserid("123");
    msg_->set_fromuserid("456");
    msg_->set_content("hello");
    msg_->set_msgtype(1);
    msg_->set_platformid(1);
    sendMsgReq.set_allocated_msg(msg_);
    auto status = msgClient.sendMsg(&sendMsgReq, &sendMsgResp);
    if(!status.ok()) {
        std::cout << "sendMsg rpc failed." << std::endl;
        return -1;
    }
    std::cout << "sendMsgResp: " << sendMsgResp.sendtime() << std::endl;
    return 0;
}