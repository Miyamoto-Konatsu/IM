#ifndef COMMON_H
#define COMMON_H
#include "sha256.hpp"
#include <cstdint>
#include <memory>
#include <string>
using namespace std;

#define DISABLE_COPY_AND_MOVE(_CLASS_NAME)                                     \
    _CLASS_NAME(const _CLASS_NAME &) = delete;                                 \
    _CLASS_NAME &operator=(const _CLASS_NAME &) = delete;                      \
    _CLASS_NAME(_CLASS_NAME &&) = delete;                                      \
    _CLASS_NAME &operator=(_CLASS_NAME &&) = delete;
    
const int PACKET_HEADER_LENGTH = 4;
const int MAX_DATA_LENGTH = 4096;

typedef int UserIdType;

shared_ptr<char> GeneratePacket(const string &js, uint32_t &packet_length);
string DecryptPacket(string &&old_packet_hex);
string EncryptPassword(const string &password);
bool CheckPassword(const string &password, const string &encrypted_password);

#endif