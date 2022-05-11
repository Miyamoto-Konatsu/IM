#include "server/msgidserver/Redis.h"
int main() {
    Redis redis;
    auto id1 = redis.GetMsgId(1);
    assert(id1 == string("1"));
    id1 = redis.GetMsgId(1);
    assert(id1 == string("2"));
    return 0;
}