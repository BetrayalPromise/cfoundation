#ifndef __NUMBER_H__
#define __NUMBER_H__

typedef enum format {
    original,   // 原码
    inverse,    // 反码
    complement, // 补码
} format_t;

typedef enum ISO_IEC_646 {
    C89,// ISO/IEC 646:1991 
    C99,// ISO/IEC 646:1999
} ISO_IEC_646_t;

#define BitGet(n, p)  ((n) >> (p)&1)        // 得到某数的某位
#define BitNOT(n, p)  ((n) ^= 1<<(p))       // 把n的p位取反
#define BitSET1(n, p) ((n)|= 1<<(p))        // 把某位置1
#define BitSET0(n, p) ((n) &= ~(1<<(p)))    // 把某位置0

typedef union nunber {
    char    c;
    short   s;
    int     i;
    float   f;
    long    l;
    double  d;
} nunber_t;

void endian();

void char2binary(char value, format_t fmt);
void short2binary(short value, format_t fmt);
void int2binary(int value, format_t fmt);
void long2binary(long value, format_t fmt);
void uchar2binary(unsigned char value, format_t fmt);
void ushort2binary(unsigned short value, format_t fmt);
void uint2binary(unsigned int value, format_t fmt);
void ulong2binary(unsigned long value, format_t fmt);
void float2binary(float value, format_t fmt);
void double2binary(double value, format_t fmt);

void showcolor();


#endif