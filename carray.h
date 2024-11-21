#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdbool.h>
#include "cutils.h"

/*
    数据结构carray
    ------------------0++++++++++++++++++
    [---long---][---long---][---long---][---long---][data.......]
    type        step        volume      length      data
    类型(0-...)  字长(0-...)  容量(0-...)  数量(0-...) 存储位置
*/

typedef enum ISO_IEC_646 {
    C89,// ISO/IEC 646:1991 
    C99,// ISO/IEC 646:1999
} ISO_IEC_646_t;

typedef enum ctype {
    cschar  = 0x00UL,
    cuchar  = 0x01UL,
    csshort = 0x02UL,
    cushort = 0x03UL,
    csint   = 0x04UL,
    cuint   = 0x05UL,
    cfloat  = 0x06UL,
    cslong  = 0x07UL,
    culong  = 0x08UL,
    cdouble = 0x09UL,
} ctype_t;


//  @return             返回一个如7行所示的包含信息的数据结构carray,结构与其一致.
//  @paramater src      常规数组.
//  @paramater type     存在类型.因为C语言数组参数入参时降级为指针,无法根据其获取类型,故而需要指定类型.
//  @paramater length   数组长度.
extern void *       carrayinit(void * src, ctype_t type, long length);

//  @return             无返回值.
//  @paramater ca       数据结构carray数组.
extern void         carrayfree(void * ca);


//  @return             类型.
//  @paramater ca       数据结构carray数组.
extern ctype_t      carraytype(void * ca);


//  @return             存储单元基本长度.
//  @paramater ca       数据结构carray数组.
extern long         carraystep(void * ca);


//  @return             存储容量.
//  @paramater ca       数据结构carray数组.
extern long         carrayvolume(void * ca);


//  @return             存储长度.
//  @paramater ca       数据结构carray数组.
extern long         carraylength(void * ca);


//  @paramater ca       数据结构carray数组.
extern void         carraydescribe(void * ca);


//  @return             返回插入操作是否成功.
//  @paramater carray   carray型.
//  @paramater t        ctype_t型.
//  @paramater idx      插入位置.
//  @paramater pc       不定参数数量.
extern bool         carrayinsert(void * ca, sc_t t, long idx, long pc, ...);
#if !defined (carrayinsert$)
    #define carrayinsert$(a, b, c, ...) carrayinsert(a, b, c, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'carrayinsert$'
#endif


//  @return             返回归堆操作是否成功.
//  @paramater array    void*型.
//  @paramater t        ctype_t型.
//  @paramater length   数组长度.
//  @paramater flag     为true,从大到小归堆;为false,从小到大排列归堆.
extern bool         carrayclassify(void * array, ctype_t t, long length, bool flag);


//  @return             返回去重复后数组的数量.
//  @paramater array    void型.
//  @paramater t        ctype_t型.
//  @paramater length   数组长度.
extern long         carrayunique(void * array, ctype_t t, long length);


//  @return             类型字节长度.
//  @paramater t        ctype_t型.
extern int          carraytypebyte(ctype_t t);


//  @return             无返回值.
//  @paramater n1       void*型.
//  @paramater n2       void*型.
//  @paramater width    int型.
extern void         carrayswap(void * n1, void * n2, int width);

//  @return             无返回值.
//  @paramater std      ISO_IEC_646_t型.
//  @paramater flag     unsigned short型.
extern void         ASCII(ISO_IEC_646_t std, unsigned short flag);

#endif