#include "msgDatabase.h"
#include "msg.pb.h"
#include "utils/msgutils.h"
#include <protobuf/message.h>
#include "msg.grpc.pb.h"

MsgDatabase::MsgDatabase() {
}

MsgDatabase::~MsgDatabase() {
}

int64_t MsgDatabase::getConversionMaxId(const std::string &key) {
    return msgCache.getConversionMaxId(key);
}

bool MsgDatabase::setConversionMaxId(const std::string &key, int64_t id) {
    return msgCache.setConversionMaxId(key, id);
}

bool MsgDatabase::batchInsertMsg(std::vector<sendMsgReq> &msgReqs) {
    auto &msg = msgReqs[0].msg_data();
    bool isNewConversion = false;

    auto conversionId =
        getConversionIdForSingle(msg.fromuserid(), msg.touserid());
    int64_t maxId = getConversionMaxId(conversionId);

    if (maxId == -1) {
        isNewConversion = true;
        maxId = 0;
    }

    for (auto &msgReq : msgReqs) {
        auto &msg = *msgReq.mutable_msg_data();
        msg.set_seq(++maxId);
    }

    if (!msgCache.setConversionMaxId(conversionId, maxId)) {
        std::cerr << "setConversionMaxId failed" << std::endl;
    } else {
        std::cerr << "setConversionMaxId success" << std::endl;
    }

    return isNewConversion;
}