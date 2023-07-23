#ifndef MSG_CACHE_H
#define MSG_CACHE_H

#include "common.h"
#include <cstdint>

class MsgCache : public Cache {
public:
    MsgCache();
    ~MsgCache();

    int64_t getConversionMaxId(const std::string &key);
    bool setConversionMaxId(const std::string &key, int64_t id);
};
#endif // MSG_CACHE_H