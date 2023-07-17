#include "msgutils.h"

std::string getSingleChatKey(const std::string &from, const std::string &to) {
    return "SingleChat:" + from + "_" + to;
}