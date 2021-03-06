#include "aes128.hpp"
string KEYWORD = "uaYBHtznvMU45n4f";
unsigned char s_box[16][16] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 // F
};

unsigned char reverse_s_box[16][16] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
    0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
    0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
    0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
    0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
    0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
    0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
    0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
    0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
    0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
    0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // A
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
    0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // B
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
    0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // C
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
    0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // D
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
    0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // E
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
    0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d // F
};

unsigned char e_mix_cloumn[4][4] = {0x02, 0x03, 0x01, 0x01, 0x01, 0x02,
                                    0x03, 0x01, 0x01, 0x01, 0x02, 0x03,
                                    0x03, 0x01, 0x01, 0x02};

unsigned char reverse_mix_cloumn[4][4] = {0x0E, 0x0B, 0x0D, 0x09, 0x09, 0x0E,
                                          0x0B, 0x0D, 0x0D, 0x09, 0x0E, 0x0B,
                                          0x0B, 0x0D, 0x09, 0x0E};

unsigned int rcon[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000,
                         0x10000000, 0x20000000, 0x40000000, 0x80000000,
                         0x1B000000, 0x36000000};

unsigned int bytes2word(const char *value) {
    return (((int)value[0] & 0x000000FF) << 24) |
           (((int)value[1] & 0x000000FF) << 16) |
           (((int)value[2] & 0x000000FF) << 8) | ((int)value[3] & 0x000000FF);
}

unsigned int T(const unsigned int *word, const int round) {
    unsigned char bt0 = (*word & 0xFF000000) >> 24;
    unsigned int shiftlift = (*word & 0x00FF0000) << 8 |
                             (*word & 0x0000FF00) << 8 |
                             (*word & 0x000000FF) << 8 | bt0;
    char new_word[4];
    for (int i = 0; i < 4; i++) {
        unsigned char tmp =
            (shiftlift & (0xFF000000 >> (8 * i))) >> (8 * (3 - i));
        short row = (tmp & 0xF0) >> 4;
        short cloumn = tmp & 0x0F;
        new_word[i] = s_box[row][cloumn];
    }
    return ((((int)new_word[0] << 24) & 0xFF000000) |
            (((int)new_word[1] << 16) & 0x00FF0000) |
            (((int)new_word[2] << 8) & 0x0000FF00) |
            ((int)new_word[3] & 0x000000FF)) ^
           rcon[round];
}

//?????????????????????????????????4?????????16?????????????????????44??????
void extern_key(const char *key, unsigned int *out_w) {
    for (int i = 0; i < 4; i++) {
        out_w[i] = bytes2word(key + 4 * i);
        // printf("0x%x ", out_w[i]);
    }

    int round = 0;
    //??????????????????
    for (int i = 4; i < 44; i++) {
        if (i % 4 != 0) {
            out_w[i] = out_w[i - 4] ^ out_w[i - 1];
        } else {
            out_w[i] = out_w[i - 4] ^ T(&out_w[i - 1], round);
            round++;
        }
        // printf("0x%x ", out_w[i]);
    }
}

//??????????????????
void sub_bytes(unsigned char *context, int encode) {
    // encode=1???????????????S??????????????????=0??????????????????S???????????????
    for (int index = 0; index < 16; index++) {
        int row = (context[index] & 0xF0) >> 4;
        int cloumn = context[index] & 0x0F;
        if (encode == 1) {
            context[index] = s_box[row][cloumn];
        } else {
            context[index] = reverse_s_box[row][cloumn];
        }
    }
}

//?????????
void shift_rows(unsigned char *context, int encode) {
    // encode=1?????????????????????????????????, = 0:??????????????????????????????
    //???16???????????????4*4????????????
    char two_dimensional_array[4][4];
    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < 4; cloumn++) {
            two_dimensional_array[row][cloumn] = context[row + 4 * cloumn];
        }
    }
    //?????????????????????
    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < row; cloumn++) {
            if (encode == 1) {
                //?????????????????????
                char tmp = two_dimensional_array[row][0];
                two_dimensional_array[row][0] = two_dimensional_array[row][1];
                two_dimensional_array[row][1] = two_dimensional_array[row][2];
                two_dimensional_array[row][2] = two_dimensional_array[row][3];
                two_dimensional_array[row][3] = tmp;
            } else {
                //?????????????????????
                char tmp = two_dimensional_array[row][3];
                two_dimensional_array[row][3] = two_dimensional_array[row][2];
                two_dimensional_array[row][2] = two_dimensional_array[row][1];
                two_dimensional_array[row][1] = two_dimensional_array[row][0];
                two_dimensional_array[row][0] = tmp;
            }

            *(context + 4 * row + cloumn) = two_dimensional_array[cloumn][row];
        }
    }

    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < 4; cloumn++) {
            *(context + 4 * row + cloumn) = two_dimensional_array[cloumn][row];
        }
    }
}

int GFMul_2(int s) {
    int result = s << 1;
    int bit_7 = result & 0x00000100;
    if (bit_7 != 0) {
        result &= 0x000000FF; //?????????????????????
        result ^= 0x0000001B; //????????????00011011??????????????????
    }
    return result;
}

int GFMul_3(int s) { return GFMul_2(s) ^ s; }

int GFMul_4(int s) { return GFMul_2(GFMul_2(s)); }

int GFMul_8(int s) { return GFMul_2(GFMul_4(s)); }

int GFMul_9(int s) { return GFMul_8(s) ^ s; }

int GFMul_11(int s) { return GFMul_9(s) ^ GFMul_2(s); }

int GFMul_12(int s) { return GFMul_8(s) ^ GFMul_4(s); }

int GFMul_13(int s) { return GFMul_12(s) ^ s; }

int GFMul_14(int s) { return GFMul_12(s) ^ GFMul_2(s); }

//????????????
int emix_mul(int n, int s) {
    int rst = 0;
    switch (n) {
    case 0x01:
        rst = s;
        break;
    case 0x02:
        rst = GFMul_2(s);
        break;
    case 0x03:
        rst = GFMul_3(s);
        break;
    case 0x09:
        rst = GFMul_9(s);
        break;
    case 0x0B:
        rst = GFMul_11(s);
        break;
    case 0x0D:
        rst = GFMul_13(s);
        break;
    case 0x0E:
        rst = GFMul_14(s);
        break;
    }
    return rst;
}

//???????????????
void mix_cloumns(unsigned char *context, int encode) {
    //???16???????????????4*4????????????
    char two_dimensional_array[4][4] = {0};
    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < 4; cloumn++) {
            two_dimensional_array[row][cloumn] = context[row + 4 * cloumn];
        }
    }

    char rst[4][4] = {0};
    //?????????????????????
    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < 4; cloumn++) {
            if (encode == 1) {
                rst[row][cloumn] = emix_mul(e_mix_cloumn[row][0],
                                            two_dimensional_array[0][cloumn]) ^
                                   emix_mul(e_mix_cloumn[row][1],
                                            two_dimensional_array[1][cloumn]) ^
                                   emix_mul(e_mix_cloumn[row][2],
                                            two_dimensional_array[2][cloumn]) ^
                                   emix_mul(e_mix_cloumn[row][3],
                                            two_dimensional_array[3][cloumn]);
            } else {
                rst[row][cloumn] = emix_mul(reverse_mix_cloumn[row][0],
                                            two_dimensional_array[0][cloumn]) ^
                                   emix_mul(reverse_mix_cloumn[row][1],
                                            two_dimensional_array[1][cloumn]) ^
                                   emix_mul(reverse_mix_cloumn[row][2],
                                            two_dimensional_array[2][cloumn]) ^
                                   emix_mul(reverse_mix_cloumn[row][3],
                                            two_dimensional_array[3][cloumn]);
            }
        }
    }

    //?????????context
    for (int row = 0; row < 4; row++) {
        for (int cloumn = 0; cloumn < 4; cloumn++) {
            *(context + 4 * row + cloumn) = rst[cloumn][row];
        }
    }
}

//??????????????????
void add_round_key(unsigned char *context, const unsigned int *keyword) {
    for (int i = 0; i < 4; i++) {
        //??????????????????
        unsigned int tmp = bytes2word((char *)&context[4 * i]);
        //????????????
        tmp = tmp ^ keyword[i];
        // S -> S'
        context[4 * i] = (tmp & 0xFF000000) >> 24;
        context[4 * i + 1] = (tmp & 0x00FF0000) >> 16;
        context[4 * i + 2] = (tmp & 0x0000FF00) >> 8;
        context[4 * i + 3] = (tmp & 0x000000FF);
    }
}

void convert_to_array(const unsigned char *p, int array[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[j][i] = (int)*(p + 4 * i + j) & 0x000000FF;
        }
    }
}

/*?????????????????????????????????AES128???bit????????????????????????ECB?????????????????????????????????PKCS5??????
 *param 1:??????????????????
 *param 2:???????????????
 *param 3:?????????????????????????????????16???????????????????????????
 *param 4:????????????????????????????????????
 *param 5:??????????????????*/
int encrpyt_aes128(const char *context, const int cb, const char *key_words,
                   unsigned char **output_context, int *out_cb) {
    int key_len = strlen(key_words);
    //???????????????????????????????????????
    if (key_len != 16) {
        return -1;
    }
    unsigned char *buffer = nullptr;
    int buffer_len = 0;
    //????????????????????????128bit???????????????16???????????????????????????????????????????????????????????????
    //???????????????????????????128bit???????????????????????????16????????????16
    int mod = cb % 16;
    if (mod != 0) {
        int lack = 16 - mod;
        buffer_len = cb + lack;
        buffer = new unsigned char[buffer_len + 1];
        memset(buffer, 0, buffer_len + 1);
        memcpy(buffer, context, cb);
        for (int i = 0; i < lack; i++) {
            memcpy(buffer + cb + i, &lack, 1);
        }
    } else {
        buffer_len = cb + 16;
        buffer = new unsigned char[buffer_len + 1];
        memset(buffer, 0, buffer_len + 1);
        memcpy(buffer, context, cb);
        int lack = 16;
        for (int i = 0; i < 16; i++) {
            memcpy(buffer + cb + i, &lack, 1);
        }
    }
    //??????????????????44???word
    unsigned int keywords_extern[44] = {0};
    extern_key(key_words, keywords_extern);
    int array[4][4] = {0};
    //????????????????????????????????????
    for (int index = 0; index < buffer_len / 16; index++) {
        //???16??????????????????4*4???????????????????????????
        convert_to_array(buffer + index * 16, array);
        //??????????????????
        add_round_key(&buffer[index * 16], &keywords_extern[0]);
        //??????1???9???????????????
        for (int count = 0; count < 9; count++) {
            //????????????
            sub_bytes(&buffer[index * 16], 1);
            //?????????
            shift_rows(&buffer[index * 16], 1);
            //?????????
            mix_cloumns(&buffer[index * 16], 1);
            //????????????
            add_round_key(&buffer[index * 16],
                          &keywords_extern[4 * (count + 1)]);
        }
        //???????????????????????????
        //????????????
        sub_bytes(&buffer[index * 16], 1);
        //?????????
        shift_rows(&buffer[index * 16], 1);
        //????????????
        add_round_key(&buffer[index * 16], &keywords_extern[40]);
    }
    *output_context = buffer;
    *out_cb = buffer_len;
    return 0;
}

/**??????????????????
 *param 1:????????????
 *param 2:??????????????????
 *param 3:??????
 *param 4:????????????????????????
 *param 5:??????????????????????????????
 */
int decode_aes128(unsigned char *context, const int cb, const char *key_words,
                  unsigned char **output_context, int *out_cb) {
    int key_len = strlen(key_words);
    //???????????????????????????????????????
    if (key_len != 16) {
        return -1;
    }
    //????????????????????????????????????
    if (cb == 0 || cb % 16 != 0) {
        return -1;
    }
    //????????????
    unsigned int keywords_extern[44];
    extern_key(key_words, keywords_extern);
    //??????????????????
    for (int index = 0; index < cb / 16; index++) {
        //??????????????????
        add_round_key(&context[16 * index], &keywords_extern[40]);
        for (int count = 9; count >= 0; count--) {
            //???????????????
            shift_rows(&context[16 * index], 0);
            //??????????????????
            sub_bytes(&context[16 * index], 0);
            //??????????????????
            add_round_key(&context[16 * index], &keywords_extern[count * 4]);
            if (count != 0) {
                //???????????????
                mix_cloumns(&context[16 * index], 0);
            }
        }
    }
    //????????????????????????????????????
    int lack = 0;
    bool is_pck5 = true;
    memcpy(&lack, &context[cb - 1], 1);
    for (int i = 0; i < lack; i++) {
        if (context[cb - 1 - i] != lack) {
            is_pck5 = false;
            break;
        }
    }
    if (is_pck5) {
        *out_cb = cb - lack;
    } else {
        *out_cb = cb;
    }
    *output_context = new unsigned char[*out_cb + 1];
    memset(*output_context, 0, *out_cb + 1);
    memcpy(*output_context, context, *out_cb);
    return 0;
}

//??????????????????
void free_memory(unsigned char *ptr) {
    if (ptr) {
        delete[] ptr;
    }
}

//
std::string decrypt_aes128_str(const std::string &mi_wen,
                               const std::string &key) {
    if (mi_wen.empty() || key.empty()) {
        printf("current decrypt context or key is empty.");
        return "";
    }
    std::string rst;
    unsigned char *output = nullptr;
    int cb = 0;
    if (decode_aes128((unsigned char *)mi_wen.c_str(), mi_wen.size(),
                      key.c_str(), &output, &cb) < 0) {
        printf("failed to decrypt aes128 context");
        return "";
    }
    rst.append((char *)output, cb);
    free_memory(output);
    return rst;
}

std::string encrypt_aes128_str(const std::string &ming_wen,
                               const std::string &key) {
    if (ming_wen.empty() || key.empty()) {
        printf("current encrypt context or key is empty.");
        return "";
    }
    std::string rst;
    unsigned char *output = nullptr;
    int cb = 0;
    if (encrpyt_aes128(ming_wen.c_str(), ming_wen.size(), key.c_str(), &output,
                       &cb) < 0) {
        printf("failed to encrypt aes128 context");
        return "";
    }
    rst.append((char *)output, cb);
    free_memory(output);
    return rst;
}

//#include "aes128.hpp"
using namespace std;
/****************************************************************************
????????????: ??????????????????????????????????????????ASSCI????????????
                ??????????????????boost::algorithm::hex??????
?????????	??????????????????123????????????????????????????????????313233???
*****************************************************************************/
void str2hex(char *dst,const unsigned char *src, int src_len) {
    for (int i = 0; i < src_len; i++) {
        sprintf(dst, "%02x", src[i]);
        dst += 2;
    }
}
/****************************************************************************
????????????: ??????????????????ASSCI????????????????????????????????????
                ??????????????????boost::algorithm::unhex??????
?????????	??????????????????313233????????????????????????????????????123???
*****************************************************************************/
void hex2str(char *dst, const char *src, int src_len) {
    for (int i = 0; i < src_len; i += 2) {
        unsigned char high, low;
        high = toupper(src[i]);
        low = toupper(src[i + 1]);
        (high > 0x39) ? (high -= 0x37) : (high -= 0x30);
        (low > 0x39) ? (low -= 0x37) : (low -= 0x30);
        dst[i / 2] = (high << 4) | low;
    }
}
/*
int main(int argc, char *argv[]) {
    string encrypt;
    {
        string ming_wen =
            "what is your name ? where are you from?what is your name ? where "
            "are you from?what is your name ? where are you from?what is your "
            "name ? where are you from?what is your name ? where are you "
            "from?what is your name ? where are you from?what is your name ? "
            "where are you from?what is your name ? where are you from?what is "
            "your name ? where are you from?";
        string keywords = "uaYBHtznvMU45n4f";
        auto mi_wen = encrypt_aes128_str(ming_wen, keywords);
        char mi_wen_hex[1024] = {0};
        str2hex(mi_wen_hex, (unsigned char *)mi_wen.c_str(), mi_wen.size());
        encrypt.assign(mi_wen_hex, strlen(mi_wen_hex));
        cout << "?????????????????????" << encrypt << endl;
        cout << mi_wen.size() << ' ' << strlen(mi_wen_hex) << ' '
             << ming_wen.size() << endl;
    }
    ///
    {
        string keywords = "uaYBHtznvMU45n4f";
        char mi_wen[1024] = {0};
        hex2str(mi_wen, encrypt.c_str(), encrypt.size());
        auto ming_wen = decrypt_aes128_str(mi_wen, keywords);
        cout << "?????????????????????" << ming_wen << endl;
    }
    return 0;
}
*/