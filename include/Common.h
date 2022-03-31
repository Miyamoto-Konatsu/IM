#ifndef COMMON_H
#define COMMON_H
#include <cstdint>
#include <string>
using namespace std;
const int PACKET_HEADER_LENGTH = 4;
const int MAX_DATA_LENGTH = 4096;

inline uint32_t PacketLength(const string &js);

char *GeneratePacket(const string &js);

#endif