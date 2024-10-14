#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <_types/_uint64_t.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cchars.h"
#include "cstring.h"
#include <stdarg.h>
#include <sys/_types/_va_list.h>

static bool cstringcheck(char * cstr) {
	return cstr == NULL ? false : true;
}

static long baseinformationsize(void) {
	return sizeof(long);
}

static long basevolumesize(void) {
	return 32;
}

void setcstringvolume(char * cstr, long value) {
	*(long *)(cstr - 2 * baseinformationsize()) = value;
}

long cstringvolume(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - 2 * baseinformationsize());
}

void setcstringlength(char * cstr, long value) {
	*(long *)(cstr - baseinformationsize()) = value;
}

long cstringlength(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - baseinformationsize());
}

/*
	return "zzz"; "zzz" 字面量存储在静态区域里 不需要释放
*/
char * cstringinit(char * str) {
    long volumestep = baseinformationsize();
	long lengthstep = baseinformationsize();

	long volumesize = basevolumesize();
	long lengthsize = str != NULL ? sizeof(char) * strlen(str) + 1 : 0;

	while (volumesize <= lengthsize) {
		volumesize *= 2;
	}

    char * space = malloc(volumestep + lengthstep + volumesize);
    char * string = space + volumestep + lengthstep;

	if (str != NULL) {
	    for (int i = 0; i < strlen(str) + 1; i ++) {
        	string[i] = str[i];
    	}
	}
	setcstringlength(string, lengthsize);
	setcstringvolume(string, volumesize);
    return string;
}

void cstringdescribe(char * cstr, unsigned short flag) {
	if (!cstringcheck(cstr)) { return; }
    printf("[long|long|char...]: (%p)\n[\n", cstr);
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "    (%ld Byte  H:0x%02x  D:%03d  C:%c)"; break;
	case 0b110: show = "    (%ld Byte  H:0x%02x  D:%03d)"; break;
	case 0b101: show = "    (%ld Byte  H:0x%02x  C:%c)"; break;
	case 0b011: show = "    (%ld Byte  D:%03d  C:%c)"; break;
	case 0b100: show = "    (%ld Byte  H:0x%02x)"; break;
	case 0b010: show = "    (%ld Byte  D:%03d)"; break;
	case 0b001: show = "    (%ld Byte  C:%c)"; break;
	default:    show = "    (%ld Byte  H:0x%02x  D:%03d  C:%c)"; break;
	}

    long volume = cstringvolume(cstr);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Chars.volume = %ld),\n", baseinformationsize(), volume, volume, volume);

    long length = cstringlength(cstr);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Chars.length = %ld)", baseinformationsize(), length, length, length);
	
	if (length != 0) {
		printf(",");
	}
	printf("\n");

	long index = length <= volume ? length : volume;

	for (int i = 0; i < index; i ++) {
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
	memcpy(index, cstr, cstringlength(cstr) + baseinformationsize());
	return index - baseinformationsize();
}

void cstringfree(char * cstr) {
	free(cstr - 2 * baseinformationsize());
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
	
	volume = control == true ? volume * multiply : volume / multiply;

	if (volume < length) {
		printf("WARNNING: cstring.volume(%ld) < cstring.length(%ld), operation will lose information.\n", volume, length);
	}

	if (volume <= 1) { return; }

	char * space = malloc(2 * baseinformationsize() + volume);
	memcpy(space, *pcstr, 2 * baseinformationsize() + volume);
	printf("cstring: (%p) -> (%p)\n", * pcstr, space);
	free(*pcstr - 2 * baseinformationsize());
	* pcstr = space;
	*(long *)(* pcstr - 2 * baseinformationsize()) = volume;
}

bool cstringinsert(char * cstr, long index, ...) {
	uint64_t rdi = 0x0;
    __asm__ __volatile__("movq %%rdi, %%rax;\n\t" : "=a"(rdi));
	uint64_t rsi = 0x0;
    __asm__ __volatile__("movq %%rsi, %%rax;\n\t" : "=a"(rsi));
	uint64_t rdx = 0x0;
    __asm__ __volatile__("movq %%rdx, %%rax;\n\t" : "=a"(rdx));
	uint64_t rcx = 0x0;
    __asm__ __volatile__("movq %%rcx, %%rax;\n\t" : "=a"(rcx));
	uint64_t r8 = 0x0;
    __asm__ __volatile__("movq %%r8, %%rax;\n\t" : "=a"(r8));
	uint64_t r9 = 0x0;
    __asm__ __volatile__("movq %%r9, %%rax;\n\t" : "=a"(r9));

	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, index);

	uint64_t result = va_arg(list, uint64_t);

	long length = cstringlength(cstr);
	long volume = cstringvolume(cstr);

	if (index < 0) { index = 0; }
	else if (index < length + 1) { ; }
	else { index = length; }
	
	if (0x00 <= result && result <= 0xff) {
		char data = result;
		while (length + 1 > volume) {
			cstringtelescope(&cstr, true, 2);
			volume = cstringvolume(cstr);
		}

		memmove(cstr + index, cstr, length - index);
		memmove(cstr + index, &data, 1);
		setcstringlength(cstr, length + 1);

		va_end(list);
		return true;
	} else {
		char * data = (void *)result;
		while (length + cstringlength(data) > volume) {
			cstringtelescope(&cstr, true, 2);
			volume = cstringvolume(cstr);
		}

		if (length <= 0) {
			for (int i = 0; i < cstringlength(data); i ++) {
				cstr[i] = data[i];
			}
			setcstringlength(cstr, length + cstringlength(data));
			va_end(list);
			return true;
		}

		memmove(cstr + cstringlength(data) , cstr, cstringlength(cstr) - index);
		memmove(cstr + index, data, cstringlength(data));
		setcstringlength(cstr, length + cstringlength(data));
		va_end(list);
		return true;
	}
}

// long * cstringsearch(char * cstr, ...) {

// }

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