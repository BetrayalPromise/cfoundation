#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>

struct array {
	long count;		// readonly 存储数量
	long capacity;	// readonly 默认存储容量
	void ** store;	// readonly 存储位置
};

extern struct array * array_init(void);
extern long array_count(struct array * array);
extern bool array_insert(struct array * array, void * dataaddress, long position);
extern bool array_remove(struct array * array, long position);
extern void * array_index(struct array * array, long position);
extern void array_free(struct array * array);
extern void array_swap(struct array * array, long i, long j);

#endif
