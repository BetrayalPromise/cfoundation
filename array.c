#ifndef __ARRAY_C__
#define __ARRAY_C__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

void array_capacity(struct array * array, unsigned long multiple);
static bool test(struct array * array);

struct array * array_init(long typesize) {
	// printf("sizeof(void)   = %lu\n", sizeof(void));
	// printf("sizeof(void *) = %lu\n", sizeof(void *));
	struct array * array = malloc(sizeof(struct array));

	if (!test(array)) { return NULL; }

	long capacity = 32;
	if (typesize > 0) {
		array->store = malloc(typesize * capacity);
	} else {
		array->store = malloc(sizeof(void *) * capacity);
	}
	array->capacity = capacity;
	array->count = 0;
	array->typesize = typesize;
	return array;
}

long array_count(struct array * array) {
	return array->count;
}

bool array_append(struct array * array, void * address) {
	return array_insert(array, address, array->count);
}

static bool test(struct array * array) {
	if (array == NULL) {
		printf("information: array(struct array *) is NULL!\n");
	}
	return array != NULL ? true : false;
}


bool array_copy_address(struct array * array, void * address, long index) {
	int start = array->count - 1;
	for (int i = start; i >= index; i --) {
		array->store[i + 1] = array->store[i];
	}
	array->store[index] = address;
	array->count ++;
	return true;
}

bool array_copy_value(struct array * array, void * address, long index) {
	int size = array->count - index;
	if (size > 0) {
		memcpy(&array->store[0] + array->typesize * (index + 1), &array->store[0] + array->typesize * index, array->typesize * size);
	}
	memcpy(&array->store[0] + array->typesize * index, address, array->typesize);
	array->count ++;
	return true;
}

bool array_insert(struct array * array, void * address, long index) {
	if (!test(array)) { return false; }
	// 数组扩容
	while (array->count + 1 > array->capacity) {
		array_capacity(array, 2);
	}
	// index[0, array->count]
	if (index < 0) {
		index = 0;
	} else if (index > array->count) {
		index = array->count;
	}
	if (array->typesize > 0) {
		return array_copy_value(array, address, index);
	} else {
		return array_copy_address(array, address, index);
	}
}

bool array_remove(struct array * array, long index) {
	if (!test(array)) { return false; }
	if (index < 0 || index > array->count - 1) {
		printf("information: index(%ld) is out of range(0-%ld)!\n", index, array->count - 1);
		return false; 
	}
	//删除指定元素	从后往前移动
	for (int i = index; i < array->count; i++) {
		array->store[i] = array->store[i + 1];
	}
	-- array->count;
	return true;
}

void * array_index(struct array * array, long index) {
	if (!test(array)) { return false; }
	if (index < 0 || index > array->count) {
		printf("information: index(%ld) is out of range(0-%ld)!\n", index, array->count - 1);
		return NULL;
	}
	if (array->typesize <= 0) {
		return array->store[index];
	} else {
		return &array->store[0] + array->typesize * index;
	}
}

void array_capacity(struct array * array, unsigned long multiple) {
	int newcapacity = array->capacity * multiple;
	if (array->typesize <= 0) {
	
	} else {
	
	}
	void * newspace = malloc(sizeof(void *) * newcapacity);
	memcpy(newspace, array->store, sizeof(void *) * array->capacity);
	free(array->store);
	array->store = newspace;
	array->capacity = newcapacity;
}

void array_free(struct array * array) {
	if (!test(array)) { return; }
	if (array->store != NULL) {
		free(array->store);
		array->store = NULL;
		free(array);
		array = NULL;
	}
}

void array_swap(struct array * array, long i, long j) {
	if (!test(array)) { return; }
	if (0 <= i && i < array->count && 0 <= j && j < array->count) {
		void * temp = array->store[i];
    	array->store[i] = array->store[j];
    	array->store[j] = temp;
	} else {
		printf("information: index(%ld), index(%ld) is out of range(0-%ld)!\n", i, j, array->count - 1);
	}
}

// 插入排序
// void insert_sort(struct array * array) {
// 	for (int i = 0; i < array->count - 1; i++) {
// 		int end = i;
// 		void * tmp = array->store[end + 1];
// 		while (end >= 0) {
// 			if (array->store[end] > tmp) {
// 				array->store[end + 1] = array->store[end]; 
// 				end--;
// 			} else {
// 				break;
// 			}
// 		}
// 		array->store[end + 1] = tmp; 
// 	}
// }

// void shell_sort(struct array * array) {
// 	int gap = array->count; 
// 	while (gap > 1) {
// 		gap = gap / 3 + 1;
// 		for (int i = 0; i < array->count - gap; ++i) {
// 			int end = i;
// 			void * tmp = array->store[end + gap];
// 			while (end >= 0) {
// 				if (array->store[end] > tmp) {
// 					array->store[end + gap] = array->store[end];
// 					end -= gap;
// 				} else {
// 					break;
// 				}
// 			}
// 			array->store[end + gap] = tmp;
// 		}
// 	}
// }

// void select_sort(struct array * array) {
// 	int begin = 0, end = array->count - 1;
// 	while (begin < end) {
// 		int max = begin, min = begin;
// 		for (int i = begin; i <= end; i ++) {
// 			if (array->store[i] > array->store[max])
// 				max = i;
// 			if (array->store[i] < array->store[min])
// 				min = i;
// 		}
// 		if (begin == max)
// 			max = min;
// 		array_swap(array, begin, min);
// 		array_swap(array, end, max);
// 		begin++;
// 		end--;
// 	}
// }

#endif