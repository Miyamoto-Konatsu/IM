#include "user.h"
#include <exception>
#include <functional>
#include "cache/common.h"
#include "relation/common.h"

const std::string UserCache::USER_PREFIX = "user:";

UserCache::UserCache(std::shared_ptr<UserModel> db) : db(db) {
}

User UserCache::getUser(const std::string &userId) {
    std::string userKey = getUserKey(userId);
    std::function<User()> fn = [&, this]() {
        auto user = this->db->findUser(userId);
        return user;
        // UserRpc userRpc;
        // copyField(userRpc, user);
        // return userRpc;
    };
    return getCache(userKey, shared_from_this(), 100, std::move(fn));
}