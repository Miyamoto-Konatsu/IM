#include "jwt_token.h"
#include <chrono>
#include <jwt-cpp/traits/kazuho-picojson/defaults.h>

std::string createToken(const std::string &userID, int platform,
                        int expireTimeSeconds) {
    // 定义一个持续时间为 3600 秒
    std::chrono::seconds duration{3600};
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    auto expireAt = now + duration;
    std::string token =
        jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("userID", jwt::claim(userID))
            .set_payload_claim("platform", jwt::claim(std::to_string(platform)))
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(expireAt)
            .sign(jwt::algorithm::hs256{"secret"});
    return token;
}

TokenInfo parseToken(const std::string &token) {
    auto decoded_token = jwt::decode(token);
    auto userID = decoded_token.get_header_claim("userID").as_string();
    auto platform = decoded_token.get_header_claim("platform").as_string();
    auto expireAt = decoded_token.get_expires_at().time_since_epoch();
    //判断expireAt和现在的时间哪个更大
    auto liveTime = std::chrono::seconds{3600};
    auto timeToLive = expireAt - liveTime;
    // auto diff = std::chrono::duration_cast<std::chrono::seconds>(now -
    // expireAt);
    return TokenInfo{userID, stoi(platform), timeToLive.count()};
}