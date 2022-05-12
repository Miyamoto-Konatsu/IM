// aes128.hpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
extern string KEYWORD;

extern unsigned char s_box[16][16];

extern unsigned char reverse_s_box[16][16];

extern unsigned char e_mix_cloumn[4][4];

extern unsigned char reverse_mix_cloumn[4][4];

extern unsigned int rcon[10];

extern unsigned int bytes2word(const char *value);

extern unsigned int T(const unsigned int *word, const int round);
//密钥扩展函数，将密钥由4个字（16个字节）扩展成44个字
extern void extern_key(const char *key, unsigned int *out_w);

//字节代换处理
extern void sub_bytes(unsigned char *context, int encode);

//行位移
extern void shift_rows(unsigned char *context, int encode);

extern int GFMul_2(int s);

extern int GFMul_3(int s);

extern int GFMul_4(int s);

extern int GFMul_8(int s);

extern int GFMul_9(int s);

extern int GFMul_11(int s);

extern int GFMul_12(int s);

extern int GFMul_13(int s);

extern int GFMul_14(int s);

//二元运算
extern int emix_mul(int n, int s);
//列混淆操作
extern void mix_cloumns(unsigned char *context, int encode);

//轮密钥加处理
extern void add_round_key(unsigned char *context, const unsigned int *keyword);

extern void convert_to_array(const unsigned char *p, int array[4][4]);

/*加密函数，该函数只进行AES128位bit加密，本加密采用ECB模式，对明文不足的采取PKCS5处理
 *param 1:明文字符串；
 *param 2:明文长度，
 *param 3:密钥字符串，密钥必须为16个字节，此为强校验
 *param 4:输出密文字符串二级指针，
 *param 5:输出密文长度*/
int encrpyt_aes128(const char *context, const int cb, const char *key_words,
                   unsigned char **output_context, int *out_cb);
/**解密函数例程
 *param 1:密文正文
 *param 2:密文正文长度
 *param 3:密钥
 *param 4:解密得到的字符串
 *param 5:解密得到的字符串长度
 */
int decode_aes128(unsigned char *context, const int cb, const char *key_words,
                  unsigned char **output_context, int *out_cb);
//释放拷贝内存
void free_memory(unsigned char *ptr);

//
std::string decrypt_aes128_str(const std::string &mi_wen,
                               const std::string &key);

std::string encrypt_aes128_str(const std::string &ming_wen,
                               const std::string &key);
//#include "aes128.hpp"

/****************************************************************************
函数功能: 将普通字符串转换成十六进制的ASSCI码字符串
                此接口功能与boost::algorithm::hex相同
举例：	源字符串：“123”－－－〉目标字符串：“313233”
*****************************************************************************/
extern void str2hex(char *dst,const unsigned  char *src, int src_len);
/****************************************************************************
函数功能: 将十六进制的ASSCI码字符串转换成普通字符串
                此接口功能与boost::algorithm::unhex相同
举例：	源字符串：“313233”－－－〉目标字符串：“123”
*****************************************************************************/
extern void hex2str(char *dst,const char *src, int src_len);
