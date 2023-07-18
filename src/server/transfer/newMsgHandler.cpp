#include "newMsgHandler.h"
#include <iostream>
#include <memory>
#include "kafka.h"
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "msgHandler.h"
#include "protobuf/message.h"
#include "utils/commonUtils.h"
#include "msg.pb.h"
#include "cache/common.h"
#include <atomic>
using ServerRpc::msg::sendMsgReq;

NewMsgHandler::NewMsgHandler() : channels(std::thread::hardware_concurrency()){
    auto factory = std::make_unique<NewMsgMqConsumerFactory>();
    newMsgConsumer = factory->getConsumer();
    auto consumeNewMsgCall =
        std::bind(&NewMsgHandler::handleNewMsg, this, std::placeholders::_1);
    newMsgConsumer->registerMsgCall(std::move(consumeNewMsgCall));
}

NewMsgHandler::~NewMsgHandler() {
    stop();
}

void NewMsgHandler::msgDistribute(ConsumerMQ::MsgVector &&msgs) {
    std::unordered_map<std::string, ConsumerMQ::MsgVector> msgMap;
    for (auto msg : msgs) {
        std::string key = *msg->key();
        msgMap[key].push_back(msg);
    }
    for (auto &msg : msgMap) {
        auto hashcode = StringHashCode(msg.first);
        auto index = hashcode % 16;
        channels[index].send(std::move(msg.second));
    }
}

void NewMsgHandler::msgHandler(int index) {
    auto &channel = channels[index];
    while (true) {
        std::vector<std::shared_ptr<RdKafka::Message>> msgs;
        try {
            msgs = channel.receive();
        } catch (std::runtime_error e) {
            std::cerr << e.what() << std::endl;
            break;
        }

        for (auto &message : msgs) {
            if (message->err()) { continue; }
            auto key = *message->key();
            std::string message_payload(static_cast<char *>(message->payload()),
                                        message->len());
            sendMsgReq msgReq;
            msgReq.ParseFromString(message_payload);
            auto &msg = msgReq.msg();
            std::cerr << msg.fromuserid() << ":" << msg.touserid() << ":"
                      << msg.content() << std::endl;
        }
    }
}

void NewMsgHandler::handleNewMsg(ConsumerMQ::MsgVector &&msgs) {
    msgDistribute(std::move(msgs));
}

void NewMsgHandler::start() {
    auto threadNum = std::thread::hardware_concurrency();
    for (int i = 0; i < threadNum; ++i) {
        // channels.emplace_back();
        msgHandlerThreads.emplace_back(&NewMsgHandler::msgHandler, this, i);
    }
    newMsgConsumer->run();
}

void NewMsgHandler::stop() {
    newMsgConsumer.reset();
    for (auto &channel : channels) { channel.close(); }
    for (auto &thread : msgHandlerThreads) { thread.join(); }
}
