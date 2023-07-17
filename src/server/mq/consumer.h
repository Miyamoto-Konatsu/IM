#ifndef CONSUMER_MQ_H
#define CONSUMER_MQ_H

#include <functional>
#include <iostream>
#include "librdkafka/rdkafkacpp.h"
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <thread>

class ConsumerMQ {
public:
    using MsgCall =
        std::function<void(std::vector<std::shared_ptr<RdKafka::Message>>)>;
    using KafkaConsumer = RdKafka::KafkaConsumer;
    using MsgVector = std::vector<std::shared_ptr<RdKafka::Message>>;

public:
    ConsumerMQ();
    ~ConsumerMQ();

    void setTopic(const std::string &topicName);
    void registerMsgCall(MsgCall &&call);
    void run();
    void stop();

private:
    int64_t now();
    MsgVector consumeBatch(size_t batch_size, int batch_tmout);

private:
    MsgCall msgCall;
    std::unique_ptr<KafkaConsumer> consumer;
    int volatile runnning = 1;
    std::string topic;
    std::thread consumerThread;
};

#endif // CONSUMER_MQ_H