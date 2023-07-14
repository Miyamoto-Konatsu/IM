#ifndef JTW_TOKEN_H
#define JTW_TOKEN_H

#include <jwt-cpp/jwt.h>
#include <string>

struct TokenInfo {
    std::string userID;
    int platform;
    long expireTimeSeconds;
};

std::string createToken(const std::string &userID, int platform,
                        int expireTimeSeconds);
TokenInfo parseToken(const std::string &token);

#endif