#ifndef MSGUTILS_UTILS_H
#define MSGUTILS_UTILS_H

#include <string>
#include "msg.pb.h"

std::string getSingleChatKey(const std::string &from, const std::string &to);
std::string getGroupChatKey(const std::string &groupId);

std::string getConversationIdForSingle(const std::string &from,
                                       const std::string &to);

std::string getConversationId(const ServerRpc::msg::msg &msg);
#endif // MSGUTILS_UTILS_H