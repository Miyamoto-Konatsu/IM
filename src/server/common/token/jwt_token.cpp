#include "jwt_token.h"
#include <chrono>
#include <cstdint>
#include <exception>
#include <jwt-cpp/traits/kazuho-picojson/defaults.h>

std::string createToken(const std::string &userID, int32_t platform,
                        int expireTimeSeconds) {
    std::chrono::seconds duration{expireTimeSeconds};
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
    auto userID = decoded_token.get_payload_claim("userID").as_string();
    auto platform = decoded_token.get_payload_claim("platform").as_string();
    auto expireAt = decoded_token.get_expires_at().time_since_epoch();
    //判断expireAt和现在的时间哪个更大
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto timeToLive = expireAt - now;
    auto timeToLiveSeconds =
        std::chrono::duration_cast<std::chrono::seconds>(timeToLive).count();
    return TokenInfo{userID, stoi(platform), timeToLiveSeconds};
}

std::string getTokenKey(std::string userID, int32_t platform) {
    return "IM_RPC_SERVER_AUTH:" + userID + +":" + std::to_string(platform);
}