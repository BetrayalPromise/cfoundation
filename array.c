#ifndef __ARRAY_C__
#define __ARRAY_C__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

void array_capacity(struct array * array, unsigned long multiple);

struct array * array_init(void) {
	struct array * array = malloc(sizeof(struct array));
	if (array == NULL) {
		printf("information: string init failure!\n");
		return NULL;
	}
	long capacity = 64;
	array->store = malloc(sizeof(void *) * capacity);
	array->capacity = capacity;
	array->count = 0;
	return array;
}

long array_count(struct array * array) {
	return array->count;
}

bool array_insert(struct array * array, void * dataaddress, long position) {
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
		array->store[0] = dataaddress;
		array->count ++;
		return true;
	}

	if (position > array->count) {
		array->store[array->count] = dataaddress;
		array->count ++;
		return true;
	}

	int start = array->count - 1;
	for (int i = start; i >= position; i --) {
		array->store[i + 1] = array->store[i];
	}
	//将数据插入到指定位置
	array->store[position] = dataaddress;
	//更新数组大小
	array->count ++;
	return true;
}

bool array_remove(struct array * array, long position) {
	if (array == NULL) {
		printf("information: array is null!\n");
		return false;
	}
	if (position < 0 || position > array->count - 1) {
		printf("information: position(%ld) is out of range(0-%ld)!\n", position, array->count - 1);
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
	if (array == NULL) {
		printf("information: array is null!\n");
		return NULL;
	}
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

void array_free(struct array * array) {
	if (array == NULL) {
		printf("information: array is null!\n");
		return;
	}
	if (array->store != NULL) {
		free(array->store);
		array->store = NULL;
		free(array);
		array = NULL;
	}
}

void array_swap(struct array * array, long i, long j) {
	if (array == NULL) {
		printf("information: index error!\n");
		return;
	}
	if (0 <= i && i < array->count && 0 <= j && j < array->count) {
		void * temp = array->store[i];
    	array->store[i] = array->store[j];
    	array->store[j] = temp;
	}
}

// void array_insert_sort(struct array * array) {
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

// void array_shell_sort(struct array * array) {
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

// void array_select_sort(struct array * array) {
// 	int begin = 0, end = array->count - 1;
// 	while (begin < end) {
// 		int max = begin, min = begin;
// 		for (int i = begin; i <= end; i ++) {
// 			if (array->store[i] > array->store[max])
// 				max = i;
// 			if (array->store[i] < array->store[min])
// 				min = i;
// 		}
// 		if (begin == max) //若最大数据在begin位置，与begin下标重合，则需进行修正
// 			max = min;
// 		array_swap(array, begin, min); //进行交换
// 		array_swap(array, end, max);
// 		begin++;
// 		end--;
// 	}
// }

#endif