#ifndef PRODUCER_MQ_H
#define PRODUCER_MQ_H

#include "librdkafka/rdkafkacpp.h"
#include <memory>
#include <string>

class ProducerMQ {
public:
    ProducerMQ(std::unique_ptr<RdKafka::DeliveryReportCb> drcb);
    ~ProducerMQ();
    RdKafka::ErrorCode produce(const std::string &topic, const std::string &msg,
                               const std::string &key = "",
                               void *opaque = NULL);

private:
    std::unique_ptr<RdKafka::Producer> producer;
    std::unique_ptr<RdKafka::Conf> conf;
    std::unique_ptr<RdKafka::DeliveryReportCb> drcb;
};
#endif // PRODUCE_MQ_H