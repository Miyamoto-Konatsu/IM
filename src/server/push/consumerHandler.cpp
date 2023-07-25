#include "consumerHandler.h"
#include "kafka.h"
#include "msg.pb.h"
#include "constant.h"
ConsumerHandler::ConsumerHandler() {
}

ConsumerHandler::~ConsumerHandler() {
    stop();
}

void ConsumerHandler::run() {
    MsgToPushConsumerFactory factory;
    consumer = factory.getConsumer();
    consumer->registerMsgCall(
        [this](ConsumerMQ::MsgVector &&msgs) { pushMsg(std::move(msgs)); });
    consumer->run();
}

void ConsumerHandler::stop() {
    consumer.reset();
}

void ConsumerHandler::pushMsg(ConsumerMQ::MsgVector &&msgs) {
    for (auto &msg : msgs) {
        if (msg->err() != RdKafka::ERR_NO_ERROR) {
            std::cout << "msg error: " << msg->errstr() << std::endl;
            continue;
        }
        std::string msgStr((char *)msg->payload(), msg->len());
        ServerRpc::msg::sendMsgReq msgObj;
        msgObj.ParseFromString(msgStr);
        
        if (msgObj.msg_data().msgtype() == SINGLE_CHAT_TYPE) {
            pusher.pushMsg2User(msgObj.msg_data());
        } else if (msgObj.msg_data().msgtype() == GROUP_CHAT_TYPE) {
            pusher.pushMsg2Group(msgObj.msg_data());
        } else {
            std::cout << "invalid msg type" << std::endl;
        }
    }
}
