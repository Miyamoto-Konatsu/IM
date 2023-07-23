#ifndef MSGUTILS_UTILS_H
#define MSGUTILS_UTILS_H


#include <string>

std::string getSingleChatKey(const std::string &from, const std::string &to);
std::string getConversionIdForSingle(const std::string &from,
                                     const std::string &to);

#endif //MSGUTILS_UTILS_H