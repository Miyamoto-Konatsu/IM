#include "msg.h"

MsgCache::MsgCache() {
}

MsgCache::~MsgCache() {
}

int64_t MsgCache::getConversionMaxId(const std::string &key) {
    auto get = client.get(key);
    client.commit();
    auto res = get.get();
    if (res.ko()) { throw std::runtime_error("getConversionMaxId failed"); }
    std::cout << key << ' ' << res << std::endl;
    if (res.is_null())
        return -1;
    else if (res.is_string())
        return stoi(res.as_string());
    else { throw std::runtime_error("getConversionMaxId failed"); }
}

bool MsgCache::setConversionMaxId(const std::string &key, int64_t id) {
    auto set = client.set(key, std::to_string(id));
    client.sync_commit();
    auto res = set.get();
    if (res.ko()) { throw std::runtime_error("setConversionMaxId failed"); }
    return res.ok();
}