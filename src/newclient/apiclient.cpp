#include "apiclient.h"
#include "httplib.h"
#include "json.hpp"
#include "constant/msg.h"
#include <exception>
#include <stdexcept>

httplib::Result ApiClient::Post(const std::string &path,
                                const std::string &body,
                                const httplib::Headers &headers,
                                const std::string &content_type) {
    return cli_.Post(path.c_str(), headers, body, content_type.c_str());
}

void ApiClient::Post(const std::string &path, const std::string &body,
                     const httpCallback &cb, const httplib::Headers &headers,
                     const std::string &content_type) {
    std::thread t([=, this]() {
        auto res =
            this->cli_.Post(path.c_str(), headers, body, content_type.c_str());
        cb(res);
    });

    t.detach();
}

std::string ApiClient::authUserToken(const std::string &userID,
                                     const std::string &password,
                                     std::string &secret, int platform) {
    std::string path = "/auth/userToken";
    nlohmann::json j;
    j["userID"] = userID;
    j["password"] = password;
    j["platformID"] = platform;
    j["secret"] = secret;
    std::string body = j.dump();
    httplib::Result res = Post(path, body);
    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data["token"];
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("auth user token failed");
}

json ApiClient::getAllConversations(const std::string &userID,
                                    const std::string &token) {
    std::string path = "/conversation/getAllConversations";
    nlohmann::json data;
    data["ownerUserID"] = userID;
    std::string body = data.dump();
    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);
    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            return j["data"];
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("get conversation failed");
}