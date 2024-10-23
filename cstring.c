#ifndef __CSTRING_C__
#define __CSTRING_C__

#include <_types/_uint64_t.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cstring.h"
#include <stdarg.h>
#include <sys/_types/_va_list.h>

static bool cstringremove0(char * cstr, char * data);
static bool cstringremove1(char * cstr, char c);
static bool cstringremove2(char * cstr, long index);

static bool cstringcheck(char * cstr) {
	return cstr == NULL ? false : true;
}

long basesize(void) {
	return sizeof(long);
}

static void setcstringvolume(char * cstr, size_t value) {
	*(size_t *)(cstr - 2 * basesize()) = value;
}

size_t cstringvolume(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(size_t *)(cstr - 2 * basesize());
}

static void setcstringlength(char * cstr, size_t value) {
	*(long *)(cstr - basesize()) = value;
}

size_t cstringlength(char * cstr) {
	if (!cstringcheck(cstr)) { return -1; }
    return *(size_t *)(cstr - basesize());
}

char * cstringinit(char * str, bool ctl) {
    long vstep = basesize();
	long lstep = basesize();
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
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Chars.volume = %ld),\n", basesize(), volume, volume, volume);

    long length = cstringlength(cstr);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Chars.length = %ld)", basesize(), length, length, length);
	
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
	memcpy(index, cstr, cstringlength(cstr) + basesize());
	return index - basesize();
}

void cstringfree(char * cstr) {
	free(cstr - 2 * basesize());
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

void cstringtelescope(char ** pcstr, bool ctl, size_t m) {
	if (!cstringcheck(*pcstr)) { return; }
	long volume = cstringvolume(* pcstr);
	long length = cstringlength(* pcstr);
	
	volume = ctl == true ? volume * m : volume / m;

	if (volume < length) {
		printf("WARNNING: cstring.volume(%ld) < cstring.length(%ld), operation will lose information.\n", volume, length);
	}

	if (volume <= 1) { return; }

	char * space = malloc(2 * basesize() + volume);
	memcpy(space, *pcstr, 2 * basesize() + volume);
	printf("cstring: (%p) -> (%p)\n", * pcstr, space);
	free(*pcstr - 2 * basesize());
	* pcstr = space;
	*(long *)(* pcstr - 2 * basesize()) = volume;
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
	else if (index < length + 1) { ({}); }
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

bool cstringremove(char * cstr, search_t t, int (* cfg)(long idx), size_t ps, ...) {
	if (!cstringcheck(cstr)) { return false; }
	va_list list;
	va_start(list, ps);
	if (cstringlength(cstr) < 1 ) { return false; }

	switch (t) {
	case character: {
		for (long i = 0; i < ps; i ++) {
			int value = va_arg(list, int);
			cstringremove1(cstr, value);
		}
	} break;
	case position: {
		long source[ps];
		memset(source, -1, sizeof(long) * ps);
		long count = 0;
		long length = cstringlength(cstr);
		for (int i = 0; i < ps; i ++) {
			long result = cfg && cfg(i) == 8 ? va_arg(list, long) : va_arg(list, int);
			if (result < length && result >= 0) {
				bool flag = false;
				for (int j = 0; j < i; j ++) {
					if (source[j] != result) { continue;}
					else {flag = !flag; break; }
				}
				if (!flag) { source[count ++] = result; }
			}
		}
		long gap = count;    //定义增量
		while(gap > 1) {
			gap = gap / 2;    //将增量减小
			long j;
			for(j = 0; j < count - gap; j ++) {
				long end = j;
				long temp = source[end + gap];
				while(end >= 0) {
					// 从大往小排列
					if(source[end] < temp) {
						source[gap + end] = source[end];
						end -= gap;
					} else {
						break;
					}
				}
				source[end + gap] = temp;
			}
		}
		for (int i = 0; i < count; i ++) {
			cstringremove2(cstr, source[i]);
		}
	} break;
	case cstring: {
		for (long i = 0; i < ps; i ++) {
			long value = va_arg(list, long);
			cstringremove0(cstr, (char *)value);
		}
	} break;
	}
	va_end(list);
	return true;
}

static bool cstringremove0(char * cstr, char * data) {
	if (!cstringcheck(cstr)) { return false; }
	long length = cstringlength(cstr);
	long size = cstringlength(data); 
	if (length <= 0 || size <= 0 || size > length) { return - 1; }
	int indexes[length / size];
	memset(indexes, -1, length / size * sizeof(int));
	int index = 0, count = 0;
	int i = 0, j = 0;
	while (i < length && j < size) {
		if (cstr[i] == data[j]) {
			if (j == size - 1) {
				indexes[index] = i; ++ index; ++ count;
				i -= (j - 1); j = 0;
			} else {
				++ i; ++ j;
			}
		} else {
			i -= (j - 1); j = 0;
		}
	}
	/*
		123211212
		12   1212
		  321
		123
		   211212
	*/
	for (int i = count - 1; i >= 0; i --) {
		printf("%ld--%d--%ld\n", indexes[i] - size + 1, indexes[i] + 1, length - indexes[i]);
		memmove(cstr + indexes[i] - size + 1, cstr + indexes[i] + 1, length - indexes[i]);
	}
	setcstringlength(cstr, length - count * size);
	return true;
}

static bool cstringremove1(char * cstr, char c) {
	if (!cstringcheck(cstr)) { return false; }

	long length = cstringlength(cstr);
	long count = 0;
	for (int i = 0; i < length; i ++) {
		if (c == cstr[i]) {
			++ count;
		}
	}
	long indexes[count];
		// 为了节省空间,所以采用了牺牲运行时间的方法处理
	({
		long index = 0;
		for (int i = 0; i < length; i ++) {
			if (c == cstr[i]) {
				indexes[index] = i;
				++ index;
			}
		}
	});

	for (int i = 0; i < count; i ++) {
		memmove(cstr + indexes[i] - i, cstr + indexes[i] + 1 - i, length - indexes[i] - 1 + i);
		memmove(cstr + length - 1, &c, 1);
	}
	setcstringlength(cstr, length - count);
	return true;
}

static bool cstringremove2(char * cstr, long index) {
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

long cstringsearch(char * cstr, search_t t, long * count, long times, ...) {
	if (!cstringcheck(cstr)) { return false; }

	long length = cstringlength(cstr);
	long index = -1;
	long total = 0;
	if (times < 0 || times > length) { return -1; }

	va_list list;
	va_start(list, times);

	switch (t) {
	case character: {
		char data = va_arg(list, int);
		for (int i = 0; i < length; i ++) {
			if (data == cstr[i]) {
				++ total;
				if (total == times) {
					index = i; break;
				} else {
					continue;
				}
			}
		}
		* count = total;
		va_end(list);
		return index;
	} break;
	case position: {
		int data = va_arg(list, int);
		return data;
	} break;
	case cstring: {
		char * data = (void *)va_arg(list, uint64_t);
		long size = cstringlength(data); 
		if (length <= 0 || size <= 0 || size > length) { return - 1; }

		uint64_t flag = va_arg(list, int) != 0 ? true : false;
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
					++ total == times ? index = i : ({});
					ctl && flag == true ? ({ ++ i; j = 0; }) : ({ i -= (j - 1); j = 0; });
				} else {
					++ i; ++ j;
				}
			} else {
				i -= (j - 1); j = 0;
			}
		}
		* count = total;
		va_end(list);
		return index;
	} break;
	}
}

bool cstringunique(char * cstr, bool flag) {
	if (!cstringcheck(cstr)) { return false; }
	long length = cstringlength(cstr);
	if (length <= 1) { return false; }

	// 为什么是256：因为只要是字符串，ASCII值都在0~255之间,标准C,暂不支持多语言字符集
    char buffer[256];
	char delete[256];

	memset(buffer, false, sizeof(buffer));
	memset(delete, false, sizeof(buffer));

    int i = 0, j = 0;
    while(i < length) {
        if(buffer[cstr[i]] == 0) {
			cstr[j] = cstr[i];
            buffer[cstr[i]] = 1;
            ++ j;
        } else {
			flag == true ? ({}) : ({
				if(delete[cstr[i]] == 0) {
					delete[cstr[i]] = 1;
					for (int k = 0; k < j; k ++) {
						if (cstr[k] == cstr[i]) {
							char c = cstr[i];
							memmove(cstr + k, cstr + k + 1, j - k - 1);
							cstr[i - 1] = c;
							--j; break;
						}
					}
				}
			});
		}
        ++ i;
    }
	setcstringlength(cstr, j);
	return true;
}

bool cstringchange(char * cstr, long pos, ...) {
	if (!cstringcheck(cstr)) { return false; }

	va_list list;
	va_start(list, pos);
	uint64_t result = va_arg(list, uint64_t);
	long length = cstringlength(cstr);
	char * data = NULL;
	if (0x00 <= result && result <= 0xff) {
		data = CHAR2CSTRING(data, result);
	} else {
		data = POINTER2CSTRING(data, (char *)result);
	}

	long loc = 0;
	long index = 0;
	long size = 0;
	if (pos < 0) {
		if (pos + cstringlength(data) <= 0) {
			return false;
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
			return false;
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
	return true;
}

char * cstringtoken(char * cstr, size_t times, ...) {
	va_list list;
	va_start(list, times);
	uint64_t result = va_arg(list, uint64_t);
	long count = 0;
	long index = cstringsearch(cstr, character, &count, times, result);
	if (index < 0) {
		va_end(list);
		return NULL;
	} else {
		char * p = cstringinit(NULL, false);
		size_t volume = cstringvolume(p);

		for (int i = 0; i < index; i ++) {
			p[i] = cstr[i];
		}
		va_end(list);
		return p;
	}
}

long cstringprefix() {
	return -1;
}

long cstringpresuffix() {
	return -1;
}

void cstringsort(char * cstr, int (* sort)(char c0, char c1)) {

}

#endif