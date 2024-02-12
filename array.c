#ifndef __ARRAY_C__
#define __ARRAY_C__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

void array_capacity(struct array * array, unsigned long multiple);

struct array * array_init(int size) {
	struct array * array = malloc(sizeof(struct array));
	if (array == NULL) {
		printf("information: string init failure!\n");
		return NULL;
	}
	long capacity = 64;
	array->store = malloc(sizeof(void *) * capacity);
	array->capacity = capacity;
	array->count = 0;
	array->size = size;
	return array;
}

long array_count(struct array * array) {
	return array->count;
}

bool array_insert(struct array * array, void * data, long position) {
	if (array == NULL) {
		printf("information: string is NULL!\n");
		return false;
	}
	// 数组扩容
	while (array->count + 1 > array->capacity) {
		array_capacity(array, 2);
	}

	if (position <= 0) {
		position = 0;
	} else if (position > array->count) {
		position = array->count;
	}

	if (array->count == 0) {
		array->store[0] = data;
		array->count ++;
		return true;
	}

	if (position > array->count) {
		array->store[array->count] = data;
		array->count ++;
		return true;
	}

	int start = array->count - 1;
	for (int i = start; i >= position; i --) {
		array->store[i + 1] = array->store[i];
	}
	//将数据插入到指定位置
	array->store[position] = data;
	//更新数组大小
	array->count ++;
	return true;
}

bool array_remove(struct array * array, long position) {
	if (array == NULL) {
		printf("information: array is null, operation has no effect!\n");
		return false;
	}
	if (position < 0 || position > array->count - 1) {
		printf("information: position(%ld) is out of range(0-%ld), operation has no effect!\n", position, array->count - 1);
		return false; 
	}
	//删除指定元素	从后往前移动
	for (int i = position; i < array->count; i++) {
		array->store[i] = array->store[i + 1];
	}
	--array->count;
	return true;
}

void * array_index(struct array * array, long position) {
	if (position < 0 || position > array->count) {
		return NULL;
	}
	return array->store[position];
}

void array_capacity(struct array * array, unsigned long multiple) {
	int newcapacity = array->capacity * multiple;
	void * newspace = malloc(sizeof(void) * newcapacity);
	memcpy(newspace, array->store, sizeof(void) * array->capacity);
	free(array->store);
	array->store = newspace;
	array->capacity = newcapacity;
}

#endif