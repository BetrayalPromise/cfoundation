#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <_types/_uint64_t.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cstring.h"
#include <stdarg.h>
#include <sys/_types/_va_list.h>

bool cstringcheck(char * cstr) {
	return cstr == NULL ? false : true;
}

/*
	return "zzz"; "zzz" 字面量存储在静态区域里 不需要释放
*/
char * tocstring(char * str) {
    long volumestep = sizeof(long);
	long lengthstep = sizeof(long);

	long basesize = 32;
	long lengthsize = str != NULL ? sizeof(char) * strlen(str) + 1 : 0;

    long volumesize = basesize;
	while (volumesize <= lengthsize) {
		volumesize *= 2;
	}

    char * cstr = malloc(volumestep + lengthstep + volumesize);
    char * string = cstr + volumestep + lengthstep;

    *(long *)cstr = volumesize;
	*(long *)(cstr + volumestep) = lengthsize;

	if (str != NULL) {
	    for (int i = 0; i < strlen(str) + 1; i ++) {
        	string[i] = str[i];
    	}
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

void cstringdescribe(char * cstr, unsigned short flag) {
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
	printf("    (%ld Byte    H:0x%016lx  D:%032ld  Chars.length = %ld)", lengthsize, length, length, length);
	
	if (length != 0) {
		printf(",");
	}
	printf("\n");

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

void cstringtelescope(char ** pcstr, bool control, long multiply) {
	if (!cstringcheck(*pcstr)) { return; }

	long volume = cstringvolume(* pcstr);
	long length = cstringlength(* pcstr);
	if (control) {
		char * space = malloc(2 * sizeof(long) + volume * multiply);
		memcpy(space, *pcstr, 2 * sizeof(long) + volume * multiply);
		printf("cstring: (%p) -> (%p)\n", * pcstr, space);
		free(*pcstr - 2 * sizeof(long));
		* pcstr = space;
		*(long *)(* pcstr - 2 * sizeof(long)) = volume * multiply;
	} else {
		if (volume <= 1) { return; }

		if (volume / multiply >= length) {
			char * space = malloc(2 * sizeof(long) + volume / multiply);
			memcpy(space, *pcstr, 2 * sizeof(long) + volume / multiply);
			printf("cstring: (%p) -> (%p)\n", * pcstr, space);
			free(*pcstr - 2 * sizeof(long));
			* pcstr = space;
			*(long *)(* pcstr - 2 * sizeof(long)) = volume / multiply;
		} else {
			printf("WARNNING: cstring.length(%ld) > cstring.volume(%ld), \n", length, volume);
			return;
		}
	}
}

/*
		012345
*/

bool cstringinsert(char * cstr, long index, ...) {
	// printf("%p\n", cstr);
	// uint64_t rbp = 0x0;
    // __asm__ __volatile__("movq %%rbp, %0" : "=r"(rbp));
	// uint64_t rsp = 0x0;
    // __asm__ __volatile__("movq %%rsp, %0" : "=r"(rsp));

	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, index);

	// uint64_t rdi = 0x0;
    // __asm__ __volatile__("movq %%rdi, %0" : "=r"(rdi));
	// uint64_t rsi = 0x0;
    // __asm__ __volatile__("movq %%rsi, %0" : "=r"(rsi));
	// uint64_t rdx = 0x0;
    // __asm__ __volatile__("movq %%rdx, %0" : "=r"(rdx));
	// uint64_t rcx = 0x0;
    // __asm__ __volatile__("movq %%rcx, %0" : "=r"(rcx));
	// uint64_t r8 = 0x0;
    // __asm__ __volatile__("movq %%r8, %0" : "=r"(r8));
	// uint64_t r9 = 0x0;
    // __asm__ __volatile__("movq %%r9, %0" : "=r"(r9));

	uint64_t result = va_arg(list, uint64_t);
	uint64_t result0 = va_arg(list, uint64_t);

	if (0x00 <= result && result <= 0xff) {
		printf("%c\n", (char)result);
	} else {
		char * data = (void *)result;
		printf("%p\n", data);
		printf("%s\n", data);
	}
	va_end(list);

	return true;
}

void ASCII(ISO_IEC_646_t standard, unsigned short flag) {
	int size = standard == C89 ? 128 : 256;
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "H:0x%02x  D:%03d  C:%c"; break;
	case 0b110: show = "H:0x%02x  D:%03d)"; break;
	case 0b101: show = "H:0x%02x  C:%c"; break;
	case 0b011: show = "D:%03d  C:%c)"; break;
	case 0b100: show = "H:0x%02x)"; break;
	case 0b010: show = "D:%03d)"; break;
	case 0b001: show = "C:%c)"; break;
	default:    show = "H:0x%02x  D:%03d  C:%c)"; break;
	}
	printf("ASCII STANDARD: %s\n", standard == C89 ? "ISO/IEC 646:1991" : "ISO/IEC 646:1999");
	for (int i = 0; i < size; i ++) {
		printf(show, i, i, i);
		printf("\n");
	}
}

void typebytelength(void) {
	printf("[void].size = %lu Bype\n", sizeof(void));
	printf("[char].size = %lu Bype\n", sizeof(char));
	printf("[short].size = %lu Bype\n", sizeof(short));
	printf("[int].size = %lu Bype\n", sizeof(int));
	printf("[long].size = %lu Bype\n", sizeof(long));
	printf("[long long].size = %lu Bype\n", sizeof(long long));
	printf("[float].size = %lu Bype\n", sizeof(float));
	printf("[double].size = %lu Bype\n", sizeof(double));

	printf("[void *].size = %lu Bype\n", sizeof(void *));
	printf("[char *].size = %lu Bype\n", sizeof(char *));
	printf("[short *].size = %lu Bype\n", sizeof(short *));
	printf("[int *].size = %lu Bype\n", sizeof(int *));
	printf("[long *].size = %lu Bype\n", sizeof(long *));
	printf("[long long *].size = %lu Bype\n", sizeof(long long *));
	printf("[float *].size = %lu Bype\n", sizeof(float *));
	printf("[double *].size = %lu Bype\n", sizeof(double *));	
}

#endif