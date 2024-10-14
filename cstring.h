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


#if !defined (DEFAULTARGC)
    #define DEFAULTARGC(a, value)           ((#a[0]) ? (a + 0) : value)
#else
    #warning "information: other module define macro 'DEFAULTARGC'
#endif

#if !defined (cstringinit$)
    #define cstringinit$(a, ...)            cstringinit(a, (32, ##__VA_ARGS__))
#else
    #warning "information: other module define macro 'cstringinit$'
#endif

#if !defined (cstringdescribe$)
    #define cstringdescribe$(a, ...)        cstringdescribe(a, (0b001, ##__VA_ARGS__))
#else
    #warning "information: other module define macro 'cstringdescribe$'
#endif

#if !defined (cstringtelescope$)
    #define cstringtelescope$(a, b, c)      cstringtelescope(a, DEFAULTARGC(b, true), DEFAULTARGC(c, 2))
#else
    #warning "information: other module define macro 'cstringtelescope$'
#endif

#if !defined (ASCII$)
    #define ASCII$(a, b)                    ASCII(DEFAULTARGC(a, C89), DEFAULTARGC(b, 0b001))
#else
    #warning "information: other module define macro 'ASCII$'
#endif


extern char *  cstringinit(char * str, long volume);
// 包含字符串末尾的0x00,即\0的存储位置也计算在内
extern long    cstringlength(char * cstr);
// 字符容量
extern long    cstringvolume(char * cstr);
extern void    cstringtelescope(char ** pcstr, bool control, long multiply);
extern void    cstringdescribe(char * cstr, unsigned short flag);
extern char *  cstringcopy(char * cstr);
extern void    cstringfree(char * cstr);
extern bool    cstringcompare(char * cstr, char * data);
extern bool    cstringinsert(char * cstr, long index, ...);
extern bool    cstringappend(char * cstr, ...);

extern void    typebytelength(void);
extern void    ASCII(ISO_IEC_646_t standard, unsigned short flag);

#endif