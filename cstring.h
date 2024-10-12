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

extern char *  tocstring(char * str);
// 字符串长度包含0x00,即\0的存储位置也计算在内
extern long    cstringlength(char * cstr);
// 字符容量
extern long    cstringvolume(char * cstr);
extern void    cstringtelescope(char ** pcstr, bool control, long multiply);
extern void    cstringdescribe(char * cstr, unsigned short flag);
extern char *  cstringcopy(char * cstr);
extern void    cstringfree(char * cstr);
extern bool    cstringcompare(char * cstr, char * data);
extern bool    cstringinsert(char * cstr, long index, ...);

extern void    typebytelength(void);
extern void    ASCII(ISO_IEC_646_t standard, unsigned short flag);

#endif