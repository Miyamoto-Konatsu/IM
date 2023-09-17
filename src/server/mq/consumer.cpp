#include "consumer.h"
#include "utils.h"
#include <librdkafka/rdkafkacpp.h>
#include <memory>

ConsumerMQ::ConsumerMQ() {
    auto conf = getKafkaConfig();
    std::string errstr;

    consumer = std::unique_ptr<KafkaConsumer>(
        KafkaConsumer::create(conf.get(), errstr));
    if (!consumer) {
        std::cerr << "Failed to create consumer: " << errstr << std::endl;
        exit(1);
    }
}

ConsumerMQ::ConsumerMQ(std::string groupid) {
    auto conf = getKafkaConfig();
    std::string errstr;
    if (conf->set("group.id", getGroupId(groupid), errstr) != Conf::CONF_OK) {
        std::cerr << "Failed to set kafka config: " << errstr << std::endl;
        exit(1);
    }
    consumer = std::unique_ptr<KafkaConsumer>(
        KafkaConsumer::create(conf.get(), errstr));
    if (!consumer) {
        std::cerr << "Failed to create consumer: " << errstr << std::endl;
        exit(1);
    }
}

ConsumerMQ::~ConsumerMQ() {
    stop();
}

void ConsumerMQ::setTopic(const std::string &topicName) {
    this->topic = getTopic(topicName);
}

void ConsumerMQ::registerMsgCall(MsgCall &&call) {
    msgCall = std::move(call);
}

void ConsumerMQ::run() {
    consumerThread = std::thread([this]() {
        consumer->subscribe({topic});
        while (runnning) {
            auto msgs = consumeBatch(100, 10);
            if (msgs.size() > 0) {
                msgCall(std::move(msgs));
            }
        }
    });
}

void ConsumerMQ::stop() {
    runnning = 0;
    consumerThread.join();
    consumer->close();
}

int64_t ConsumerMQ::now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

ConsumerMQ::MsgVector ConsumerMQ::consumeBatch(size_t batch_size,
                                               int batch_tmout) {
    MsgVector msgs;
    msgs.reserve(batch_size);
    int64_t end = now() + batch_tmout;
    int remaining_timeout = batch_tmout;
    while (msgs.size() < batch_size) {
        auto msg = std::shared_ptr<RdKafka::Message>(
            consumer->consume(remaining_timeout));
        switch (msg->err()) {
        case RdKafka::ERR__TIMED_OUT: {
            return msgs;
        }

        case RdKafka::ERR_NO_ERROR: {
            msgs.push_back(msg);
            break;
        }

        default: {
            std::cerr << "%% Consumer error: " << msg->errstr() << std::endl;
            runnning = 0;
            return msgs;
        }
        }
        remaining_timeout = end - now();
        if (remaining_timeout < 0) break;
    }
    return msgs;
}