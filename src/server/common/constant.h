#ifndef CONSTANT_SERVER_H
#define CONSTANT_SERVER_H

#include "constant/msg.h"
#define SERVER_PORT 50051
#define SERVER_ADDRESS "0.0.0.0"

// token
#define TOKEN_EXPIRE_TIME_SECONDS (60 * 60 * 24) // one day

#define SINGLE_CHAT_TYPE TCP_MSG_SINGLE_CHAT_TYPE
#define GROUP_CHAT_TYPE TCP_MSG_GROUP_CHAT_TYPE
#endif