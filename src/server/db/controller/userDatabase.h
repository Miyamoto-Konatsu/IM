#ifndef USERDATABASE_CONTROLLER_H
#define USERDATABASE_CONTROLLER_H

#include <memory>
#include <string>
#include <vector>
#include "cache/user.h"
#include "relation/user_model.h"
#include "table/user.h"
#include "user.pb.h"
using UserRpc = ServerRpc::user::user;
class UserDatabase {
public:
    UserDatabase();

    virtual ~UserDatabase() = default;

    User getUser(const std::string &userId);

    bool createUser(const UserRpc &userRpc);

    bool checkUser(const std::string &userId, const std::string &password);
private:
    std::shared_ptr<UserCache> userCache_;
    std::shared_ptr<UserModel> userModel_;
};

#endif