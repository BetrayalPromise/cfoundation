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
	if (!check(cs)) { return NULL; }
	if (str == NULL || strlen(str) == 0) {
		// 默认初始化
		long capacity = 64;
		cs->capacity = capacity;
		cs->store = (char *)malloc(sizeof(char) * capacity);
		cs->count = count;
		for (int i = 0; i < count; i ++) {
			cs->store[i] = str[i];
		}
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
		++ cs->count;
		return true;
	}

	if (position > cs->count) {
		cs->store[cs->count] = data;
		++ cs->count;
		return true;
	}

	int start = cs->count - 1;
	for (int i = start; i >= position; i --) {
		cs->store[i + 1] = cs->store[i];
	}
	//将数据插入到指定位置
	cs->store[position] = data;
	++ cs->count;
	return true;
}

bool cchars_append_character(cchars_t * cs, char data) {
	return cchars_insert_character(cs, cs->count, data);
}

bool cchars_insert_cchars(cchars_t * cs, long position, cchars_t * data) {
	if (!check(cs)) { return false; }

	while (cs->count + data->count > cs->capacity) {
		cchars_capacity(cs, 2);
	}

	if (position <= 0) {
		position = 0;
	} else if (position > cs->count) {
		position = cs->count;
	}

	if (cs->count == 0) {
		for (int i = 0; i < data->count; i ++) {
			cs->store[i] = data->store[i];
			++ cs->count;
		}
		return true;
	}

	if (position > cs->count) {
		for (int i = 0; i < data->count; i ++) {
			cs->store[cs->count - 1] = data->store[i];
			++ cs->count;
		}
		return true;
	}

	int start = cs->count - 1;
	for (int i = start; i >= position; i --) {
		cs->store[i + 1] = cs->store[i];
	}
	//将数据插入到指定位置
	// cs->store[position] = data;

	for (int i = 0; i < data->count; i ++) {
		cs->store[position + i] =data->store[i];
	}
	cs->count += data->count;
	return true;
}

bool cchars_change_character(cchars_t * cs, long position, char data) {
	if (!check(cs)) { return false; }
	if (position < 0 || position > cs->count - 1) {
		printf("information: position(%ld) is out of range(0-%ld), operation has no effect!\n", position, cs->count - 1);
		return false; 
	}
	cs->store[position] = data;
	return true;
}

bool cchars_remove_boundary(cchars_t * cs, long position, long size) {
	if (!check(cs) && size > 0) { return false; }
	// if (position < 0 || position > cs->count - 1) {
	// 	printf("information: position(%ld) is out of range(0-%ld), operation has no effect!\n", position, cs->count - 1);
	// 	return false; 
	// }
	// //删除指定元素	从后往前移动
	// for (int i = position; i < cs->count; i++) {
	// 	cs->store[i] = cs->store[i + 1];
	// }
	// --cs->count;

	/*
	   9876543210123456789
				987654321
			        4  
			        123456   
	*/

	long start = 0;
	long stop = 0;

	if (position < 0) {
		if (position + size - 1 < 0) { return false; }
		start = 0;
		stop = position + size - 1 > cs->count - 1 ? cs->count - 1 : position + size - 1;
	} else if (position == 0) {
		start = position;
		stop = position + size - 1 > cs->count -1 ? cs->count - 1 : position + size - 1;
	} else {
		if (position > cs->count - 1) { return false; }
		start = position;
		stop = position + size - 1 > cs->count -1 ? cs->count - 1 : position + size - 1;
	}
	printf("start = %ld, stop = %ld\n", start, stop);

	long i = start;
	long j = stop;
	for (; i < cs->count - (stop - start + 1); i ++) {
		cs->store[i] = cs->store[stop - start + 1 + i];
		cs->store[stop - start + 1 + i] = 0x00;
	}
	cs->count -= stop - start + 1;
	return true;
}

bool cchars_append_cchars(cchars_t * cs, cchars_t * data) {
	return cchars_insert_cchars(cs, cs->count, data);
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

bool cchars_remove_cchars(cchars_t * cs, cchars_t * data) {
	if (!check(cs) && !check(data)) { return false; }

	return true;
}

long * cchars_search_character(cchars_t * cs, char data) {
	if (!check(cs)) { return NULL; }
	long * info = malloc(sizeof(long) * cs->count + 1);
	info[0] = 0;
	for (int i = 0; i < cs->count; i ++) {
		if (cs->store[i] == data) {
			info[info[0] + 1] = i;
			info[0] += 1;
		}
	}
	return info;
}

long * cchars_search_cchars(cchars_t * cs, cchars_t * data) {
	if (!check(cs) && !check(data) || data->count > cs->count) {
		return NULL;
	}
	long * info = malloc(sizeof(long) * cs->count + 1);
	info[0] = 0;
	int i = 0;
	int j = 0;
	int index = -1;
	for (; i < cs->count - data->count + 1;) {
		for (; j < data->count;) {
			if (cs->store[i] != data->store[j]) {
				if (index == -1) {
					++ i;
				} else {
					i = index + 1;
				}
				index = -1;
				j = 0;
				break;
			} else {
				if (index == -1) {
					index = i;
				}
				if (j + 1 == data->count) {
					j = 0;
					i = index + 1;
					// printf("index: %d\n", index);
					// info->start[info->count] = index;
					// info->count += 1;
					info[info[0] + 1] = index;
					info[0] += 1;
					index = -1;
					break;
				}
				++ j;
				++ i;
			}
		}
	}
	return info;
}

bool cchars_change_cchars(cchars_t * cs, long position, cchars_t * data) {
	if (!check(cs) && !check(data)) { return false; }
	if (cs->count <= 0 || data->count <= 0) { return false; }

	long location = 0;

	long index = 0;
	long size = 0;

	if (position < 0) {
		if (position + data->count <= 0) {
			return false;
		} else {
			index = labs(position);
			size = position + data->count < cs->count ? position + data->count : cs->count;
			location = 0;
		}
	} else if (position == 0) {
		index = 0;
		size = cs->count > data->count ? data->count : cs->count;
		location = 0;
	} else {
		if (position >= cs->count) {
			return false;
		} else {
			index = 0;
			size = position + data->count < cs->count ? data->count : cs->count - position;
			location = position;
		}
	}
	printf("location:%ld, index: %ld, size: %ld\n", location, index, size);
	long i = location;
	long j = index;

	/*
	9876543210123456789
	         aaaaa
			    87
	*/

	for (; i < size + location; i ++) {
		cs->store[i] = data->store[j];
		j ++;
	}

	return false;
}

char * cchars_mutate_cstring(cchars_t * cs) {
	if (!check(cs)) { return NULL; }
	long size = sizeof(long);
	char * c = malloc(sizeof(char) * cs->count + size + 1);
	*(long *)c = cs->count;
	for (int i = 0; i < cs->count; i ++) {
		c[i + size] = cs->store[i];
	}
	c[cs->count + size] = 0x00;
	return c;
}

void cchars_description(cchars_t * cs, long flag) {
	printf("CCHARS(%p).count = %ld\nCCHARS(%p).capacity = %ld\nsize = %lu Byte\n[\n", cs, cs->count, cs, cs->capacity, sizeof(char));
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "    (H:0x%02x  D:%03d  C:%c)"; break;
	case 0b110: show = "    (H:0x%02x  D:%03d)"; break;
	case 0b101: show = "    (H:0x%02x  C:%c)"; break;
	case 0b011: show = "    (D:%03d  C:%c)"; break;
	case 0b100: show = "    (H:0x%02x)"; break;
	case 0b010: show = "    (D:%03d)"; break;
	case 0b001: show = "    (C:%c)"; break;
	default:    show = "    (H:0x%02x  D:%03d  C:%c)"; break;
	}
	for (int i = 0; i < cs->count; i ++) {
		printf(show, cs->store[i], cs->store[i], cs->store[i]);
		if (i != cs->count - 1) {
			printf(",\n");
		} else {
			printf("\n");
		}
	}
	printf("]\n");
}

void cchars_search_description(long * info) {
	printf("search.size = %ld\n[\n", info[0]);
	for (int i = 0; i < info[0]; i ++) {
		char * show = i == info[0] - 1 ? "    (index: %ld)\n" : "    (index: %ld),\n";
		printf(show, info[i + 1]);
	}
	printf("]\n");
}

void cchars_ascii_form() {
	printf("Dec   Hex    Char\n");
	for (int i = 0; i < 128; i ++) {
		printf("%03d   0x%02x   %c\n", i, i, i);
	}
}

cchars_t * cchars_copy(cchars_t * cs) {
	if (!check(cs)) { return NULL; } 
	cchars_t * init = malloc(sizeof(cchars_t));
	init->count = cs->count;
	init->capacity = cs->capacity;
	init->store = malloc(sizeof(char) * cs->capacity);
	for (int i = 0; i < cs->count; i ++) {
		init->store[i] = cs->store[i];
	}
	return init;
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