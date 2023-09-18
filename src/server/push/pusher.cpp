#include "pusher.h"
#include "gateway.pb.h"
#include "gateway/gateway.h"
#include "msg.pb.h"
#include "utils/commonUtils.h"
#include "utils/msgutils.h"
#include <string>
Pusher::Pusher() : gatewayClient_(GatewayClient::getGatewayClient()) {
}

Pusher::~Pusher() {
}

bool Pusher::pushMsg2User(const msg &msg) {
    std::vector<std::string> userIds;
    userIds.push_back(msg.touserid());
    if(msg.fromuserid() != msg.touserid())
        userIds.push_back(msg.fromuserid());
    getConnsAndOnlinePush(userIds, msg);
    return true;
}

bool Pusher::pushMsg2Group(const msg &msg) {
    std::cout << msg.fromuserid() << ' ' << msg.groupid() << ' '
              << msg.content() << std::endl;
    std::vector<std::string> userIds;
    try {
        userIds = groupLocalCache_.getGroupMemberIds(msg.groupid());
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    getConnsAndOnlinePush(userIds, msg);
    return true;
}

void Pusher::getConnsAndOnlinePush(const std::vector<std::string> &userIds,
                                   const msg &msg) {
    onlineBatchPushOneMsgReq req;
    onlineBatchPushOneMsgResp resp;
    for (auto userId : userIds) { req.add_pushtouserids()->assign(userId); }
    ServerRpc::msg::msg *msgData = new ServerRpc::msg::msg();
    msgData->CopyFrom(msg);
    req.set_allocated_msg_data(msgData);
    gatewayClient_.onlineBatchPushOneMsg(req, &resp);
}