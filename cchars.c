#ifndef __CCHARS_C__
#define __CCHARS_C__

#include "cchars.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void cchars_capacity(cchars_t * cs, unsigned long multiple);
static int cchars_compare(void * input0, void * input1);

static bool check(cchars_t * cs) {
	if (cs == NULL) {
		printf("information: string is null, operation has no effect!\n");
		return false;
	} else {
		return true;
	}
}

cchars_t * cchars_init(const char * str, long count) {
	cchars_t * cs = malloc(sizeof(cchars_t));
	if (!check(cs)) {
		return NULL;
	}
	if (str == NULL) {
		// 默认初始化
		long capacity = 64;
		cs->capacity = capacity;
		cs->store = (char *)malloc(sizeof(char) * capacity);
		cs->count = 0;
		return cs;
	} else {
		long capacity = count > 0 ? count : strlen(str);
		cs->capacity = capacity;
		cs->store = (char *)malloc(sizeof(char) * capacity);
		cs->count = capacity;
		for (int i = 0; i < capacity; ++ i) {
			cs->store[i] = str[i];
		}
		return cs;
	}
}

void cchars_free(cchars_t * cs) {
	if (!check(cs)) {
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

bool cchars_insert_character(cchars_t * cs, long position, char data) {
	if (!check(cs)) { return false; }
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
	return true;
}

// bool cchars_insert_cstring(cchars_t * cs, long position, char * str) {
// 	if (!check(cs)) { return false; }

// 	while (cs->count + strlen(str) + 1 > cs->capacity) {
// 		cchars_capacity(cs, 2);
// 	}

// 	if (position <= 0) {
// 		position = 0;
// 	} else if (position > cs->count) {
// 		position = cs->count;
// 	}

// 	if (cs->count == 0) {
// 		for (int i = 0; i < strlen(str) + 1; i ++) {
// 			cs->store[i] = *str ++;
// 			++ cs->count;
// 		}
// 		return true;
// 	}

// 	if (position > cs->count) {
// 		for (int i = 0; i < strlen(str) + 1; i ++) {
// 			cs->store[cs->count - 1] = *str ++;
// 			++ cs->count;
// 		}
// 		return true;
// 	}

// 	int start = cs->count - 1;
// 	for (int i = start; i >= position; i --) {
// 		cs->store[i + 1] = cs->store[i];
// 	}
// 	//将数据插入到指定位置
// 	cs->store[position] = data;
// 	return true;
// }

bool cchars_change_character(cchars_t * cs, long position, char data) {
	if (!check(cs)) { return false; }
	if (position < 0 || position > cs->count - 1) {
		printf("information: position(%ld) is out of range(0-%ld), operation has no effect!\n", position, cs->count - 1);
		return false; 
	}
	cs->store[position] = data;
	return true;
}

bool cchars_remove_position(cchars_t * cs, long position) {
	if (!check(cs)) { return false; }
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

bool cchars_remove_character(cchars_t * cs, char data) {
	if (!check(cs)) { return false; }

	int j = 0;
	int time = 0;
    for(int i = 0; i < cs->count; i ++) {
		if (cs->store[i] != data) {
			cs->store[j ++] = cs->store[i];
		} else {
			++ time;
		}
    }
	cs->count -= time;
	for (; j < cs->count; j ++) {
		cs->store[j] = 0x00;
	}
	return true;
}

bool cchars_remove_cchars(cchars_t * cs, cchars_t *c) {
	if (!check(cs) && !check(c)) { return false; }

	return true;
}

char * cchars_mutate_cstring(cchars_t * cs) {
	if (!check(cs)) { return NULL; }
	char * c = malloc(sizeof(char) * cs->count + 1);
	c[cs->count] = '\0';
	for (int i = 0; i < cs->count; i ++) {
		c[i] = cs->store[i];
	}
	return c;
}

void cchars_description(cchars_t * cs) {
	for (int i = 0; i < cs->count; i ++) {
		if (cs->store[i] == '\0') {
			printf("'\\0' ");
		} else {
			printf("'%c' ", cs->store[i]);
		}
	}
	printf("\n");
}

cchars_t * cchars_copy(cchars_t * cs) {
	// todo:
	return NULL;
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