#ifndef KAFKA_MQ_H
#define KAFKA_MQ_H

#include "consumer.h"
#include "producer.h"
#include <memory>
#include <queue>

class MqProducerFactory {
public:
    virtual std::unique_ptr<ProducerMQ> getProducer() = 0;
};

class NewMsgMqProducerFactory : public MqProducerFactory {
public:
    std::unique_ptr<ProducerMQ> getProducer() override;
};

// 消费者工厂
class MqConsumerFactory {
public:
    virtual std::unique_ptr<ConsumerMQ> getConsumer() = 0;
};

class NewMsgMqConsumerFactory : public MqConsumerFactory {
public:
    std::unique_ptr<ConsumerMQ> getConsumer() override;
};

#endif // KAFKA_MQ_H