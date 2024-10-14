#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum ISO_IEC_646 {
    C89,// ISO/IEC 646:1991 
    C99,// ISO/IEC 646:1999
} ISO_IEC_646_t;

/*
    数据结构
     -----------------------0++++++++++++
    [---long---][---long---][char.......]
     volume      length       chars
     容量(0-...)  数量(0-...)  存储位置
*/

// #define __ARGS(X)                   (X)
// #define __ARGC_N(_0, _1, N, ...)    N == 1 ? (#_0)[0] != 0 : N
// #define __ARGC(...)                 __ARGS(__ARGC_N(__VA_ARGS__,2,1))
// #define ARGC(...)                   __ARGC(__VA_ARGS__)

// #define cstringinit$(a, ...)            cstringinit(a, (32, ##__VA_ARGS__))
// #define cstringdescribe$(a, ...)        cstringdescribe(a, (0b001, ##__VA_ARGS__))
// #define cstringtelescope$(a, b, c)      cstringtelescope(a, DEFAULTARGC(b, true), DEFAULTARGC(c, 2))
// #define ASCII$(a, b)                    ASCII(DEFAULTARGC(a, C89), DEFAULTARGC(b, 0b001))

/*
========================================================================================
                                        宏定义区域
========================================================================================
*/

#if !defined (DEFAULTARGC)
    #define DEFAULTARGC(a, value)           ((#a[0]) ? (a + 0) : value)
#else
    #warning "information: duplicate define macro 'DEFAULTARGC'
#endif

#if !defined (cstringinit$)
    #define cstringinit$(a, ...)            cstringinit(a, (32, ##__VA_ARGS__))
#else
    #warning "information: duplicate define macro 'cstringinit$'
#endif

#if !defined (cstringdescribe$)
    #define cstringdescribe$(a, ...)        cstringdescribe(a, (0b001, ##__VA_ARGS__))
#else
    #warning "information: duplicate define macro 'cstringdescribe$'
#endif

#if !defined (cstringtelescope$)
    #define cstringtelescope$(a, b, c)      cstringtelescope(a, DEFAULTARGC(b, true), DEFAULTARGC(c, 2))
#else
    #warning "information: duplicate define macro 'cstringtelescope$'
#endif

#if !defined (ASCII$)
    #define ASCII$(a, b)                    ASCII(DEFAULTARGC(a, C89), DEFAULTARGC(b, 0b001))
#else
    #warning "information: duplicate define macro 'ASCII$'
#endif


/*
========================================================================================
                                        函数区域
========================================================================================
*/

/*
    @return             返回一个如13行所示的包含信息的字符串,结构与其一致.
    @paramater str      常规的字符串.
    @paramater volume   容量大小.会根据str的长度进行内部调整大小.
*/
extern char *  cstringinit(char * str, long volume);

/*
    @return             返回包含信息的字符串的长度.长度包含字符串末尾的0x00,即\0的存储位置也计算在内
    @paramater str      经过cstringinit处理过的包含信息的字符串.
*/
extern long    cstringlength(char * cstr);
// 字符容量

/*
    @return             返回包含信息的字符串的长度的容量,与存储内容无关.
    @paramater str      经过cstringinit处理过的包含信息的字符串.
*/
extern long    cstringvolume(char * cstr);

/*
    @return             无返回值.
    @paramater pstr     经过cstringinit处理过的包含信息的字符串它的二级的指针.
    @paramater control  false:代表减少容量,true:代表增加容量.
    @paramater multiply 容量增加或者减少的倍率.
*/
extern void    cstringtelescope(char ** pcstr, bool control, long multiply);

/*
    @return             无返回值.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
    @paramater flag     显示标记(0b111, 0b110, 0b101, 0b011, 0b100, 0b010, 0b001)共计7种,三位数字代表十六进制显示,十进制显示,字符显示.
*/
extern void    cstringdescribe(char * cstr, unsigned short flag);

/*
    @return             经过cstringinit处理过的包含信息的字符串.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
*/
extern char *  cstringcopy(char * cstr);

/*
    @return             无返回值.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
*/
extern void    cstringfree(char * cstr);

/*
    @return             两者存在的内容是否一致.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
    @paramater data     经过cstringinit处理过的包含信息的字符串.
*/
extern bool    cstringcompare(char * cstr, char * data);

/*
    @return             插入操作是否成功.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
    @paramater index    插入位置,总是以cstr作为0为参照.
    @prarmater ...      插入内容,只处理第一个参数,其他忽略,采用不定参数,只为模拟函数重载方便而已,只能能处理字符型和经过cstringinit处理过的包含信息的字符串两种.
*/
extern bool    cstringinsert(char * cstr, long index, ...);

/*
    @return             插入操作是否成功.
    @paramater cstr     经过cstringinit处理过的包含信息的字符串.
    @paramater index    插入位置,总是以cstr作为0为参照.
    @prarmater ...      插入内容,只处理第一个参数,其他忽略,采用不定参数,只为模拟函数重载方便而已,只能能处理字符型和经过cstringinit处理过的包含信息的字符串两种.
*/
extern bool    cstringappend(char * cstr, ...);

/*
    @return             无返回值.
    @paramater cstr     显示各种C语言类型的占用字节数.
*/
extern void    typebytelength(void);

/*
    @return             无返回值.
    @paramater standard 有C89和C99两种,区别为C89(0-127),C99(0-255),字符集范围不同而已.
    @paramater flag     与cstringdescribe函数flag参数意义完全一致.
*/
extern void    ASCII(ISO_IEC_646_t standard, unsigned short flag);

#endif