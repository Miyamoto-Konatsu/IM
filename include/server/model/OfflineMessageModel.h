#ifndef OFFLINE_MESSAGE_MODEL_H
#define OFFLINE_MESSAGE_MODEL_H

#include "server/db/MySQL.h"
#include "server/model/User.h"
#include <istream>
#include <memory>
#include <muduo/base/Logging.h>
#include <string>
#include <vector>
using namespace std;
class OfflineMessageModel {
  private:
    /* data */
  public:
    bool Insert(int, const string &);
    void Delete(int);
    unique_ptr<vector<string>> Query(int);
};

#endif