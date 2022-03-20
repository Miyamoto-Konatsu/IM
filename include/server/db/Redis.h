#ifndef REDIS_H
#define REDIS_H

#include "json.hpp"
#include <functional>
#include <hiredis/hiredis.h>
#include <iostream>
#include <thread>
using namespace std;
using subscribe_callback = function<void(int, string)>;

class Redis {
  public:
    Redis();
    ~Redis();

    bool Publish(int, const string &);
    bool Subscribe(int);
    bool Unsubscribe(int);
    void SetSubscribeCallback(subscribe_callback);

    bool SignIn(int);

    //如果在线，返回false;不在线，返回true
    bool IsOnline(int);
    void SignOut(int);

  private:
    void RedisConnect(redisContext **);
    void MessageHandler(subscribe_callback);
    redisContext *publish_context_;
    redisContext *subscribe_context_;

    thread message_handler_;
    bool redis_alive_;
};

#endif