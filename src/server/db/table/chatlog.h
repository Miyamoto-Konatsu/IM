#pragma once
#include "odb/core.hxx"
#include <string>
#include <cstring>


using namespace odb::core;

typedef unsigned long long uint64;
#pragma db object table("ChatLog")
class ChatLog {
public:
    ChatLog() {
    }

    ChatLog(const std::string &fromUserId, const std::string &toUserId,
            const std::string &content, const int64_t &time, const int64_t &seq,
            const int &platform, const int &msgType,
            const std::string &groupId
                ,const std::string& conversaionId) :
        content_(content),
        time_(time), seq_(seq), platform_(platform), msgType_(msgType) {
        strncpy(fromUserId_, fromUserId.c_str(), sizeof(fromUserId_) - 1);
        strncpy(toUserId_, toUserId.c_str(), sizeof(toUserId_) - 1);
        strncpy(groupId_, groupId.c_str(), sizeof(groupId_) - 1);
        strncpy(conversaionId_, conversaionId.c_str(),
                sizeof(conversaionId_) - 1);
    }
    //  getter 和 setter 函数

    const uint64 &id() const {
        return id_;
    }

    std::string fromUserId() const {
        return fromUserId_;
    }

    void fromUserId(const std::string &fromUserId) {
        strncpy(fromUserId_, fromUserId.c_str(), sizeof(fromUserId_) - 1);
    }

    std::string toUserId() const {
        return toUserId_;
    }

    void toUserId(const std::string &toUserId) {
        strncpy(toUserId_, toUserId.c_str(), sizeof(toUserId_) - 1);
    }

    const std::string &content() const {
        return content_;
    }

    void content(const std::string &content) {
        content_ = content;
    }

    const int64_t &time() const {
        return time_;
    }

    void time(const int64_t &time) {
        time_ = time;
    }

    const int64_t &seq() const {
        return seq_;
    }

    void seq(const int64_t &seq) {
        seq_ = seq;
    }

    const int &platform() const {
        return platform_;
    }

    void platform(const int &platform) {
        platform_ = platform;
    }

    const int &msgType() const {
        return msgType_;
    }

    void msgType(const int &msgType) {
        msgType_ = msgType;
    }

    std::string groupId() const {
        return groupId_;
    }

    void groupId(const std::string &groupId) {
        strncpy(groupId_, groupId.c_str(), sizeof(groupId_) - 1);
    }

     std::string conversaionId() const {
        return conversaionId_;
    }

    void conversaionId(const std::string &conversaionId) {
        strncpy(conversaionId_, conversaionId.c_str(),
                sizeof(conversaionId_) - 1);
    }
private:
    friend class odb::access;
#pragma db id auto
    uint64 id_;

#pragma db not_null
    char fromUserId_[32] = {0};
#pragma db not_null
    char toUserId_[32] = {0};
#pragma db not_null
    char conversaionId_[64] = {0};
#pragma db not_null
    std::string content_;
#pragma db not_null
    int64_t time_;
#pragma db not_null
    int64_t seq_;
#pragma db not_null
    int platform_;
#pragma db not_null
    int msgType_;
#pragma db not_null
    char groupId_[32] = {0};
#pragma db index("conversaionIndex") unique members(conversaionId_, seq_)
};