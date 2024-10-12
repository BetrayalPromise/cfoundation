#ifndef __CCHARS_H__
#define __CCHARS_H__

#include <stdbool.h>

// 字符串数组结构
typedef struct cchars {
	// public readonly, 数组容量
	long capacity;
	// public readonly 数组元素个数
	long count;
	// public readonly 存储元素首地址
	char * store;
} cchars_t;

typedef enum information {
	unknow_type,
	cchars_type,
	search_type,
	string_type,
} information_t;

extern cchars_t *	ccharsinit(const char * str, long count);
extern cchars_t *   ccharscopy(cchars_t * cs);
extern void			ccharsfree(cchars_t * cs);
extern long			ccharslength(cchars_t * cs);
extern bool			ccharscompare(cchars_t * cs, cchars_t * data);
extern void 		ccharsdescribe(void * object, information_t info, long flag);


extern bool			ccharsinsertcharacter(cchars_t * cs, long position, char data);
extern bool			ccharsappendcharacter(cchars_t * cs, char data);
// (long *)[count][index0][index1]..., need free
extern long *		ccharssearchcharacter(cchars_t * cs, char data);
extern bool			ccharschangecharacter(cchars_t * cs, long position, char data);
extern bool			ccharsremovecharacter(cchars_t * cs, char data);


extern bool			ccharsinsertcchars(cchars_t * cs, long position, cchars_t * data);
extern bool			ccharsappendcchars(cchars_t * cs, cchars_t * data);
//(long *)[count][index0][index1]..., need free
extern long * 		ccharssearchcchars(cchars_t * cs, cchars_t * data, long flag);
extern bool 		ccharschangecchars(cchars_t * cs, long position, cchars_t * data);
extern bool			ccharsremovecchars(cchars_t * cs, cchars_t * data);

extern bool			ccharsremoveboundary(cchars_t * cs, long position, long size);
// [8byte=length][c0][c1]..., need free
extern char *		cchars_mutate_cstring(cchars_t * cs);

#define __CONNECT__(a,b) a##b
// 只适用于字面量
#define __CSTRING__(a) #a

// 只适用于字面量,唯一的办法是用char[]接收字符串,不要使用char *接收,否则无法获取有'\0'的字符串准确长度,sizeof(char[])得到字符串长度
#define __CCHARS_LENGTH__(array) (sizeof(array)/sizeof(char) - 1)
#define __CCHARS_INIT__(array) ccharsinit(array, sizeof(array)/sizeof(char) - 1)

#endif /* cchars.h */

