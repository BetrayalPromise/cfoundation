#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"

bool cstringcheck(char * source) {
	return source == NULL ? false : true;
}

char * cstring(char * source) {
	if (!cstringcheck(source)) {
		return NULL;
	}
    // "zzz" 字面量存储在静态区域里 不需要释放
	// return "zzz";
    long size = sizeof(long);
    char * index = malloc(sizeof(char) * strlen(source) + 1 + size);
    char * string = index + size;
    *(long *)index = sizeof(char) * strlen(source) + 1;

    for (int i = 0; i < strlen(source) + 1; i ++) {
        string[i] = source[i];
    }
    return string;
}

long cstringlength(char * source) {
	if (!cstringcheck(source)) { return -1; }
    long size = sizeof(long);
    char * index = source - size;
    long len = *(long *)index;
    index = NULL;
    return len;
}

void cstringdescribe(char * cstring, long flag) {
    printf("[long|char...]: (%p)\n[\n", cstring);
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "    (%ld Byte, H:0x%02x  D:%03d  C:%c)"; break;
	case 0b110: show = "    (%ld Byte, H:0x%02x  D:%03d)"; break;
	case 0b101: show = "    (%ld Byte, H:0x%02x  C:%c)"; break;
	case 0b011: show = "    (%ld Byte, D:%03d  C:%c)"; break;
	case 0b100: show = "    (%ld Byte, H:0x%02x)"; break;
	case 0b010: show = "    (%ld Byte, D:%03d)"; break;
	case 0b001: show = "    (%ld Byte, C:%c)"; break;
	default:    show = "    (%ld Byte, H:0x%02x  D:%03d  C:%c)"; break;
	}

    long size = sizeof(long);
	char * index = cstring - size;
    long count = *(long *)index;

    if (count == 0) {
		printf("    (%ld Byte, H:0x%016lx  D:%032ld  CharArray.count = %ld)\n", size, count, count, count);
	} else {
		printf("    (%ld Byte, H:0x%016lx  D:%032ld  CharArray.count = %ld),\n", size, count, count, count);
	}
	
	for (int i = 0; i < count; i ++) {
		printf(show, sizeof(char), cstring[i], cstring[i], cstring[i]);
		if (i != count - 1) {
			printf(",\n");
		} else {
			printf("\n");
		}
	}
	printf("]\n");
}

// void cstring
// strcpy

char * cstringcopy(char * source) {
	if (!cstringcheck(source)) { return NULL; }
	char * index = NULL;
	memcpy(index, source, cstringlength(source) + sizeof(long));
	return index - sizeof(long);
}

#endif