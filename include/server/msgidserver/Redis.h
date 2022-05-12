#ifndef REDIS_H
#define REDIS_H

#include "json.hpp"
#include <functional>
#include <hiredis/hiredis.h>
#include <iostream>
#include "server/msgidserver/MsgCommon.h"
using namespace std;

class Redis {
  public:
    Redis();
    ~Redis();

    MsgIdType GetMsgId(int);

  private:
    void RedisConnect(redisContext **);

    redisContext *context_;
};

#endif