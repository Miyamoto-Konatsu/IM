#include "server/msgidserver/Service.h"
#include <exception>
MsgIdService::MsgIdService() {
    handler_map_[MsgType::get_msg_id] =
        std::bind(&MsgIdService::GetMsgId, this, _1);
}

MsgHandler MsgIdService::GetHandler(MsgType msg_type) {
    if (handler_map_.find(msg_type) != handler_map_.end()) {
        return handler_map_[msg_type];
    }
    throw std::invalid_argument("msg_type error");
}

int MsgIdService::GetMsgId(json &js) {
    lock_guard<mutex> lock(redis_mutex_);
    return redis_.GetMsgId(js["user_id"].get<int>());
}

MsgIdService *MsgIdService::GetInstance() {
    static MsgIdService service;
    return &service;
}