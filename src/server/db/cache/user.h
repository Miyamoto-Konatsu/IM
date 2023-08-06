#ifndef USER_CACHE_H
#define USER_CACHE_H

#include <memory>
#include "common.h"
#include "relation/user_model.h"

class UserCache : public Cache {
public:
    static const std::string USER_PREFIX;

    UserCache(std::shared_ptr<UserModel>);

    virtual ~UserCache() = default;

   // UserRpc getUser(const std::string &userId);
    User getUser(const std::string &userId);
    // std::vector<User> getUsers(const std::vector<std::string> &userIds);

    std::string getUserKey(const std::string &userId) {
        return USER_PREFIX + userId;
    }

private:
    std::shared_ptr<UserModel> db;
};
#endif