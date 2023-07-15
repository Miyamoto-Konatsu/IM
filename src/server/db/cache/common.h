#ifndef COMMON_CACHE_H
#define COMMON_CACHE_H

#include "cpp_redis/cpp_redis"
#include <string>
#include "config/config.h"

class Cache {
public:
    Cache();

    ~Cache();

    std::string set(const std::string &key, const std::string &value);

    std::string get(const std::string &key);

    std::string del(const std::string &key);

protected:
    cpp_redis::client client;
};

#endif