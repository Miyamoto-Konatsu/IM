#ifndef KAFKA_MQ_H
#define KAFKA_MQ_H

#include "producer.h"
#include <memory>
#include <queue>

class MqFactory {
public:
    virtual std::unique_ptr<ProducerMQ> getProducer() = 0;
};

class NewMsgMqFactory : public MqFactory {
public:
    std::unique_ptr<ProducerMQ> getProducer() override;
};
#endif // KAFKA_MQ_H