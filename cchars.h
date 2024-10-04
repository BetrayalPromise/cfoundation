#ifndef __CCHARS_H__
#define __CCHARS_H__

#include <stdbool.h>

typedef struct cchars {
	// public readonly, 数组容量
	long capacity;
	// public readonly 数组元素个数
	long count;
	// public readonly 存储元素首地址
	char * store;
} cchars_t;

extern cchars_t * cchars_init(const char * str, long count);
extern void cchars_free(cchars_t * cs);
extern long cchars_length(cchars_t * cs);
extern bool cchars_insert(cchars_t * cs, long position, char data);
extern bool cchars_change(cchars_t * cs, long position, char data);
extern bool cchars_remove(cchars_t * cs, long position);

// extern cchars_t * cchars_copy(cchars_t * cs);

// #define CCHARS(name, string)\
// 	struct cchars name = { -1, -1, NULL };\
// 	do {\
// 		char array[] = string;\
// 		name.capacity = sizeof(array)/sizeof(char) - 1;\
// 		name.count = sizeof(array)/sizeof(char) - 1;\
// 		name.store = NULL;\
// 	} while(0);

#define __CONNECT__(a,b) a##b
// 只适用于字面量
#define __CSTRING__(a) #a

// 只适用于字面量,唯一的办法是用char[]接收字符串,sizeof(char[])得到字符串长度
#define __CCHARS_LENGTH__(name, array)\
	0; name = sizeof(array)/sizeof(char) - 1;

#define __CCHARS_INIT__(name, array)\
	NULL; name = cchars_init(array, sizeof(array)/sizeof(char) - 1);\

#endif /* cchars.h */

