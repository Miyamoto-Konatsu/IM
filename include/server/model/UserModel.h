#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "server/db/MySQL.h"
#include "server/model/User.h"
#include <istream>
#include <muduo/base/Logging.h>
using namespace muduo;
class UserModel {
  public:
    UserModel() {
      Logger::setLogLevel(Logger::LogLevel::DEBUG);
    }

    bool Insert(User &user);

    bool QueryUser(int user_id, User &user);

    bool UpdateState(const User &);
};
#endif