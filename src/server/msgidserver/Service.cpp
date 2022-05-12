#include "server/msgidserver/Service.h"
#include <exception>
#include <muduo/base/Logging.h>
using namespace muduo;
using namespace std;
MsgIdService::MsgIdService() {
    handler_map_[MsgType::get_msg_id] =
        std::bind(&MsgIdService::GetMsgId, this, _1,_2);
}

MsgHandler MsgIdService::GetHandler(MsgType msg_type) {
    if (handler_map_.find(msg_type) != handler_map_.end()) {
        return handler_map_[msg_type];
    }
    throw std::invalid_argument("msg_type error");
}

void Send(const TcpConnectionPtr &conn, const nlohmann::json &response) {
    try {
        uint32_t packet_length;
        auto res = GeneratePacket(response.dump(), packet_length);
        if (res == nullptr)
            return;
        conn->send((const void*)res.get(), packet_length);
    } catch (const exception &e) {
        LOG_DEBUG << e.what();
    }
}

void MsgIdService::GetMsgId(const TcpConnectionPtr &conn, json &js) {
    lock_guard<mutex> lock(redis_mutex_);
    json response;
    response["msg_type"] = MsgType::get_msg_id_res;
    response["msg_id"] = redis_.GetMsgId(js["user_id"].get<MsgIdType>());
    Send(conn, response);
}

MsgIdService *MsgIdService::GetInstance() {
    static MsgIdService service;
    return &service;
}