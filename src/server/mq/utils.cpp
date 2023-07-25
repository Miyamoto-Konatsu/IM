
#include "utils.h"

using RdKafka::Conf;

std::unique_ptr<Conf> getKafkaConfig() {
    auto uniqueKafkaConf =
        std::unique_ptr<Conf>(Conf::create(Conf::CONF_GLOBAL));
    std::string errstr;
    auto config = getConfig();
    auto kafkaConf = config["kafka"];

    auto brokers = kafkaConf["brokers"].as<std::string>();
    auto user = kafkaConf["user"].as<std::string>();
    auto password = kafkaConf["password"].as<std::string>();
    auto acks = kafkaConf["acks"].as<std::string>();
    auto timeOut = kafkaConf["timeout"].as<std::string>();

    for (const auto &[name, value] :
         {std::pair("bootstrap.servers", brokers), std::pair("acks", acks),
          std::pair("message.timeout.ms", timeOut)}) {
        if (uniqueKafkaConf->set(name, value, errstr) != Conf::CONF_OK) {
            std::cerr << "Failed to set kafka config: " << name << "," << value
                      << ":" << errstr << std::endl;
            exit(1);
        }
    }
    return uniqueKafkaConf;
}

std::string getTopic(const std::string &topicName) {
    auto config = getConfig();
    auto kafkaConf = config["kafka"];
    auto topicNode = kafkaConf[topicName];
    return topicNode["topic"].as<std::string>();
}

std::string getGroupId(const std::string &group) {
    auto config = getConfig();
    auto kafkaConf = config["kafka"];
    auto groupIds = kafkaConf["groupid"];
    auto id = groupIds[group].as<std::string>();
    return id;
}