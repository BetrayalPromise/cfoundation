#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>

typedef struct Array {
	long typesize;	// readonly item字长
	long length;	// readonly 存储数量
	long volume;	// readonly 默认存储容量
	void ** store;	// readonly 存储位置 存储的均为指针
} array_t;

/*
	@return		返回指向struct Array的指针
	@parameter	typesize元素字长,typesize小于等于0,数组存储指向元素的指针,数据类型可任意,依赖原始数据的生命周期typesize等于sizeof(T),T:char,bool,int,double...,复制元素,数据类型为统一的具体N个字节的数组,不依赖原始数据的生命周期具体存储为该类型[T, T, T, ...]
*/ 
extern struct Array * arrayinit(long typesize);

/*
	@return		返回数组的元素数量
	@parameter	array数组
*/
extern long arraylength(struct Array * array);

/*
	@return		操作是否成功
	@parameter	array数组
	@parameter	address元素的地址
	@parameter	index插入位置
*/
extern bool arrayinsert(struct Array * array, void * address, long index);

/*
	@return		操作是否成功
	@parameter	array数组
	@parameter	index插入位置
*/
extern bool arrayremove(struct Array * array, long index);

/*
	@return		索引地址
	@parameter	array数组
	@parameter	index插入位置
*/
extern void * arrayindex(struct Array * array, long index);

/*
	@parameter	array数组
*/
extern void arrayfree(struct Array * array);

/*
	@parameter	array数组
	@parameter	i插入位置
	@parameter	j插入位置
*/
extern void arrayswap(struct Array * array, long i, long j);

#endif
