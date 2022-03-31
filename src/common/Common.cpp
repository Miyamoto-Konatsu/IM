#include "Common.h"

#include <muduo/net/TcpClient.h>
inline uint32_t PacketLength(const string &js) {
    return js.size() + 1 + PACKET_HEADER_LENGTH;
}

char *GeneratePacket(const string &js) {
    uint32_t data_length = strlen(js.c_str()) + 1;
    uint32_t packet_length = PacketLength(js);
    char *data = (char *)malloc(packet_length);

    *(uint32_t *)data = muduo::net::sockets::hostToNetwork32(data_length);
    if (data == nullptr) {
        return nullptr;
    }
    strcpy(data + PACKET_HEADER_LENGTH, js.c_str());
    return data;
}