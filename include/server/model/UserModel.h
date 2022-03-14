#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "server/model/User.h"
#include "db/MySQL.h"

class UserModel {
    public:
    UserModel(){}

    bool Insert(const User& user) {
        return true;
    }

};
#endif