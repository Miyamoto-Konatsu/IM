#ifndef REDIS_H
#define REDIS_H

#include "json.hpp"
#include <functional>
#include <hiredis/hiredis.h>
#include <iostream>
using namespace std;

class Redis {
  public:
    Redis();
    ~Redis();

    int GetMsgId(int);

  private:
    void RedisConnect(redisContext **);

    redisContext *context_;
    redisContext *subscribe_context_;
};

#endif