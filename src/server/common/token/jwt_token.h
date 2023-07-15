#ifndef JTW_TOKEN_H
#define JTW_TOKEN_H

#include <cstdint>
#include <jwt-cpp/jwt.h>
#include <string>

struct TokenInfo {
    std::string userID;
    int32_t platform;
    long expireTimeSeconds;
};

std::string createToken(const std::string &userID, int32_t platform,
                        int expireTimeSeconds);
TokenInfo parseToken(const std::string &token);

#endif