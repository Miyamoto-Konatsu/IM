#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "server/model/Group.h"
#include "server/model/User.h"
#include <istream>
#include <memory>
#include <muduo/base/Logging.h>
using namespace std;
using namespace muduo;
class GroupModel {
  public:
    GroupModel() { Logger::setLogLevel(Logger::LogLevel::DEBUG); }

    bool InsertGroup(Group &group);
    bool InsertGroupUser(int group_id, int user_id, string role = "normal");
    //查询用户所在的所有群
    unique_ptr<vector<Group>> QueryGroup(int user_id);

  private:
    //查询该群所有成员id和身份
    unique_ptr<vector<pair<int,string>>> QueryGroupUser(int group_id);

    bool UpdateState(const Group &);
};

#endif