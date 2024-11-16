#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdint.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_u_int16_t.h>
#include <stdbool.h>
#include "cutils.h"

/*
    数据结构carray
    ------------------0++++++++++++++++++
    [---long---][---long---][---long---][---long---][data.......]
    type        step        volume      length      data
     容量(0-...)  数量(0-...)  存储位置
*/
enum insert {
    single,
    duplicate,
} insert_t;


typedef enum ISO_IEC_646 {
    C89,// ISO/IEC 646:1991 
    C99,// ISO/IEC 646:1999
} ISO_IEC_646_t;

typedef enum ctype {
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
} ctype_t;

// #define Double(x) (x * 1.0000000f)

//  @return             返回一个如7行所示的包含信息的数据结构carray,结构与其一致.
//  @paramater src      常规数组.
//  @paramater length   存在长度.
//  @paramater type     存在类型.因为C语言数组参数入参时降级为指针,无法根据其获取类型,故而需要指定类型.
extern void *       carrayinit(void * src, size_t length, ctype_t type);


//  @paramater ca       数据结构carray数组.
extern void         carrayfree(void * ca);


//  @return             存在类型.
//  @paramater ca       数据结构carray数组.
extern ctype_t  carraytype(void * ca);


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


extern bool         carrayinsert(void * ca, long idx, long pc, ...);


//  插入函数
//  @return             返回追加操作是否成功.
//  @paramater ca       carray型.
//  @paramater idx      追加位置,总是以cstr作为0为参照.
//  @paramater pc       插入元素个数
//  @paramater ...      插入元素(char,short,int,long,uchar,ushort,uint,ulong,float,double,必须保证ca类型与元素类型一致,否则结果有问题),接受多个不定参数.
extern bool         carrayinsert0(void * ca, long idx, long pc, ...);
#if !defined (carrayinsert0$)
    #define carrayinsert0$(a, b, ...) carrayinsert0(a, b, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'carrayinsert$'
#endif


//  插入函数
//  @return             返回追加操作是否成功.
//  @paramater ca       carray型.
//  @paramater idx      追加位置,总是以cstr作为0为参照.
//  @paramater pc       插入元素个数
//  @paramater ...      插入数组(carray型,必须保证ca类型与元素类型一致,否则结果有问题),接受多个不定参数.
extern bool         carrayinsert1(void * ca, long idx, long pc, ...);
#if !defined (carrayinsert1$)
    #define carrayinsert1$(a, b, ...) carrayinsert1(a, b, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'carrayinsert$'
#endif

extern void showcolor();

extern int          unique(void * idxes, ctype_t t, int length);
extern int          typebyte(ctype_t t);
extern void         swap(void * n1, void * n2, int width);

#endif