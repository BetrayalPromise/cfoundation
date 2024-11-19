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

typedef union store {
    schar   scharvalue;
    uchar   ucharvalue;
    sshort  sshortvalue;
    ushort  ushortvalue;
    sint    sintvalue;
    uint    uintvalue;
    float   floatvalue;
    slong   slongvalue;
    ulong   ulongvalue;
    double  doublevalue;
} store_t;


//  @return             返回一个如7行所示的包含信息的数据结构carray,结构与其一致.
//  @paramater src      常规数组.
//  @paramater length   存在长度.
//  @paramater type     存在类型.因为C语言数组参数入参时降级为指针,无法根据其获取类型,故而需要指定类型.
extern void *       carrayinit(void * src, long length, ctype_t type);


//  @paramater ca       数据结构carray数组.
extern void         carrayfree(void * ca);


//  @return             存在类型.
//  @paramater ca       数据结构carray数组.
extern ctype_t      carraytype(void * ca);


//  @return             存在单元基本长度.
//  @paramater ca       数据结构carray数组.
extern long         carraystep(void * ca);


//  @return             存在容量.
//  @paramater ca       数据结构carray数组.
extern long         carrayvolume(void * ca);


//  @return             存在长度.
//  @paramater ca       数据结构carray数组.
extern long         carraylength(void * ca);


//  @paramater ca       数据结构carray数组.
extern void         carraydescribe(void * ca);


extern bool         carrayinsert(void * ca, is_t t, long idx, long pc, ...);
#if !defined (carrayinsert$)
    #define carrayinsert$(a, b, c, ...) carrayinsert(a, b, c, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'carrayinsert$'
#endif


extern long         unique(void * array, ctype_t t, long length);
extern int          typebyte(ctype_t t);
extern void         swap(void * n1, void * n2, int width);
extern void         ASCII(ISO_IEC_646_t std, unsigned short flag);

#endif