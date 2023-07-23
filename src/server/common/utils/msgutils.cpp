#include "msgutils.h"

std::string getSingleChatKey(const std::string &from, const std::string &to) {
    if (from > to) return "SingleChat:" + to + "_" + from;
    return "SingleChat:" + from + "_" + to;
}

std::string getConversionIdForSingle(const std::string &from, const std::string &to) {
    if (from > to) return to + "_" + from;
    return from + "_" + to;
}