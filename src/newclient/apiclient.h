#ifndef APICLIENT_NEWCLIENT_H
#define APICLIENT_NEWCLIENT_H

#include "json.hpp"
#include <httplib.h>
#include <string>
#include <thread>

using nlohmann::json;

using httpCallback = std::function<void(const httplib::Result &)>;

class ApiClient {
public:
    ApiClient(const std::string &host, int port) : cli_(host, port) {
    }

    // async
    void Post(const std::string &path, const std::string &body,
              const httpCallback &cb, const httplib::Headers &headers = {},
              const std::string &content_type = "application/json");

    // sync
    httplib::Result Post(const std::string &path, const std::string &body,
                         const httplib::Headers &headers = {},
                         const std::string &content_type = "application/json");

    std::string authUserToken(const std::string &userID,
                              const std::string &password, std::string &secret,
                              int platform);

    // conversation

    json getConversation(const std::string &userID, const std::string &token,
                         const std::string &conversationID);

    json getAllConversations(const std::string& userID, const std::string& token);

private:
    httplib::Client cli_;
};
#endif