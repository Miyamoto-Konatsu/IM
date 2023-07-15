#include "server/db/Redis.h"

using namespace std;

Redis::Redis() : redis_alive_(true) {
    RedisConnect(&this->subscribe_context_);
    RedisConnect(&this->publish_context_);
}
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

void Redis::SetSubscribeCallback(subscribe_callback&& sc) {
    message_handler_ = thread(&Redis::MessageHandler, this, std::move(sc));
    message_handler_.detach();
}

void Redis::MessageHandler(subscribe_callback&& sc) {
    while (true) {
        if (this->subscribe_context_ == nullptr) {
            RedisConnect(&this->subscribe_context_);
            if (this->subscribe_context_ == nullptr) {
                printf(" Can't allocate redis context \n ");
                return;
            }
        }
        redisReply *reply;
        void *_reply = nullptr;
        if (redisGetReply(this->subscribe_context_, &_reply) != REDIS_OK) {
            continue;
        }
        reply = (redisReply *)_reply;
        if (reply->type != REDIS_REPLY_ARRAY || reply->elements != 3 ||
            reply->element[2]->str == nullptr) {
            freeReplyObject(reply);
            continue;
        }
        // printf("%s\n", reply->element[2]->str);
        sc(stoi(string(reply->element[1]->str)),
           string(reply->element[2]->str));
        freeReplyObject(reply);
    }
}

Redis::~Redis() {
    redisFree(subscribe_context_);
    redisFree(publish_context_);
    subscribe_context_ = nullptr;
    publish_context_ = nullptr;
}

bool Redis::Subscribe(int user_id) {
    redisAppendCommand(subscribe_context_, "subscribe %d", user_id);
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->subscribe_context_, &done)) {
            cerr << "subscribe command failed!" << endl;
            return false;
        }
    }
    /*   if (status == nullptr) {
          RedisConnect(&this->subscribe_context_);
          reply = (redisReply *)redisCommand(subscribe_context_, "subscribe %d",
                                             user_id);
      }
      if (reply == nullptr || reply->type == REDIS_REPLY_ERROR) {
          freeReplyObject(reply);
          return false;
      }
      freeReplyObject(reply); */
    return true;
}

bool Redis::Unsubscribe(int user_id) {
    /*  redisReply *reply = (redisReply *) */ redisAppendCommand(
        subscribe_context_, "unsubscribe %d", user_id);
    /*if (reply == nullptr) {
        RedisConnect(&this->subscribe_context_);
        reply = (redisReply *)redisCommand(subscribe_context_, "unsubscribe %d",
                                           user_id);
    }
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply); */
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->subscribe_context_, &done)) {
            cerr << "subscribe command failed!" << endl;
            return false;
        }
    }
    return true;
}

bool Redis::Publish(int user_id, const string &message) {
    redisReply *reply = (redisReply *)redisCommand(
        publish_context_, "publish %d %s", user_id, message.c_str());
    if (reply == nullptr) {
        RedisConnect(&this->publish_context_);
        reply = (redisReply *)redisCommand(publish_context_, "publish %d %s",
                                           user_id, message.c_str());
    }
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

bool Redis::SignIn(int user_id) {
    redisReply *reply = (redisReply *)redisCommand(
        publish_context_, "sadd online_user %d ", user_id);
    if (reply == nullptr) {
        RedisConnect(&this->publish_context_);
        reply = (redisReply *)redisCommand(publish_context_,
                                           "sadd online_user %d ", user_id);
    }
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER ||
        reply->integer != 1) {
        freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

bool Redis::IsOnline(int user_id) {
    redisReply *reply = (redisReply *)redisCommand(
        publish_context_, "sismember online_user %d ", user_id);
    if (reply == nullptr) {
        RedisConnect(&this->publish_context_);
        reply = (redisReply *)redisCommand(
            publish_context_, "sismember online_user %d ", user_id);
    }
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER ||
        reply->integer != 1) {
        freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

void Redis::SignOut(int user_id) {
    redisReply *reply = (redisReply *)redisCommand(
        publish_context_, "srem online_user %d ", user_id);
    if (reply == nullptr) {
        RedisConnect(&this->publish_context_);
        reply = (redisReply *)redisCommand(publish_context_,
                                           "srem online_user %d ", user_id);
    }
    freeReplyObject(reply);
}