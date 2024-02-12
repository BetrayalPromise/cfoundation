#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>

struct array {
    long size;		// readonly 存在单个元素字长
	long count;		// readonly 存储数量
	long capacity;	// readonly 默认存储容量
	void ** store;	// readonly 存储位置
};

extern struct array * array_init(int size);
extern long array_count(struct array * array);
extern bool array_insert(struct array * array, void * data, long position);
extern bool array_remove(struct array * array, long position);
extern void * array_index(struct array * array, long position) ;

#endif
