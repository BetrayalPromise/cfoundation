#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cstring.h"

bool cstringcheck(char * cstr) {
	return cstr == NULL ? false : true;
}

/*
	return "zzz"; "zzz" 字面量存储在静态区域里 不需要释放
*/
char * cstring(char * str) {
	if (!cstringcheck(str)) { return NULL; }

    long volumesize = sizeof(long);
	long lengthsize = sizeof(long);

	long charsize = sizeof(char) * strlen(str) + 1;
    char * cstr = malloc(volumesize + lengthsize + charsize);
    char * string = cstr + volumesize + lengthsize;

    *(long *)cstr = charsize;
	*(long *)(cstr + volumesize) = charsize;

	// printf("%ld, %ld\n", *(long *)cstr, *(long *)(cstr + volumesize));

    for (int i = 0; i < strlen(str) + 1; i ++) {
        string[i] = str[i];
    }
    return string;
}

long cstringlength(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - sizeof(long));
}

long cstringvolume(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - 2 * sizeof(long));
}

void cstringdescribe(char * cstr, long flag) {
	if (!cstringcheck(cstr)) { return; }
    printf("[long|long|char...]: (%p)\n[\n", cstr);
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "    (%ld Byte    H:0x%02x  D:%03d  C:%c)"; break;
	case 0b110: show = "    (%ld Byte    H:0x%02x  D:%03d)"; break;
	case 0b101: show = "    (%ld Byte    H:0x%02x  C:%c)"; break;
	case 0b011: show = "    (%ld Byte    D:%03d  C:%c)"; break;
	case 0b100: show = "    (%ld Byte    H:0x%02x)"; break;
	case 0b010: show = "    (%ld Byte    D:%03d)"; break;
	case 0b001: show = "    (%ld Byte    C:%c)"; break;
	default:    show = "    (%ld Byte    H:0x%02x  D:%03d  C:%c)"; break;
	}

	long volumesize = 2 * sizeof(long);
    long volume = *(long *)(cstr - volumesize);
	printf("    (%ld Byte    H:0x%016lx  D:%032ld  Chars.volume = %ld),\n", volumesize / 2, volume, volume, volume);

    long lengthsize = sizeof(long);
    long length = *(long *)(cstr - lengthsize);
	printf("    (%ld Byte    H:0x%016lx  D:%032ld  Chars.length = %ld),\n", lengthsize, length, length, length);
    

	for (int i = 0; i < length; i ++) {
		printf(show, sizeof(char), cstr[i], cstr[i], cstr[i]);
		if (i != length - 1) {
			printf(",\n");
		} else {
			printf("\n");
		}
	}
	printf("]\n");
}

char * cstringcopy(char * cstr) {
	if (!cstringcheck(cstr)) { return NULL; }
	char * index = NULL;
	memcpy(index, cstr, cstringlength(cstr) + sizeof(long));
	return index - sizeof(long);
}

void cstringfree(char * cstr) {
	free(cstr - 2 * sizeof(long));
}

bool cstringcompare(char * cstr, char * data) {
	if (!cstringcheck(cstr)) { return false; }
	long ssize = cstringlength(cstr);
	long dsize = cstringlength(data);
	if (ssize != dsize) {
		return false;
	} else {
		for (int i = 0; i < ssize; i ++) {
			if (cstr[i] == data[i]) {
				continue;
			} else {
				return false;
			}
		}
		return true;
	}
}

void cstringexpansise(char * source, double multiply) {
	long size = cstringlength(source) * multiply + sizeof(long);

}

/*
		012345
*/
bool cstringinsertcstring(char * source, long index, char data) {
	if (!cstringcheck(source)) { return false; }

	// long insert = -1;
	// long size = cstringlength(source);
	// if (index < 0 || index > ) {
	// 	return false;
	// } 

	return true;
}

bool cstringinsert(char * source, char data) {
	if (!cstringcheck(source)) {
		return false;
	}
	return true;
}

#endif