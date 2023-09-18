#ifndef APICLIENT_NEWCLIENT_H
#define APICLIENT_NEWCLIENT_H

#include "json.hpp"
#include <cstdint>
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

    json getAllConversations(const std::string &userID,
                             const std::string &token);

    // sync msgs

    json syncMsgs(const std::string &userID, const std::string &token,
                  const std::string groupID, const std::string &toUserID,
                  int msgtype, int64_t fromSeq, int64_t toSeq);

    json syncGroupMsgs(const std::string &userID, const std::string &token,
                       const std::string &groupID, int64_t fromSeq,
                       int64_t toSeq);

    json syncSingleMsgs(const std::string &userID, const std::string &token,
                        const std::string &toUserID, int64_t fromSeq,
                        int64_t toSeq);

    // seq
    json getHasReadSeqAndMaxSeq(const std::string &userID,
                                const std::string &token,
                                const std::string &groupID,
                                const std::string &toUserID, int msgtype);

    json setHasReadSeq(const std::string &userID, const std::string &token,
                       const std::string &groupID, const std::string &toUserID,
                       int msgtype, int64_t seq);

    // group

    json createGroup(const std::string &userID, const std::string &token,
                     const std::string &groupId);

    json joinGroup(const std::string &userID, const std::string &token,
                   const std::string &groupId);

private:
    httplib::Client cli_;
};
#endif