#include "kafka.h"
#include "producer.h"
#include <cstdio>
#include <memory>
#include "deliverycallback.h"

std::unique_ptr<ProducerMQ> NewMsgMqFactory::getProducer() {
    std::unique_ptr<ProducerMQ> producer = std::make_unique<ProducerMQ>(
        std::make_unique<NewMsgDeliveryReportCb>());
    producer->setTopic("newMsgToRedis");
    return producer;
}