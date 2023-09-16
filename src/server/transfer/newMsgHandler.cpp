#include "newMsgHandler.h"
#include <iostream>
#include <memory>
#include "constant.h"
#include "conversation.pb.h"
#include "conversation/conversation.h"
#include "kafka.h"
#include <muduo/base/Logging.h>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "msgHandler.h"
#include "protobuf/message.h"
#include "utils/commonUtils.h"
#include "msg.pb.h"
#include "cache/common.h"
#include "utils/msgutils.h"
#include <atomic>
using ServerRpc::msg::sendMsgReq;

NewMsgHandler::NewMsgHandler() :
    channels(std::thread::hardware_concurrency()),
    conversationClient(ConversationClient::getConversationClient()) {
    auto producerFactory = std::make_unique<MsgToPushProducerFactory>();
    msgToPushProducer = producerFactory->getProducer();

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
        std::vector<sendMsgReq> msgReqs;
        msgReqs.reserve(msgs.size());
        std::string key;
        for (auto &message : msgs) {
            if (message->err()) { continue; }
            key = *message->key();
            std::string message_payload(static_cast<char *>(message->payload()),
                                        message->len());
            sendMsgReq msgReq;
            msgReq.ParseFromString(message_payload);
            auto &msg = msgReq.msg_data();
            // std::cerr << msg.fromuserid() << ":" << msg.touserid() << ":"
            //   << msg.content() << std::endl;
            msgReqs.push_back((msgReq));
        }

        bool isNewConversation = msgDatabase.batchInsertMsg(msgReqs);

        if (isNewConversation) {
            //在关系数据库里创建新的会话
            auto &msg = msgReqs[0].msg_data();
            if (msg.msgtype() == SINGLE_CHAT_TYPE) {
                createSingleChatConversationsResp resp;
                createSingleChatConversationsReq req;
                req.set_sendid(msg.fromuserid());
                req.set_recvid(msg.touserid());
                auto status = conversationClient.createSingleChatConversations(
                    &req, &resp);
                if (!status.ok()) {
                    LOG_WARN << "createSingleChatConversations failed" << ' '
                             << msg.fromuserid() << ' ' << msg.touserid();
                    continue;
                }
            }
        }
        // push到mq，给push模块消费
        msgToPush(key, msgReqs);
    }
}

void NewMsgHandler::handleNewMsg(ConsumerMQ::MsgVector &&msgs) {
    msgDistribute(std::move(msgs));
}

void NewMsgHandler::run() {
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
    msgToPushProducer.reset();
}

void NewMsgHandler::msgToPush(std::string key,
                              const std::vector<sendMsgReq> &msgReqs) {
    for (auto msg : msgReqs) {
        std::string msgStr;
        msg.SerializeToString(&msgStr);
        auto ErrorCode = msgToPushProducer->produce(msgStr, key, nullptr);
        if (ErrorCode != RdKafka::ERR_NO_ERROR) {
            std::cerr << "msgToPushProducer produce error" << std::endl;
        }
    }
}