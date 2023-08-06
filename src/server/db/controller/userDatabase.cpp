#include "userDatabase.h"
#include "cache/common.h"
#include "relation/common.h"
#include "relation/user_model.h"
#include <memory>
#include <muduo/base/Logging.h>

UserDatabase::UserDatabase() {
    userModel_ = std::make_shared<UserModel>();
    userCache_ = std::make_shared<UserCache>(userModel_);
}

// UserRpc UserDatabase::getUser(const std::string &userId) {
//     return userCache_->getUser(userId);
// }

// throw DatabaseLookupError if not found
User UserDatabase::getUser(const std::string &userId) {
    return userCache_->getUser(userId);
}

bool UserDatabase::createUser(const UserRpc &userRpc) {
    User user;
    copyField(user, userRpc);
    try {
        userModel_->createUser(user);
        LOG_INFO << "create user: userId: " << user.userId()
                 << " user nickname: " << user.nickname()
                 << " user password: " << user.password();
        return true;
    } catch (const DatabaseLookupError &e) {
        LOG_INFO << "failed to create user:" << e.what()
                 << " userId: " << user.userId()
                 << " user nickname: " << user.nickname()
                 << " user password: " << user.password();
        return false;
    }
}

bool UserDatabase::checkUser(const std::string &userId,
                             const std::string &password) {
    try {
        auto user = userCache_->getUser(userId);
        if (user.password() == password) { return true; }
        return false;
    } catch (const DatabaseLookupError &e) {
        LOG_INFO << "failed to check user:" << e.what() << " userId: " << userId
                 << " password: " << password;
        return false;
    }
}