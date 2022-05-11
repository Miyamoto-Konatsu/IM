#include "server/msgidserver/Redis.h"

using namespace std;

Redis::Redis() { RedisConnect(&this->context_); }

void Redis::RedisConnect(redisContext **context) {
    *context = redisConnect("127.0.0.1", 6379);
    if (*context == NULL || (*context)->err) {
        if (*context) {
            printf(" Error: %s \n ", (*context)->errstr);
        } else {
            printf(" Can't allocate redis context \n ");
        }
        *context = nullptr;
        exit(-1);
    }
}

Redis::~Redis() {
    redisFree(context_);
    context_ = nullptr;
}

int Redis::GetMsgId(int user_id) {
    redisReply *reply =
        (redisReply *)redisCommand(context_, "incr %d", user_id);
    if (reply == nullptr) {
        RedisConnect(&this->context_);
        reply = (redisReply *)redisCommand(context_, "incr %d", user_id);
    }
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER ||
        reply->integer <= 0) {
        freeReplyObject(reply);
        return 0;
    }
    int res_msg_id{reply->integer};
    freeReplyObject(reply);
    return res_msg_id;
}