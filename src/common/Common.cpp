#include "Common.h"
#include "aes128.hpp"
#include <muduo/net/TcpClient.h>

shared_ptr<char> GeneratePacket(const string &js, uint32_t &packet_length) {

    auto text_encrypt = encrypt_aes128_str(js, KEYWORD);
    packet_length = 2 * text_encrypt.size() + PACKET_HEADER_LENGTH;
    char *data = (char *)malloc(packet_length);
    if (data == nullptr) {
        return nullptr;
    }
    *(uint32_t *)data =
        /*muduo::net::sockets::hostToNetwork32*/ packet_length -
        PACKET_HEADER_LENGTH;
    str2hex(data + PACKET_HEADER_LENGTH,
            (const unsigned char *)text_encrypt.c_str(), text_encrypt.size());
    return shared_ptr<char>(data);
}

string DecryptPacket(string &&old_packet_hex) {
    string old_packet_str;
    old_packet_str.reserve(old_packet_hex.size() / 2);
    old_packet_str.resize(old_packet_hex.size() / 2);
    hex2str(&old_packet_str[0], old_packet_hex.c_str(), old_packet_hex.size());
    auto packet = decrypt_aes128_str(old_packet_str, KEYWORD);
    return packet;
}

string EncryptPassword(const string &password) {
    sha256::Sha256 sha256;
    return sha256.getHexMessageDigest(password);
}

bool CheckPassword(const string &password, const string &encrypted_password) {
    return EncryptPassword(password) == encrypted_password;
}