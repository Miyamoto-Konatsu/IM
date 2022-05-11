#ifndef COMMON_H
#define COMMON_H
#include <cstdint>
#include <memory>
#include <string>
#include "sha256.hpp"
using namespace std;
const int PACKET_HEADER_LENGTH = 4;
const int MAX_DATA_LENGTH = 4096;

shared_ptr<char> GeneratePacket(const string &js, uint32_t &packet_length);
string DecryptPacket( string &&old_packet_hex);
string EncryptPassword(const string& password);
bool CheckPassword(const string& password, const string& encrypted_password);
#endif