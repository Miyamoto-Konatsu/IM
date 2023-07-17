#ifndef UTILS_MQ_H
#define UTILS_MQ_H

#include <iostream>
#include <librdkafka/rdkafkacpp.h>
#include "config/config.h"
#include <memory>
#include <thread>

using RdKafka::Conf;

std::unique_ptr<Conf> getKafkaConfig();

std::string getTopic(const std::string &topicName);

#endif