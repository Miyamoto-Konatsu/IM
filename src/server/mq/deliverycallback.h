#ifndef DELIVERYCALLBACK_H
#define DELIVERYCALLBACK_H
#include "librdkafka/rdkafkacpp.h"

class NewMsgDeliveryReportCb : public RdKafka::DeliveryReportCb {
public:
    void dr_cb(RdKafka::Message &message);
};

class MsgToPushDeliveryReportCb : public RdKafka::DeliveryReportCb {
public:
    void dr_cb(RdKafka::Message &message);
};

#endif