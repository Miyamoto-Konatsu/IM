#include "json.hpp"
#include "server/db/Redis.h"
#include <cstring>
#include <hiredis/hiredis.h>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using nlohmann::json;
using namespace std;
void f(const json &message) {}
int main() {
    Redis redis;
    /* redis.Subscribe(15);

    redis.SetSubscribeCallback(f);
    int i = 0;
    while (i < 100000) {
        ++i; redis.Publish(15, to_string(i));
    } */
    cout << redis.SignIn(14);
    cout << redis.SignIn(15);
    cout << redis.SignIn(15);
    cout << redis.SignIn(14);

    /* redisReply *reply = nullptr;
    reply = (redisReply *)redisCommand(c, "subscribe %s", "redischat");
    if (NULL == reply ||
        reply->type != REDIS_REPLY_ARRAY) //订阅成功返回一个数组标识
    {
        std::cout << "subscribe failed!" << endl;
        freeReplyObject(reply);
        redisFree(c);
        c = NULL;
        return 0;
    }
    freeReplyObject(reply);

    // 5、阻塞等待订阅消息
    while (true) {
        void *_reply = nullptr;
        if (redisGetReply(c, &_reply) != REDIS_OK) {
            continue;
        }
        reply = (redisReply *)_reply;
        for (int nIndex = 0; nIndex < reply->elements; nIndex++) {
            std::cout << nIndex + 1 << ")";
            std::cout << reply->element[nIndex]->str << std::endl;
        }
        freeReplyObject(reply);
        std::cout << "***************" << std::endl;
    }
    redisFree(c);
    c = NULL; */
    return 0;
}