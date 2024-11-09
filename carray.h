#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdint.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_u_int16_t.h>

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

/*
    数据结构carray
    ------------------0++++++++++++++++++
    [---long---][---long---][---long---][---long---][data.......]
    type        step        volume      length      data
     容量(0-...)  数量(0-...)  存储位置
*/

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

#define EXCHANGE(n1, n2) do { n1 = n1 ^ n2; n2 = n1 ^ n2; n1 = n1 ^ n2; } while(0)

typedef enum cbasetype {
    cbasechar   = 0x00UL,
    cbaseuchar  = 0x01UL,
    cbaseshort  = 0x02UL,
    cbaseushort = 0x03UL,
    cbaseint    = 0x04UL,
    cbaseuint   = 0x05UL,
    cbasefloat  = 0x06UL,
    cbaselong   = 0x07UL,
    cbaseulong  = 0x08UL,
    cbasedouble = 0x09UL,
} cbasetype_t;


//  @return             返回一个如7行所示的包含信息的数据结构carray,结构与其一致.
//  @paramater src      常规数组.
//  @paramater length   存在长度.
//  @paramater type     存在类型.因为C语言数组参数入参时降级为指针,无法根据其获取类型,故而需要指定类型.
extern void *       carrayinit(void * src, size_t length, cbasetype_t type);


//  @paramater ca       数据结构carray数组.
extern void         carrayfree(void * ca);


//  @return             存在类型.
//  @paramater ca       数据结构carray数组.
extern cbasetype_t  carraytype(void * ca);


//  @return             存在单元基本长度.
//  @paramater ca       数据结构carray数组.
extern size_t       carraystep(void * ca);


//  @return             存在容量.
//  @paramater ca       数据结构carray数组.
extern size_t       carrayvolume(void * ca);


//  @return             存在长度.
//  @paramater ca       数据结构carray数组.
extern size_t       carraylength(void * ca);


//  @paramater ca       数据结构carray数组.
extern void         carraydescribe(void * ca);


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