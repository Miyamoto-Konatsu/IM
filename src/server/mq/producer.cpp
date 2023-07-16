#include "producer.h"
#include <iostream>
#include <librdkafka/rdkafkacpp.h>
#include "config/config.h"
#include <memory>

using RdKafka::Conf;
using RdKafka::ErrorCode;

static std::unique_ptr<Conf> getKafkaConfig() {
    auto uniqueKafkaConf =
        std::unique_ptr<Conf>(Conf::create(Conf::CONF_GLOBAL));
    std::string errstr;
    auto config = get_config();
    auto kafkaConf = config["kafka"];

    auto brokers = kafkaConf["brokers"].as<std::string>();
    auto user = kafkaConf["user"].as<std::string>();
    auto password = kafkaConf["password"].as<std::string>();
    auto acks = kafkaConf["acks"].as<std::string>();
    auto timeOut = kafkaConf["timeout"].as<std::string>();

    for (auto [name, value] :
         {std::pair("bootstrap.servers", brokers), std::pair("user.name", user),
          std::pair("user.password", password), std::pair("acks", acks),
          std::pair("message.timeout.ms", timeOut)}) {
        if (uniqueKafkaConf->set(name, value, errstr) != Conf::CONF_OK) {
            std::cerr << "Failed to set kafka config: " << name << " " << value
                      << " " << errstr << std::endl;
            exit(1);
        }
    }
    return uniqueKafkaConf;
}

ProducerMQ::ProducerMQ(std::unique_ptr<RdKafka::DeliveryReportCb> drcb) :
    drcb(std::move(drcb)) {
    conf = std::move(getKafkaConfig());
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
}

ProducerMQ::~ProducerMQ() {
    producer->flush(10000);
}

ErrorCode ProducerMQ::produce(const std::string &topic, const std::string &msg,
                              const std::string &key, void *opaque) {
    return producer->produce(
        topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
        const_cast<char *>(msg.c_str()), msg.size(),
        const_cast<char *>(key.c_str()), key.size(), 0, opaque);
}