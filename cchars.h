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

extern cchars_t * cchars_init();
extern cchars_t * cchars_string(const char * str, long count);
extern void cchars_free(cchars_t * cs);
extern long cchars_length(cchars_t * cs);
extern bool cchars_insert(cchars_t * cs, long position, char data);
extern bool cchars_remove(cchars_t * cs, long position);
// extern cchars_t * cchars_copy(cchars_t * cs);

#define CCHARS(name, string)\
	struct cchars name = { -1, -1, NULL };\
	do {\
		char array[] = string;\
		name.capacity = sizeof(array)/sizeof(char) - 1;\
		name.count = sizeof(array)/sizeof(char) - 1;\
		name.store = NULL;\
	} while(0);
	
#endif /* cchars.h */

