#include "auth.h"

AuthCache::AuthCache() {
}

AuthCache::~AuthCache() {
}

std::string AuthCache::setToken(const std::string &key,
                                const std::string &token, int expireSecond) {
    auto set = client.set(key, token);
    auto expire = client.expire(key, expireSecond);
    client.sync_commit();
    auto res = set.get();
    auto expireRes = expire.get();
    if (res.as_string() != "OK" || expireRes.as_integer() != 1)
        return "ERROR";
    else
        return "OK";
}

std::string AuthCache::getToken(const std::string &key) {
    auto get = client.get(key);
    client.sync_commit();
    auto res = get.get();
    if (res.is_null())
        return "ERROR";
    else
        return res.as_string();
}

std::string AuthCache::delToken(const std::string &key) {
    auto del = client.del({key});
    client.sync_commit();
    auto res = del.get();
    if(res.as_integer() != 1)
        return "ERROR";
    else
        return "OK";
}