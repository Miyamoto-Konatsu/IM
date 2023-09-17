#include "toMysqlHandler.h"
#include "constant.h"
#include "controller/chatlogDatabase.h"
#include "kafka.h"
#include "msg/msg.h"
#include "table/chatlog.h"
#include "user.pb.h"
#include "utils/msgutils.h"

ToMysqlHandler::ToMysqlHandler() {
    newMsgConsumer =
        std::make_unique<MsgToMysqlConsumerFactory>()->getConsumer();
    auto consumeNewMsgCall =
        std::bind(&ToMysqlHandler::persistMsg, this, std::placeholders::_1);
    newMsgConsumer->registerMsgCall(std::move(consumeNewMsgCall));
}

ToMysqlHandler::~ToMysqlHandler() {
    stop();
}

void ToMysqlHandler::stop() {
    newMsgConsumer.reset();
}

void ToMysqlHandler::run() {
    newMsgConsumer->run();
}

void ToMysqlHandler::persistMsg(ConsumerMQ::MsgVector &&msgs) {
    std::vector<ChatLog> msgReqs;
    msgReqs.reserve(msgs.size());
    for (auto &message : msgs) {
        if (message->err()) { continue; }
       
        std::string message_payload(static_cast<char *>(message->payload()),
                                    message->len());
        sendMsgReq msgReq;
        msgReq.ParseFromString(message_payload);
        auto &msg = msgReq.msg_data();
        // std::cerr << msg.fromuserid() << ":" << msg.touserid() << ":"
        //   << msg.content() << std::endl;
        ChatLog chatLog;
        chatLog.fromUserId(msg.fromuserid());
        chatLog.toUserId(msg.touserid());
        chatLog.content(msg.content());
        chatLog.time(msg.createtime());
        chatLog.groupId(msg.groupid());
        chatLog.msgType(msg.msgtype());
        chatLog.seq(msg.seq());
        chatLog.platform(msg.platformid());
        if(msg.msgtype() == SINGLE_CHAT_TYPE)
            chatLog.conversaionId(getConversationIdForSingle(msg.fromuserid(), msg.touserid()));
        else
            chatLog.conversaionId(getConversationIdForGroup(msg.groupid()));
        msgReqs.push_back((chatLog));
    }
    chatLogController.createChatLog(msgReqs);
}

