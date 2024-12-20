#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <stdbool.h>
#include "cutils.h"

/*
    数据结构cstring
    ------------------0++++++++++++++++++
    [---long---][---long---][char.......]
     volume      length      chars
     容量(0-...)  数量(0-...)  存储位置
*/

// 小端存储能使用,栈数据,不能扩容
// char[]
// 能处理字面量字符串中包含'\0'的
#if !defined (STRING2CSTRING)
    #define STRING2CSTRING(name, s)\
        NULL;\
	    do {\
		    char temp[2 * sizeof(long) + sizeof(s)/sizeof(char) - 1];\
		    *(long *)(temp) = sizeof(s)/sizeof(char) - 1; *(long *)(temp + sizeof(long)) = sizeof(s)/sizeof(char) - 1;\
		    for(int i = 0; i < sizeof(s)/sizeof(char) - 1; i ++) { temp[2 * sizeof(long) + i] = s[i]; }\
		    name = temp + 2 * sizeof(long);\
	    } while(0);
#else
    #warning "information: duplicate define macro 'S2CSTRING'
#endif


// 小端存储能使用,栈数据,不能扩容
// char *
// 能处理字面量字符串中包含'\0'的
#if !defined (POINTER2CSTRING)
    #define POINTER2CSTRING(name, p)\
        NULL;\
	    do {\
		    char temp[2 * sizeof(long) + cstringlength(p)];\
            for(int i = 0; i < cstringlength(p); i ++) { temp[2 * sizeof(long) + i] = ((char *)p)[i]; }\
		    name = temp + 2 * sizeof(long);\
	    } while(0);
#else
    #warning "information: duplicate define macro 'POINTER2CSTRING'
#endif


// 小端存储能使用,栈数据,不能扩容
// char
// 能处理字面量字符
#if !defined (CHAR2CSTRING)
    #define CHAR2CSTRING(name, c)\
        NULL;\
	    do {\
		    char temp[2 * sizeof(long) + 1];\
		    *(long *)(temp) = 1; *(long *)(temp + sizeof(long)) = 1;\
            temp[2 * sizeof(long)] = c;\
		    name = temp + 2 * sizeof(long);\
	    } while(0);
#else
    #warning "information: duplicate define macro 'C2CSTRING'
#endif


//  @return             返回一个如13行所示的包含信息的字符串,结构与其一致.
//  @paramater str      常规字符串.str(NULL,0,0x00),ctl不生效,length始终为0,volume不存储.str(!NULL)时,按照ctl控制参数接受.str("","\0","\000..."),ctrl(true)则length为1,volume存储0.str("","\0","\000..."),ctrl(false)则length为0,volume不存储.
//  @paramater ctl      是否存储字符串默认结尾的(0x00,0,NULL,'\0','\0...'),true:存储,false:不存储.
extern char *   cstringinit(char * str, bool ctl);
#if !defined (cstringinit$)
    #define cstringinit$(a, ...) cstringinit(a, (false, ##__VA_ARGS__))
#else
    #warning "information: duplicate define macro 'cstringinit$'
#endif


//  功能类似于long strlen(const char *s);
//  @return             返回包含信息的字符串的长度.长度包含字符串末尾的0x00,即\0的存储位置也计算在内
//  @paramater str      cstring型.
extern long     cstringlength(char * cstr);


//  @return             返回包含信息的字符串的长度的容量,与存储内容无关.
//  @paramater str      cstring型.
extern long     cstringvolume(char * cstr);


//  只针对使用cstringinit函数处理过的字符串,即为堆字符串;使用POINTER2CSTRING,STRING2CSTRING,CHAR2CSTRING宏构建的为栈字符串,无法改变容量
//  @return             无返回值.
//  @paramater pstr     cstring*型.cstring的二级的指针.
//  @paramater ctl      false:代表减少容量,true:代表增加容量.
//  @paramater m        容量增加或者减少的倍率.
extern void     cstringtelescope(char ** pcstr, bool ctl, long m);
#if !defined (cstringtelescope$)
    #define cstringtelescope$(a, b, c) cstringtelescope(a, DEFAULTARGC(b, true), DEFAULTARGC(c, 2))
#else
    #warning "information: duplicate define macro 'cstringtelescope$'
#endif


//  @return             格式化打印,无返回值.
//  @paramater cstr     cstring型.
//  @paramater flag     显示标记(0b111, 0b110, 0b101, 0b011, 0b100, 0b010, 0b001)共计7种,三位数字代表十六进制显示,十进制显示,字符显示.
extern void     cstringdescribe(char * cstr, unsigned short flag);
#if !defined (cstringdescribe$)
    #define cstringdescribe$(a, ...) cstringdescribe(a, (0b001, ##__VA_ARGS__))
#else
    #warning "information: duplicate define macro 'cstringdescribe$'
#endif


//  功能类似于char *strcpy(char *dest, const char *src);
//  @return             返回cstring型.
//  @paramater cstr     cstring型.
extern char *   cstringcopy(char * cstr);


//  @return             是否内存,无返回值.
//  @paramater cstr     cstring型.
extern void     cstringfree(char * cstr);


//  @return             返回两者存在的内容是否一致.
//  @paramater cstr     cstring型.
//  @paramater data     cstring型.比较的数据
extern bool     cstringcompare(char * cstr, char * data);


//  @return             返回插入操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater index    插入位置,总是以cstr作为0为参照.
//  @prarmater ...      插入内容(char型或cstring型),接受一个不定参数.
extern bool     cstringinsert(char * cstr, long index, ...);


//  功能类似char *strcat(char *dest, const char *src);
//  @return             返回追加操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater index    追加位置,总是以cstr作为0为参照.
//  @paramater ...      追加内容(char型或cstring型),接受一个不定参数.
extern bool     cstringcatenate(char * cstr, ...);


//  @return             返回删除操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater t        rm_t型.
//  @paramater pc       不定参数个数.
//  @paramater ...      清空内容(int, char型或cstring型),接受最多32个不定参数.
extern bool     cstringremove(char * cstr, rm_t t, long pc, ...);
#if !defined (cstringremove$)
    #define cstringremove$(a, b, ...) cstringremove(a, b, ARGC(__VA_ARGS__), ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'cstringremove$'
#endif


//  功能类似char *strchr(const char *s, int c); char *strstr(const char *s1, const char *s2);
//  @return             返回第times次出现检索内容的索引值,若为-1则未找到.
//  @paramater cstr     cstring型.
//  @paramater t        sc_t型.
//  @paramater times    检索内容第times次出现次数.
//  @paramater ...      检索内容(char型或cstring型),若为int型,接受一个不定参数,若为char型,接受一个不定参数,若为cstring型,还需传入一个bool型(针对cstring型[111],[222]...,控制索引方式),接受两个不定参数.
extern long     cstringsearch(char * cstr, sc_t t, long times, ...);
#if !defined (cstringsearch$)
    #define cstringsearch$(a, b, c, ...) cstringremove(a, b, c, ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'cstringremove$'
#endif


//  数组去重复元素
//  @return             返回操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater flag     bool型.为true:重复元素保留一个;为false:重复元素一个不保留.
extern bool     cstringunique(char * cstr, bool flag);


//  @return             返回操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater pos      操作起始索引.
//  @paramater ...      改变内容(char型或cstring型),接受一个不定参数.
extern bool     cstringchange(char * cstr, long pos, ...);


//  @return             无返回值.
//  @paramater cstr     cstring型.
//  @paramater ctl      bool型.为true:按照ASCII码从大到小排序;为false:按照ASCII码从小到大排序.
extern void     cstringsort(char * cstr, bool ctl);

#endif