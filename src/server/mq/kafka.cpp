#include "kafka.h"
#include "producer.h"
#include <cstdio>
#include <memory>
#include "deliverycallback.h"
#include "config/config.h"

std::unique_ptr<ProducerMQ> NewMsgMqProducerFactory::getProducer() {
    std::unique_ptr<ProducerMQ> producer = std::make_unique<ProducerMQ>(
        std::make_unique<NewMsgDeliveryReportCb>());
    producer->setTopic("newMsgToRedis");
    return producer;
}

std::unique_ptr<ProducerMQ> MsgToPushProducerFactory::getProducer() {
    std::unique_ptr<ProducerMQ> producer = std::make_unique<ProducerMQ>(
        std::make_unique<MsgToPushDeliveryReportCb>());
    producer->setTopic("msgToPush");
    return producer;
}

std::unique_ptr<ConsumerMQ> NewMsgMqConsumerFactory::getConsumer() {
    std::unique_ptr<ConsumerMQ> consumer =
        std::make_unique<ConsumerMQ>("newMsgGroup");
    consumer->setTopic("newMsgToRedis");
    return consumer;
}

std::unique_ptr<ConsumerMQ> MsgToPushConsumerFactory::getConsumer() {
    std::unique_ptr<ConsumerMQ> consumer =
        std::make_unique<ConsumerMQ>("msgToPushGroup");
    consumer->setTopic("msgToPush");
    return consumer;
}
