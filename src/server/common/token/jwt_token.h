#ifndef JTW_TOKEN_H
#define JTW_TOKEN_H

#include <cstdint>
#include <jwt-cpp/jwt.h>
#include <string>

struct TokenInfo {
    std::string userID;
    int32_t platform;
    long expireTimeSeconds; // token的剩余有效时间，单位是秒
};

std::string createToken(const std::string &userID, int32_t platform,
                        int expireTimeSeconds);
TokenInfo parseToken(const std::string &token);

std::string getTokenKey(std::string userID, int32_t platform);
#endif