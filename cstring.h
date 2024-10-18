#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <stdbool.h>
#include <stdint.h>

// #pragma pack(1)
// typedef struct cstring_one {
//     char c;
// 	long l;
// 	long v;
// } cstring_one_t;
// #pragma pack()

// return "zzz"; "zzz" 字面量存储在静态区域里 不需要释放
/*
    数据结构cstring
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
    #define cstringinit$(a, ...)            cstringinit(a, (false, ##__VA_ARGS__))
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

#if !defined (cstringindex$)
    #define cstringindex$(a, b, c, ...)     cstringindex(a, DEFAULTARGC(b, 1), c, ##__VA_ARGS__)
#else
    #warning "information: duplicate define macro 'cstringindex$'
#endif


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
            long length = cstringlength(p);\
		    char temp[2 * sizeof(long) + length];\
            for(int i = 0; i < length; i ++) { temp[2 * sizeof(long) + i] = ((char *)p)[i]; }\
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


/* 
========================================================================================
                                        函数区域
========================================================================================
*/

extern long     baseinformationsize(void);

//  @return             返回一个如13行所示的包含信息的字符串,结构与其一致.
//  @paramater str      常规字符串.str(NULL,0,0x00),ctl不生效,length始终为0,volume不存储.str(!NULL)时,按照ctl控制参数接受.str("","\0","\000..."),ctrl(true)则length为1,volume存储0.str("","\0","\000..."),ctrl(false)则length为0,volume不存储.
//  @paramater ctl      是否存储字符串默认结尾的(0x00,0,NULL,'\0','\0...'),true:存储,false:不存储.
extern char *   cstringinit(char * str, bool ctl);

//  功能类似于size_t strlen(const char *s);
//  @return             返回包含信息的字符串的长度.长度包含字符串末尾的0x00,即\0的存储位置也计算在内
//  @paramater str      cstring型.
extern long     cstringlength(char * cstr);


//  @return             返回包含信息的字符串的长度的容量,与存储内容无关.
//  @paramater str      cstring型.
extern long     cstringvolume(char * cstr);


//  @return             无返回值.
//  @paramater pstr     cstring型它的二级的指针.
//  @paramater ctl      false:代表减少容量,true:代表增加容量.
//  @paramater m        容量增加或者减少的倍率.
extern void     cstringtelescope(char ** pcstr, bool ctl, long m);


//  @return             无返回值.
//  @paramater cstr     cstring型.
//  @paramater flag     显示标记(0b111, 0b110, 0b101, 0b011, 0b100, 0b010, 0b001)共计7种,三位数字代表十六进制显示,十进制显示,字符显示.
extern void     cstringdescribe(char * cstr, unsigned short flag);


//  功能类似于char *strcpy(char *dest, const char *src);
//  @return             返回cstring型.
//  @paramater cstr     cstring型.
extern char *   cstringcopy(char * cstr);


//  @return             无返回值.
//  @paramater cstr     cstring型.
extern void     cstringfree(char * cstr);


//  @return             返回两者存在的内容是否一致.
//  @paramater cstr     cstring型.
//  @paramater data     cstring型.
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
//  @paramater ...      清空内容(char型或cstring型),接受一个不定参数.
extern bool     cstringclean(char * cstr, ...);


//  @return             返回删除操作是否成功.
//  @paramater cstr     cstring型.
//  @paramater index    删除索引
extern bool     cstringremove(char * cstr, long index);


//  功能类似char *strchr(const char *s, int c); char *strstr(const char *s1, const char *s2);
//  @return             返回第times次出现检索内容的索引值,若为-1则未找到.
//  @paramater cstr     cstring型.
//  @paramater times    检索内容出现次数.
//  @paramater ...      检索内容(char型或cstring型),若为char型,接受一个不定参数,若为cstring型,还需传入一个bool型(针对cstring型[111],[222]...,控制索引方式),接受两个不定参数.
extern long     cstringindex(char * cstr, long times, ...);


//  @return             返回共计出现检索内容的总数.
//  @paramater cstr     cstring型.
//  @paramater ...      检索内容(char型或cstring型),若为char型,接受一个不定参数,若为cstring型,还需传入一个bool型(针对cstring型[111],[222]...,控制索引方式),接受两个不定参数.
extern long     cstringindexcount(char * cstr, ...);


//  数组每个元素只保留一个
//  @return             无返回值.
//  @paramater cstr     cstring型.
extern void     cstringunique(char * cstr);


//  @return             无返回值.
//  @paramater cstr     cstring型.
//  @paramater pos      操作起始索引.
//  @paramater ...      改变内容(char型或cstring型),接受一个不定参数.
extern void     cstringchange(char * cstr, long pos, ...);

#endif