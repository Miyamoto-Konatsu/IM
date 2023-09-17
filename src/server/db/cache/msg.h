#ifndef MSG_CACHE_H
#define MSG_CACHE_H

#include "common.h"
#include <cstdint>
#include <utility>

class MsgCache : public Cache {
public:
    MsgCache();
    ~MsgCache();

    int64_t getConversationMaxId(const std::string &key);
    bool setConversationMaxId(const std::string &key, int64_t id);

    void setHasReadSeqs(const std::string &conversationId,const std::unordered_map<std::string, int64_t> &userHasRead);
    std::string getConversationIdSeqKey(const std::string &conversationId);

    std::pair<int64_t, int64_t> getHasReadSeqAndMaxSeq(const std::string &conversationId, const std::string &userid);
};
#endif // MSG_CACHE_H