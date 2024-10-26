#ifndef __CDATA_H__
#define __CDATA_H__

#include "cstring.h"
#include <sys/_types/_size_t.h>

typedef char cdata_t;

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

#define EXCHANGE(num1, num2) do { num1 = num1 ^ num2; num2 = num1 ^ num2; num1 = num1 ^ num2; } while(0)

typedef enum cbasetype {
    cchar   = 0x00UL,
    cuchar  = 0x01UL,
    cshort  = 0x02UL,
    cushort = 0x03UL,
    cint    = 0x04UL,
    cuint   = 0x05UL,
    cfloat  = 0x06UL,
    clong   = 0x07UL,
    culong  = 0x08UL,
    cdouble = 0x09UL,
} cbasetype_t;

extern void *       cdatainit(void * src, cbasetype_t type, size_t length);

extern cbasetype_t  cdatatype(void * cs);
extern size_t       cdatastep(void * cs);
extern size_t       cdatavolume(void * cs);
extern size_t       cdatalength(void * cs);

extern void         cdatadescribe(void * cs);

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