#include "msg.h"
#include <grpcpp/channel.h>
#include <string>
#include <vector>
#include <thread>
#include "constant.h"
using ServerRpc::msg::msg;

void genGroupChatMsg() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; ++i) {
        threads.push_back(std::thread([i]() {
            auto channel = grpc::CreateChannel(
                "0.0.0.0:50051", grpc::InsecureChannelCredentials());
            auto msgClient = MsgClient(channel);
            int j = 100;
            using ServerRpc::msg::sendMsgResp;
            using ServerRpc::msg::sendMsgReq;
            while (j--) {
                msg *msg_ = new msg;
                sendMsgReq sendMsgReq;
                msg_->set_groupid("groupId:" + std::to_string(i));
                msg_->set_fromuserid("from:" + std::to_string(i));
                msg_->set_content("hello");
                msg_->set_msgtype(GROUP_CHAT_TYPE);
                msg_->set_platformid(1);
                sendMsgReq.set_allocated_msg_data(msg_);
                sendMsgResp sendMsgResp;
                auto status = msgClient.sendMsg(&sendMsgReq, &sendMsgResp);
                if (!status.ok()) {
                    std::cout << "sendMsg rpc failed." << std::endl;
                } else {
                    // std::cout << "sendMsgResp: " << sendMsgResp.sendtime()
                    //           << std::endl;
                }
            }
        }));
    }
    for (auto &t : threads) { t.join(); }
}

void genSingleChatMsg() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; ++i) {
        threads.push_back(std::thread([i]() {
            auto channel = grpc::CreateChannel(
                "0.0.0.0:50051", grpc::InsecureChannelCredentials());
            auto msgClient = MsgClient(channel);
            int j = 100;
            using ServerRpc::msg::sendMsgResp;
            using ServerRpc::msg::sendMsgReq;
            while (j--) {
                msg *msg_ = new msg;
                sendMsgReq sendMsgReq;
                msg_->set_touserid("to:" + std::to_string(i));
                msg_->set_fromuserid("from:" + std::to_string(i));
                msg_->set_content("hello");
                msg_->set_msgtype(1);
                msg_->set_platformid(1);
                sendMsgReq.set_allocated_msg_data(msg_);
                sendMsgResp sendMsgResp;
                auto status = msgClient.sendMsg(&sendMsgReq, &sendMsgResp);
                if (!status.ok()) {
                    std::cout << "sendMsg rpc failed." << std::endl;
                } else {
                    // std::cout << "sendMsgResp: " <<
                 
                    //           << std::endl;
                }
            }
        }));
    }
    for (auto &t : threads) { t.join(); }
}
int main() {
    msg *msg_ = new msg;
    sendMsgResp sendMsgResp;
    sendMsgReq sendMsgReq;
    msg_->set_touserid("123");
    msg_->set_fromuserid("456");
    msg_->set_content("hello");
    msg_->set_msgtype(1);
    msg_->set_platformid(1);
    sendMsgReq.set_allocated_msg_data(msg_);

    auto now = std::chrono::system_clock::now();
    genGroupChatMsg();
    auto end = std::chrono::system_clock::now();
    std::cout << "time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end
                                                                       - now)
                     .count()
              << std::endl;
    return 0;
}