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

extern void			cchars_ascii_form();
extern cchars_t *	cchars_init(const char * str, long count);
extern cchars_t *   cchars_copy(cchars_t * cs);
extern void			cchars_free(cchars_t * cs);
extern long			cchars_length(cchars_t * cs);
extern void			cchars_description(cchars_t * cs, long ctrl);
extern void			cchars_search_description(long * info);

extern bool			cchars_insert_character(cchars_t * cs, long position, char data);
extern bool			cchars_append_character(cchars_t * cs, char data);
// (long *)[count][index0][index1]...
extern long *		cchars_search_character(cchars_t * cs, char data);
extern bool			cchars_change_character(cchars_t * cs, long position, char data);
extern bool			cchars_remove_character(cchars_t * cs, char data);


extern bool			cchars_insert_cchars(cchars_t * cs, long position, cchars_t * data);
extern bool			cchars_append_cchars(cchars_t * cs, cchars_t * data);
//(long *)[count][index0][index1]...
extern long * 		cchars_search_cchars(cchars_t * cs, cchars_t * data);
extern bool 		cchars_change_cchars(cchars_t * cs, long position, cchars_t * data);
// TODO:
extern bool			cchars_remove_cchars(cchars_t * cs, cchars_t * data);
extern bool			cchars_remove_boundary(cchars_t * cs, long position, long size);
// [8byte=length][xxx...]
extern char *		cchars_mutate_cstring(cchars_t * cs);

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

// 只适用于字面量,唯一的办法是用char[]接收字符串,不要使用char *接收,否则无法获取有'\0'的字符串准确长度,sizeof(char[])得到字符串长度
#define __CCHARS_LENGTH__(array) (sizeof(array)/sizeof(char) - 1)
#define __CCHARS_INIT__(array) cchars_init(array, sizeof(array)/sizeof(char) - 1)

#endif /* cchars.h */

