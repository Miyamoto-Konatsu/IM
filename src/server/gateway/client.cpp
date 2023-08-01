#include "client.h"

#include "json.hpp"
#include <string>
#include <string>
#include <iostream>

using nlohmann::json;

void Client::handlerMsg(const std::string &msg) {
    json j = json::parse(msg);
    int type = j["type"];
    std::cout << type << std::endl;
    switch (type) {
    default: break;
    }
}
