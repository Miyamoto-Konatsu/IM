#ifndef Friend_MODEL_H
#define Friend_MODEL_H

#include "server/db/MySQL.h"
#include "server/model/User.h"
#include <istream>
#include <memory>
#include <muduo/base/Logging.h>
#include <vector>
using namespace std;
class FriendModel {
  public:
    bool Insert(int user_id1, int user_id2);
    unique_ptr<vector<User>> GetFriend(int user_id);
};

#endif