#ifndef __CCHARS_C__
#define __CCHARS_C__

#include "cchars.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void cchars_capacity(cchars_t * cs, unsigned long multiple);
static int cchars_compare(void * input0, void * input1);

cchars_t * cchars_init() {
	cchars_t * cs = malloc(sizeof(cchars_t));
	if (cs == NULL) {
		printf("information: string init failure, operation has no effect!\n");
		return NULL;
	}
	//给属性初始化
	long capacity = 64;
	cs->capacity = capacity;
	cs->store = (char *)malloc(sizeof(char) * capacity);
	cs->count = 0;
	return cs;
}

cchars_t * cchars_string(const char * str, long count) {
	if (count < 0) {
		return NULL;
	}
	cchars_t * cs = malloc(sizeof(cchars_t));
	if (cs == NULL) {
		printf("information: chars init failure, operation has no effect!\n");
		return NULL;
	}
	long capacity = count > 0 ? count : strlen(str);
	cs->capacity = capacity;
	cs->store = (char *)malloc(sizeof(char) * capacity);
	cs->count = capacity;
	for (int i = 0; i < capacity; ++ i) {
		cs->store[i] = str[i];
	}
	return cs;
}

void cchars_free(cchars_t * cs) {
	if (cs == NULL) {
		printf("information: string is null, operation has no effect!\n");
		return;
	}
	//内部维护在堆区数组指针先释放
	if (cs->store != NULL) {
		char * p = cs->store;
		for (int i = 0; i < cs->count; ++ i) {
			free(p++);
		}
		p = NULL;
		free(cs->store);
		cs->store = NULL;
	}
	free(cs);
	cs = NULL;
}

long cchars_length(cchars_t * cs) {
	return cs->count;
}

bool cchars_insert(cchars_t * cs, long position, char data) {
	if (cs == NULL) {
		printf("information: string is null, operation has no effect!\n");
		return false;
	}
	// 数组扩容
	while (cs->count + 1 > cs->capacity) {
		cchars_capacity(cs, 2);
	}

	if (position <= 0) {
		position = 0;
	} else if (position > cs->count) {
		position = cs->count;
	}

	if (cs->count == 0) {
		cs->store[0] = data;
		cs->count ++;
		return true;
	}

	if (position > cs->count) {
		cs->store[cs->count] = data;
		cs->count ++;
		return true;
	}

	int start = cs->count - 1;
	for (int i = start; i >= position; i --) {
		cs->store[i + 1] = cs->store[i];
	}
	//将数据插入到指定位置
	cs->store[position] = data;
	//更新数组大小
	return true;
}

bool cchars_remove(cchars_t * cs, long position) {
	if (cs == NULL) {
		printf("information: array is null, operation has no effect!\n");
		return false;
	}
	if (position < 0 || position > cs->count - 1) {
		printf("information: position(%ld) is out of range(0-%ld), operation has no effect!\n", position, cs->count - 1);
		return false; 
	}
	//删除指定元素	从后往前移动
	for (int i = position; i < cs->count; i++) {
		cs->store[i] = cs->store[i + 1];
	}
	--cs->count;
	return true;
}

void cchars_capacity(cchars_t * cs, unsigned long multiple) {
	int newcapacity = cs->capacity * multiple;
	char * newspace = malloc(sizeof(char) * newcapacity);
	memcpy(newspace, cs->store, sizeof(char) * cs->capacity);
	free(cs->store);
	cs->store = newspace;
	cs->capacity = newcapacity;
}

static int cchars_compare(void * input0, void * input1) {
	cchars_t * source0 = input0;
	cchars_t * source1 = input1;
	if (source0 != NULL && source1 != NULL) {
	
	}
	if (source0->count == source1->count) {
		for (int i = 0; i < source0->count; i ++) {
			if (source0->store[i] == source1->store[i]) {
				continue;
			} else {
				return -1;
			}
		}
		return 0;
	}
	return -1;
}

#endif /* cchars.c */