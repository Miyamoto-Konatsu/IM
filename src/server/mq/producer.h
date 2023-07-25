#ifndef PRODUCER_MQ_H
#define PRODUCER_MQ_H

#include "librdkafka/rdkafkacpp.h"
#include <memory>
#include <string>
#include <thread>

class ProducerMQ {
public:
    ProducerMQ(std::unique_ptr<RdKafka::DeliveryReportCb> &&drcb);
    ProducerMQ(const ProducerMQ &) = delete;
    ProducerMQ &operator=(const ProducerMQ &) = delete;

    virtual ~ProducerMQ();
    RdKafka::ErrorCode produce(const std::string &topic, const std::string &msg,
                               const std::string &key = "",
                               void *opaque = NULL);
    RdKafka::ErrorCode produce(const std::string &msg,
                               const std::string &key = "",
                               void *opaque = NULL);
    void setTopic(const std::string &topicName);

protected:
    std::string topic;
    std::unique_ptr<RdKafka::Producer> producer;
    std::unique_ptr<RdKafka::Conf> conf;
    std::unique_ptr<RdKafka::DeliveryReportCb> drcb;

    std::thread pollThread;

    int volatile run = 1;

private:
    void poll() {
        while (run)  { producer->poll(50); }
    }
};

#endif // PRODUCE_MQ_H