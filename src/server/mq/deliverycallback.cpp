#include "deliverycallback.h"
#include "kafka.h"
#include <iostream>
#include <future>

#include <librdkafka/rdkafkacpp.h>
#include <memory>
#include <thread>

using RdKafka::ErrorCode;

void NewMsgDeliveryReportCb::dr_cb(RdKafka::Message &message) {
    // if (message.err()) {
    //     std::cerr << "% Message delivery failed: " << message.errstr()
    //               << std::endl;
    // } else {
    //     std::string message_payload(static_cast<char *>(message.payload()),
    //                                 message.len());
    //     std::cerr << "% Message delivered to topic " << message.topic_name()
    //               << " [" << message_payload << "] at offset "
    //               << message.offset() << std::endl;
    // }
    std::promise<ErrorCode> *p =
        reinterpret_cast<std::promise<ErrorCode> *>(message.msg_opaque());
    p->set_value(message.err());
}