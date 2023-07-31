#ifndef APICLIENT_NEWCLIENT_H
#define APICLIENT_NEWCLIENT_H

#include <httplib.h>
#include <string>
#include <thread>

using httpCallback = std::function<void(const httplib::Result &)>;

class ApiClient {
public:
    ApiClient(const std::string &host, int port) : cli_(host, port) {
    }

    // async
    void Post(const std::string &path, const std::string &body,
              const httpCallback &cb,
              const std::string &content_type = "application/json");

    // sync
    httplib::Result Post(const std::string &path, const std::string &body,
                         const std::string &content_type = "application/json");

    std::string authUserToken(const std::string &userID,
                              const std::string &password, std::string &secret,
                              int platform);

private:
    httplib::Client cli_;
};
#endif