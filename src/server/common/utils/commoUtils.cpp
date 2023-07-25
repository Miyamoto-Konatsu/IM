#include "commonUtils.h"

size_t StringHashCode(const std::string &str) {
    std::hash<std::string> hasher;
    return hasher(str);
}
