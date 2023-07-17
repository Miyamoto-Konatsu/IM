#include "producer.h"
#include <iostream>
#include <librdkafka/rdkafkacpp.h>
#include "config/config.h"
#include <memory>
#include <thread>
#include "utils.h"

using RdKafka::Conf;
using RdKafka::ErrorCode;

ProducerMQ::ProducerMQ(std::unique_ptr<RdKafka::DeliveryReportCb> &&pdrcb) :
    drcb(std::move(pdrcb)) {
    conf = getKafkaConfig();
    std::string errstr;

    if (conf->set("dr_cb", drcb.get(), errstr) != Conf::CONF_OK) {
        std::cerr << errstr << std::endl;
        exit(1);
    }

    producer = std::unique_ptr<RdKafka::Producer>(
        RdKafka::Producer::create(conf.get(), errstr));
    if (!producer) {
        std::cerr << "Failed to create producer: " << errstr << std::endl;
        exit(1);
    }

    pollThread = std::thread([this]() { this->poll(); });
}

ProducerMQ::~ProducerMQ() {
    producer->flush(10000);
    run = 0;
    pollThread.join();
}

ErrorCode ProducerMQ::produce(const std::string &topic, const std::string &msg,
                              const std::string &key, void *opaque) {
    return producer->produce(
        topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
        const_cast<char *>(msg.c_str()), msg.size(),
        const_cast<char *>(key.c_str()), key.size(), 0, opaque);
}

ErrorCode ProducerMQ::produce(const std::string &msg, const std::string &key,
                              void *opaque) {
    auto code = produce(topic, msg, key, opaque);
    producer->poll(0);
    return code;
}

void ProducerMQ::setTopic(const std::string &topicName) {
    this->topic = getTopic(topicName);
}