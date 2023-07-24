#ifndef MSG_CACHE_H
#define MSG_CACHE_H

#include "common.h"
#include <cstdint>

class MsgCache : public Cache {
public:
    MsgCache();
    ~MsgCache();

    int64_t getConversationMaxId(const std::string &key);
    bool setConversationMaxId(const std::string &key, int64_t id);
};
#endif // MSG_CACHE_H