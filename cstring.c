#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <_types/_uint64_t.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cstring.h"
#include <stdarg.h>
#include <sys/_types/_va_list.h>

static bool cstringcheck(char * cstr) {
	return cstr == NULL ? false : true;
}

static long baseinformationsize(void) {
	return sizeof(long);
}

static void setcstringvolume(char * cstr, long value) {
	*(long *)(cstr - 2 * baseinformationsize()) = value;
}

long cstringvolume(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - 2 * baseinformationsize());
}

static void setcstringlength(char * cstr, long value) {
	*(long *)(cstr - baseinformationsize()) = value;
}

long cstringlength(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(long *)(cstr - baseinformationsize());
}

/*
	
*/
char * cstringinit(char * str, bool ctl) {
    long vstep = baseinformationsize();
	long lstep = baseinformationsize();
	long volume = 32;
	long length = 0;

	if (str == NULL) {
		length = 0;
	} else {
		length = ctl == true ? strlen(str) + 1 : strlen(str);
	}
	while (volume <= length) {
		volume *= 2;
	}
    char * space = malloc(vstep + lstep + volume);
    char * cstr = space + vstep + lstep;
	for (int i = 0; i < length; i ++) {
		cstr[i] = str[i];
	}
	setcstringlength(cstr, length);
	setcstringvolume(cstr, volume);
    return cstr;
}

void cstringdescribe(char * cstr, unsigned short flag) {
	if (!cstringcheck(cstr)) { return; }
    printf("\n[long|long|char...]: (%p)\n[\n", cstr);
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
	printf("]\n\n");
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

void cstringtelescope(char ** pcstr, bool ctl, long m) {
	if (!cstringcheck(*pcstr)) { return; }
	long volume = cstringvolume(* pcstr);
	long length = cstringlength(* pcstr);
	
	volume = ctl == true ? volume * m : volume / m;

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

		memmove(cstr + cstringlength(data), cstr, cstringlength(cstr) - index);
		memmove(cstr + index, data, cstringlength(data));
		setcstringlength(cstr, length + cstringlength(data));

		va_end(list);
		return true;
	}
}

bool cstringcatenate(char * cstr, ...) {
	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, cstr);

	long length = cstringlength(cstr);
	long volume = cstringvolume(cstr);

	uint64_t result = va_arg(list, uint64_t);
	if (0x00 <= result && result <= 0xff) {
		char data = result;
		while (length + 1 > volume) {
			cstringtelescope(&cstr, true, 2);
			volume = cstringvolume(cstr);
		}
		memmove(cstr + length, &data, 1);
		setcstringlength(cstr, length + 1);
		
		va_end(list);
		return true;
	} else {
		char * data = (void *)result;
		while (length + cstringlength(data) > volume) {
			cstringtelescope(&cstr, true, 2);
			volume = cstringvolume(cstr);
		}
		memmove(cstr + length, data, cstringlength(data));
		setcstringlength(cstr, length + cstringlength(data));
		va_end(list);
		return true;
	}
}

bool cstringclean(char * cstr, ...) {
	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, cstr);

	long length = cstringlength(cstr);
	long volume = cstringvolume(cstr);

	if (length < 1 ) { return false; }

	uint64_t result = va_arg(list, uint64_t);

	if (0x00 <= result && result <= 0xff) {
		char data = result;
		long count = 0;
		for (int i = 0; i < length; i ++) {
			if (data == cstr[i]) {
				++ count;
			}
		}
		long indexes[count];
		// 为了节省空间,所以采用了牺牲运行时间的方法处理
		({
			long index = 0;
			for (int i = 0; i < length; i ++) {
				if (data == cstr[i]) {
					indexes[index] = i;
					++ index;
				}
			}
		});

		long index = 0;
		for (int i = 0; i < count; i ++) {
			memmove(cstr + indexes[i] - index, cstr + indexes[i] + 1 - index, length - indexes[i] - 1 + index);
			memmove(cstr + length - 1, &data, 1);
			cstringdescribe(cstr, 0b001);
			 ++ index;
		}
	
		setcstringlength(cstr, length - count);
		va_end(list);
		return true;
	} else {
		char * data = (void *)result;
		long size = cstringlength(data);
		long temp = length;
		long i = cstringindex(cstr, 1, data, true);
		do {
			memmove(cstr, cstr + size, temp - size);
			setcstringlength(cstr, temp - size);
			temp -= size;
			i = cstringindex(cstr, 1, data, true);
		} while (i != -1);
		/*
			0000
			00
		*/

		va_end(list);
		return true;
	}
}

bool cstringremove(char * cstr, long index) {
	if (!cstringcheck(cstr)) { return false; }

	long length = cstringlength(cstr);

	if (index > length - 1 || index < 0) {
		return false;
	} else {
		memmove(cstr + index, cstr + index + 1, length - index - 1);
		setcstringlength(cstr, length - 1);
		return true;
	}
}

long cstringindex(char * cstr, long times, ...) {
	if (!cstringcheck(cstr)) { return false; }

	long length = cstringlength(cstr);
	long index = -1;
	long count = 0;

	if (times < 0 || times > length) { return -1; }

	va_list list;
	va_start(list, times);
	uint64_t result = va_arg(list, uint64_t);
	
	if (0x00 <= result && result <= 0xff) {
		char data = result;
		for (int i = 0; i < length; i ++) {
			if (data == cstr[i]) {
				++ count;
				if (count == times) {
					index = i; break;
				} else {
					continue;
				}
			}
		}
		va_end(list);
		return index;
	} else {
		char * data = (void *)result;
		long size = cstringlength(data); 
		if (length <=0 || size <= 0 || size > length) { return - 1; }

		uint64_t flag = va_arg(list, uint64_t) != 0 ? true : false;
		bool ctl = false;
		
		if (flag) {
			for (int i = 0; i < size - 1; i ++) {
				data[0] == data[i] ? ({ ctl = true; continue; }) : ({ ctl = false; break; });
			}	
		}

		int i = 0, j = 0;
		while (i < length && j < size) {
			if (cstr[i] == data[j]) {
				if (j == size - 1) {
					++ count == times ? index = i : ({});
					ctl && flag == true ? ({ ++ i; j = 0; }) : ({ i -= (j - 1); j = 0; });
				} else {
					++ i; ++ j;
				}
			} else {
				i -= (j - 1); j = 0;
			}
		}

		va_end(list);
		return index;
	}
}

long cstringindexcount(char * cstr, ...) {
	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, cstr);

	long length = cstringlength(cstr);
	long volume = cstringvolume(cstr);

	uint64_t result = va_arg(list, uint64_t);
	long count = 0;

	if (0x00 <= result && result <= 0xff) {
		char data = result;
		for (int i = 0; i < length; i ++) {
			if (data == cstr[i]) {
				++ count;
			}
		}
		va_end(list);
		return count;
	} else {
		char * data = (void *)result;
		long index = 0;
		long size = cstringlength(data); 
		int64_t flag = va_arg(list, uint64_t) != 0 ? true : false;
		bool ctl = false;
		
		if (flag) {
			for (int i = 0; i < size - 1; i ++) {
				data[0] == data[i] ? ({ ctl = true; continue; }) : ({ ctl = false; break; });
			}
		}

		int i = 0, j = 0;
		while (i < length && j < size) {
			if (cstr[i] == data[j]) {
				if (j == size - 1) {
					++ count;
					ctl && flag == true ? ({ ++ i; j = 0; }) : ({ i -= (j - 1); j = 0; });
				} else {
					++ i; ++ j;
				}
			} else {
				i -= (j - 1); j = 0;
			}
		}

		va_end(list);
		return count;
	}
}

void cstringunique(char * cstr) {
	if (!cstringcheck(cstr)) { return; }
	long length = cstringlength(cstr);
	if (length <= 1) { return; }

	long i, j, k;
 	for(i = 0; i < length; i ++) {
        for(j = i + 1; j < length; j ++) {
            if(cstr[i] == cstr[j]) {
                for(k = j; k < length - 1; k ++) { 
                	cstr[k] = cstr[k + 1];
                }
            	length--;
            	j--;
            }
        }
    }
	setcstringlength(cstr, length);
}

void cstringchange(char * cstr, long pos, ...) {
	if (!cstringcheck(cstr)) { return; }

	va_list list;
	va_start(list, pos);
	uint64_t result = va_arg(list, uint64_t);
	long length = cstringlength(cstr);
	char * data = NULL;
	if (0x00 <= result && result <= 0xff) {
		char str[1 + baseinformationsize() * 2];
		data = str + baseinformationsize() * 2;
		str[0] = result;
		setcstringlength(data, 1);
		setcstringvolume(data, 1);
	} else {
		data = (void *)result;
	}

	long loc = 0;
	long index = 0;
	long size = 0;
	if (pos < 0) {
		if (pos + cstringlength(data) <= 0) {
			return;
		} else {
			index = labs(pos);
			size = pos + cstringlength(data) < cstringlength(cstr) ? pos + cstringlength(data) : cstringlength(cstr);
			loc = 0;
		}
	} else if (pos == 0) {
		index = 0;
		size = cstringlength(cstr) > cstringlength(data) ? cstringlength(data) : cstringlength(cstr);
		loc = 0;
	} else {
		if (pos >= cstringlength(cstr)) {
			return;
		} else {
			index = 0;
			size = pos + cstringlength(data) < cstringlength(cstr) ? cstringlength(data) : cstringlength(cstr) - pos;
			loc = pos;
		}
	}
	long i = loc;
	long j = index;
	for (; i < size + loc; i ++) {
		cstr[i] = data[j];
		j ++;
	}
	va_end(list);
}

long cstringprefix() {
	return -1;
}

long cstringpresuffix() {
	return -1;
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