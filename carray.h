#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdint.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_u_int16_t.h>
#include <stdbool.h>
#include "cutils.h"

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

typedef enum ISO_IEC_646 {
    C89,// ISO/IEC 646:1991 
    C99,// ISO/IEC 646:1999
} ISO_IEC_646_t;

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


typedef enum cainsert {
    single,   // 单个元素
    carray,   // 数组元素
} cainsert_t;
extern bool         carrayinsert(void * ca, cainsert_t t, long idx, long ps, ...);
#if !defined (carrayinsert$)
    #define carrayinsert$(a, b, c, ...) carrayinsert(a, b, c, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'carrayinsert$'
#endif


void endian();
void showcolor();

#endif