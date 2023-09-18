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
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("get conversation failed");
}

json ApiClient::syncMsgs(const std::string &userID, const std::string &token,
                         const std::string groupID, const std::string &toUserID,
                         int msgtype, int64_t fromSeq, int64_t toSeq) {
    // string fromUserID = 1;
    // string toUserID = 2;
    // string groupID = 3;
    // int32 msgType = 4;
    // int64 startSeq = 5;
    // int64 endSeq = 6;
    std::string path = "/msg/syncMsgs";
    nlohmann::json data;
    data["fromUserID"] = userID;
    data["toUserID"] = toUserID;
    data["groupID"] = groupID;
    data["msgType"] = msgtype;
    data["startSeq"] = fromSeq;
    data["endSeq"] = toSeq;
    std::string body = data.dump();
    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);

    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("sync msgs failed");
}

json ApiClient::syncSingleMsgs(const std::string &userID,
                               const std::string &token,
                               const std::string &toUserID, int64_t fromSeq,
                               int64_t toSeq) {
    return syncMsgs(userID, token, "", toUserID, TCP_MSG_SINGLE_CHAT_TYPE, fromSeq, toSeq);
}

json ApiClient::syncGroupMsgs(const std::string &userID,
                              const std::string &token,
                              const std::string &groupID, int64_t fromSeq,
                              int64_t toSeq) {
    return syncMsgs(userID, token, groupID, "", TCP_MSG_GROUP_CHAT_TYPE, fromSeq, toSeq);
}

json ApiClient::getHasReadSeqAndMaxSeq(const std::string &userID,
                                       const std::string &token,
                                       const std::string &groupID,
                                       const std::string &toUserID,
                                       int msgtype) {
    // string fromUserID = 1;
    // string toUserID = 2;
    // string groupID = 3;
    // int32 msgType = 4;
    std::string path = "/msg/getHasReadSeqAndMaxSeq";
    nlohmann::json data;
    data["fromUserID"] = userID;
    data["toUserID"] = toUserID;
    data["groupID"] = groupID;
    data["msgType"] = msgtype;
    std::string body = data.dump();
    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);

    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("get has read seq and max seq failed");
}

json ApiClient::setHasReadSeq(const std::string &userID,
                              const std::string &token,
                              const std::string &groupID,
                              const std::string &toUserID, int msgtype,
                              int64_t seq) {
    // string fromUserID = 1;
    // string toUserID = 2;
    // string groupID = 3;
    // int32 msgType = 4;
    // int64 seq = 5;
    std::string path = "/msg/setHasReadSeq";
    nlohmann::json data;
    data["fromUserID"] = userID;
    data["toUserID"] = toUserID;
    data["groupID"] = groupID;
    data["msgType"] = msgtype;
    data["seq"] = seq;
    std::string body = data.dump();
    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);

    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("set has read seq failed");
}

json ApiClient::createGroup(const std::string &userID, const std::string &token,
                            const std::string &groupId) {
    std::string path = "/group/createGroup";
    nlohmann::json data;
    data["groupOwnerId"] = userID;
    data["groupId"] = groupId;
    std::string body = data.dump();

    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);

    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("set has read seq failed");
}

json ApiClient::joinGroup(const std::string &userID, const std::string &token,
                          const std::string &groupId) {
    std::string path = "/group/joinGroup";
    nlohmann::json data;
    data["userID"] = userID;
    data["groupID"] = groupId;
    std::string body = data.dump();

    httplib::Headers parameter;
    parameter.insert({"token", token});
    httplib::Result res = Post(path, body, parameter);

    if (res) {
        if (res->status != 200) { throw std::runtime_error(res->body); }
        nlohmann::json j = nlohmann::json::parse(res->body);
        if (j["code"] == MSG_CODE_SUCCESS) {
            nlohmann::json data =
                nlohmann::json::parse(j["data"].get<std::string>());
            return data;
        } else {
            std::string errerMsg = j["error_message"];
            throw std::runtime_error(errerMsg);
        }
    }
    throw std::runtime_error("set has read seq failed");
}