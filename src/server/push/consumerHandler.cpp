#include "consumerHandler.h"
#include "kafka.h"
#include "msg.pb.h"
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
        pusher.PushMsg2User(msgObj.msg_data());
    }
}
