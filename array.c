#ifndef __ARRAY_C__
#define __ARRAY_C__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

void array_capacity(struct Array * array, unsigned long multiple);
static bool test(struct Array * array);

struct Array * arrayinit(long typesize) {
	// printf("sizeof(void)   = %lu\n", sizeof(void));
	// printf("sizeof(void *) = %lu\n", sizeof(void *));
	struct Array * array = malloc(sizeof(struct Array));

	if (!test(array)) { return NULL; }

	long capacity = 32;
	if (typesize > 0) {
		array->store = malloc(typesize * capacity);
	} else {
		array->store = malloc(sizeof(void *) * capacity);
	}
	array->volume = capacity;
	array->length = 0;
	array->typesize = typesize;
	return array;
}

long arraylength(struct Array * array) {
	return array->length;
}

bool arrayappend(struct Array * array, void * address) {
	return arrayinsert(array, address, array->length);
}

static bool test(struct Array * array) {
	if (array == NULL) {
		printf("information: array(struct Array *) is NULL!\n");
	}
	return array != NULL ? true : false;
}


bool array_copy_address(struct Array * array, void * address, long index) {
	int start = array->length - 1;
	for (int i = start; i >= index; i --) {
		array->store[i + 1] = array->store[i];
	}
	array->store[index] = address;
	array->length ++;
	return true;
}

bool array_copy_value(struct Array * array, void * address, long index) {
	int size = array->length - index;
	if (size > 0) {
		memcpy(&array->store[0] + array->typesize * (index + 1), &array->store[0] + array->typesize * index, array->typesize * size);
	}
	memcpy(&array->store[0] + array->typesize * index, address, array->typesize);
	array->length ++;
	return true;
}

bool arrayinsert(struct Array * array, void * address, long index) {
	if (!test(array)) { return false; }
	// 数组扩容
	while (array->length + 1 > array->volume) {
		array_capacity(array, 2);
	}
	// index[0, array->length]
	if (index < 0) {
		index = 0;
	} else if (index > array->length) {
		index = array->length;
	}
	if (array->typesize > 0) {
		return array_copy_value(array, address, index);
	} else {
		return array_copy_address(array, address, index);
	}
}

bool arrayremove(struct Array * array, long index) {
	if (!test(array)) { return false; }
	if (index < 0 || index > array->length - 1) {
		printf("information: index(%ld) is out of range(0-%ld)!\n", index, array->length - 1);
		return false; 
	}
	//删除指定元素	从后往前移动
	for (int i = index; i < array->length; i++) {
		array->store[i] = array->store[i + 1];
	}
	-- array->length;
	return true;
}

void * arrayindex(struct Array * array, long index) {
	if (!test(array)) { return false; }
	if (index < 0 || index > array->length) {
		printf("information: index(%ld) is out of range(0-%ld)!\n", index, array->length - 1);
		return NULL;
	}
	if (array->typesize <= 0) {
		return array->store[index];
	} else {
		return &array->store[0] + array->typesize * index;
	}
}

void arraycapacity(struct Array * array, unsigned long multiple) {
	int newcapacity = array->volume * multiple;
	if (array->typesize <= 0) {
	
	} else {
	
	}
	void * newspace = malloc(sizeof(void *) * newcapacity);
	memcpy(newspace, array->store, sizeof(void *) * array->volume);
	free(array->store);
	array->store = newspace;
	array->volume = newcapacity;
}

void arrayfree(struct Array * array) {
	if (!test(array)) { return; }
	if (array->store != NULL) {
		free(array->store);
		array->store = NULL;
		free(array);
		array = NULL;
	}
}

void arrayswap(struct Array * array, long i, long j) {
	if (!test(array)) { return; }
	if (0 <= i && i < array->length && 0 <= j && j < array->length) {
		void * temp = array->store[i];
    	array->store[i] = array->store[j];
    	array->store[j] = temp;
	} else {
		printf("information: index(%ld), index(%ld) is out of range(0-%ld)!\n", i, j, array->length - 1);
	}
}

#endif