#ifndef DB_CACHE_AUTH_H
#define DB_CACHE_AUTH_H

#include "common.h"

class AuthCache : public Cache {
public:
    AuthCache();

    virtual ~AuthCache();

    std::string setToken(const std::string &key, const std::string &token, int expire);

    std::string getToken(const std::string &key);

    std::string delToken(const std::string &key);
};
#endif