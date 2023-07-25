#include "common.h"

Cache::Cache() {
    auto config = getConfig();
    auto redis_config = config["redis"];
    auto host = redis_config["host"].as<std::string>();
    auto port = redis_config["port"].as<int>();
    client.connect(host, port,
                   [](const std::string &host, std::size_t port,
                      cpp_redis::client::connect_state status) {
                       if (status
                           == cpp_redis::client::connect_state::dropped) {
                           std::cout << "client disconnected from " << host
                                     << ":" << port << std::endl;
                       }
                   });
}

Cache::~Cache() {
    client.disconnect();
}

cpp_redis::reply Cache::set(const std::string &key, const std::string &value) {
    auto set = client.set(key, value);
    client.sync_commit();
    return set.get();
}

cpp_redis::reply Cache::get(const std::string &key) {
    auto get = client.get(key);
    client.sync_commit();
    return get.get();
}

cpp_redis::reply Cache::del(const std::string &key) {
    auto del = client.del({key});
    client.sync_commit();
    return del.get();
}

cpp_redis::reply
Cache::batchSet(std::vector<std::pair<std::string, std::string>> &keyValues) {
    auto mset = client.mset(keyValues);
    client.commit();
    return mset.get();
}

cpp_redis::reply Cache::batchDel(const std::vector<std::string> &keys) {
    auto del = client.del(keys);
    client.commit();
    return del.get();
}

cpp_redis::reply Cache::batchGet(const std::vector<std::string> &keys) {
    auto mget = client.mget(keys);
    client.commit();
    return mget.get();
}
