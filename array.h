#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>

struct array {
	long itemsize;	// readonly item字长
	long count;		// readonly 存储数量
	long capacity;	// readonly 默认存储容量
	void ** store;	// readonly 存储位置 存储的均为指针
};

/*
	@return		返回指向struct array的指针
	@parameter	itemsize元素字长,itemsize小于等于0,数组存储指向元素的指针;itemsize等于sizeof(T),T:char,bool,int,double...,复制元素
*/ 
extern struct array * array_init(long itemsize);

/*
	@return		返回数组的元素数量
	@parameter	array数组
*/
extern long array_count(struct array * array);

/*
	@return		操作是否成功
	@parameter	array数组
	@parameter	dataaddress元素的地址
	@parameter	index插入位置
*/
extern bool array_insert(struct array * array, void * dataaddress, long index);

/*
	@return		操作是否成功
	@parameter	array数组
	@parameter	index插入位置
*/
extern bool array_remove(struct array * array, long index);

/*
	@return		索引地址
	@parameter	array数组
	@parameter	index插入位置
*/
extern void * array_index(struct array * array, long index);

/*
	@parameter	array数组
*/
extern void array_free(struct array * array);

/*
	@parameter	array数组
	@parameter	i插入位置
	@parameter	j插入位置
*/
extern void array_swap(struct array * array, long i, long j);

#endif
