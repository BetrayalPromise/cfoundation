#ifndef __CARRAY_C__
#define __CARRAY_C__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "carray.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cutils.h"
#include "macro.h"

void carraytelescope(void ** pca, bool ctl, long m);
static bool carrayinsert0(void * ca, long idx, long pc, ...);
static bool carrayinsert1(void * ca, long idx, long pc, ...);

static long basesize(void) {
	return sizeof(long);
}

static void setcarraytype(void * ca, ctype_t value) {
    if (ca == NULL) { return; }
	*(long *)(ca - 4 * basesize()) = value;
}

ctype_t carraytype(void * ca) {
	if (ca == NULL) { return -1; }
    return *(ctype_t *)(ca - 4 * basesize());
}

static void setcarraystep(void * ca, long value) {
    if (ca == NULL) { return; }
	*(long *)(ca - 3 * basesize()) = value;
}

long carraystep(void * ca) {
	if (ca == NULL) { return -1; }
    return *(long *)(ca - 3 * basesize());
}

static void setcarrayvolume(void * ca, long value) {
    if (ca == NULL) { return; }
	*(long *)(ca - 2 * basesize()) = value;
}

long carrayvolume(void * ca) {
	if (ca == NULL) { return -1; }
    return *(long *)(ca - 2 * basesize());
}

static void setcarraylength(void * ca, long value) {
    if (ca == NULL) { return; }
	*(long *)(ca - 1 * basesize()) = value;
}

long carraylength(void * ca) {
	if (ca == NULL) { return -1; }
    return *(long *)(ca - 1 * basesize());
}

void * carrayinit(void * src, ctype_t type, long length) {
    if (!src || length < 0) { return NULL; }
    long step = 0;
    switch (type) {
    case cschar:  step = sizeof(char); break;
    case cuchar:  step = sizeof(unsigned char); break;
    case csshort: step = sizeof(short); break;
    case cushort: step = sizeof(unsigned short); break;
    case csint:   step = sizeof(int); break;
    case cuint:   step = sizeof(unsigned int); break;
    case cfloat:  step = sizeof(float); break;
    case cslong:  step = sizeof(long); break;
    case culong:  step = sizeof(unsigned long); break;
    case cdouble: step = sizeof(double); break;
    }
    long base = 4 * basesize();
    long volume = 32;
    while (volume <= length * step) {
		volume *= 2;
	}
    void * space = malloc(base + volume);
    void * ca = space + base;
    switch (type) {
    case cschar: case cuchar: case csshort: case cushort: case csint: case cuint: case cslong: case culong: {
        memcpy(ca, src, step * length);
    } break;
    case cfloat: {
        float * sf = src; float * tf = ca;
        for (int i = 0; i < length; i ++) { float temp = sf[i]; tf[i] = temp; }
    } break;
    case cdouble: {
        double * sd = src; double * td = ca;
        for (int i = 0; i < length; i ++) { double temp = sd[i]; td[i] = temp; }
    } break;
    }
    setcarraytype(ca, type);
    setcarraystep(ca, step);
	setcarraylength(ca, length);
	setcarrayvolume(ca, volume);
    return ca;
}

void carrayfree(void * ca) {
    if (!ca) { return; }
    free(ca - 0x20);
    ca = NULL;
}

void carraydescribe(void * ca) {
	if (!ca) { return; }
    printf("\n[type(8 Byte)|step(8 Bytpe)|volume(8 Byte)|length(8 Byte)|data...]: (%p)\n[\n", ca);
    ctype_t type = carraytype(ca);
    char * info = NULL;
    switch (type) {
    case cschar:  info = "char"; break;
    case cuchar:  info = "uchar"; break;
    case csshort: info = "short"; break;
    case cushort: info = "ushort"; break;
    case csint:   info = "int"; break;
    case cuint:   info = "uint"; break;
    case cfloat:  info = "float"; break;
    case cslong:  info = "long"; break;
    case culong:  info = "ulong"; break;
    case cdouble: info = "double"; break;
    }

    printf("    (%ld Byte  HEX:0x%016x  DEC:%032u  Array.type = %s),\n", basesize(), type, type, info);

    long step = carraystep(ca);
	printf("    (%ld Byte  HEX:0x%016lx  DEC:%032ld  Array.step = %ld),\n", basesize(), step, step, step);

    long volume = carrayvolume(ca);
	printf("    (%ld Byte  HEX:0x%016lx  DEC:%032ld  Array.volume = %ld),\n", basesize(), volume, volume, volume);

    long length = carraylength(ca);
	printf("    (%ld Byte  HEX:0x%016lx  DEC:%032ld  Array.length = %ld),", basesize(), length, length, length);

	printf("\n");
	for (int i = 0; i < length; i ++) {
        switch (type) {
        case cschar:   printf("    (%d  BIN:", ((char *)ca)[i]); BIT_DISPLAY(char, ((char *)ca)[i]); break;
        case cuchar:  printf("    (%d  BIN:", ((unsigned char *)ca)[i]); BIT_DISPLAY(unsigned char, ((unsigned char *)ca)[i]); break;
        case csshort:  printf("    (%d  BIN:", ((short *)ca)[i]); BIT_DISPLAY(short, ((short *)ca)[i]); break;
        case cushort: printf("    (%d  BIN:", ((unsigned short *)ca)[i]); BIT_DISPLAY(unsigned short, ((unsigned short *)ca)[i]); break;
        case csint:    printf("    (%d  BIN:", ((int *)ca)[i]); BIT_DISPLAY(int, ((int *)ca)[i]); break;
        case cuint:   printf("    (%d  BIN:", ((unsigned int *)ca)[i]); BIT_DISPLAY(unsigned int, ((unsigned int *)ca)[i]); break;
        case cfloat:  printf("    (%f  BIN:", ((float *)ca)[i]); BIT_DISPLAY(float, ((float *)ca)[i]); break;
        case cslong:   printf("    (%ld  BIN:", ((long *)ca)[i]); BIT_DISPLAY(long, ((long *)ca)[i]); break;
        case culong:  printf("    (%ld  BIN:", ((unsigned long *)ca)[i]); BIT_DISPLAY(unsigned long, ((unsigned long *)ca)[i]); break;
        case cdouble: printf("    (%lf  BIN:", ((double *)ca)[i]); BIT_DISPLAY(double, ((double *)ca)[i]); break;
        }
		printf("),\n");
	}
	printf("]\n\n");
}

bool carrayinsert(void * ca, sc_t t, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);
    switch (t) {
    case scsin: {
	    long length  = carraylength(ca);
	    long volume  = carrayvolume(ca);
        ctype_t type = carraytype(ca);
        long step    = carraystep(ca);
        while (length * step + pc * step  > volume) {
		    carraytelescope(&ca, true, 2);
		    volume = carrayvolume(ca);
	    }
        if (idx < 0) { idx = 0; } else if (idx < length + 1) { ; } else { idx = length; }
        memmove(ca + (idx + pc) * step, ca + idx * step, (length - idx) * step);
        switch (type) {
        case cschar: case cuchar: case csshort: case cushort: case csint: case cuint: {
            int temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, int); }
            for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
        } break;
        case cslong: case culong: {
            long temp[pc]; 
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, long); }
            for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
        } break;
        case cfloat: { // 防止出现整形数据按照整形存储
            double temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
            for (int i = 0; i < pc; i ++) { float value = (float)temp[i]; ((float *)ca)[i + idx] = value; }
        } break;
        case cdouble: { // 防止出现整形数据按照整形存储
            double temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
            for (int i = 0; i < pc; i ++) { double value = (double)temp[i]; ((double *)ca)[i + idx] = value; }
        } break;
        }
        setcarraylength(ca, length + pc);
        return true;
    } break;
    case scdup: {
        void * temp[pc];
        for (int i = 0; i < pc; i ++) {
            temp[i] = (void *)va_arg(list, unsigned long);
        }
        for (int i = pc - 1; i >= 0; i --) {
            carrayinsert1(ca, idx, 1, temp[i]);
        }
        va_end(list);
        return false; 
    } break;
    }
}

bool carraysearch(void * ca, sc_t t, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);
    long length  = carraylength(ca);
    long volume  = carrayvolume(ca);
    ctype_t type = carraytype(ca);
    long step    = carraystep(ca);
    switch (t) {
    case scsin: {
        while (length * step + pc * step  > volume) {
		    carraytelescope(&ca, true, 2);
		    volume = carrayvolume(ca);
	    }
        if (idx < 0) { idx = 0; } else if (idx < length + 1) { ; } else { idx = length; }
        memmove(ca + (idx + pc) * step, ca + idx * step, (length - idx) * step);
        switch (type) {
        case cschar: case cuchar: case csshort: case cushort: case csint: case cuint: {
            int temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, int); }
            for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
        } break;
        case cslong: case culong: {
            long temp[pc]; 
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, long); }
            for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
        } break;
        case cfloat: { // 防止出现整形数据按照整形存储
            double temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
            for (int i = 0; i < pc; i ++) { float value = (float)temp[i]; ((float *)ca)[i + idx] = value; }
        } break;
        case cdouble: { // 防止出现整形数据按照整形存储
            double temp[pc];
            for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
            for (int i = 0; i < pc; i ++) { double value = (double)temp[i]; ((double *)ca)[i + idx] = value; }
        } break;
        }
        setcarraylength(ca, length + pc);
        return true;
    } break;
    case scdup: {
        void * temp[pc];
        for (int i = 0; i < pc; i ++) {
            temp[i] = (void *)va_arg(list, unsigned long);
        }
        for (int i = pc - 1; i >= 0; i --) {
            carrayinsert1(ca, idx, 1, temp[i]);
        }
        va_end(list);
        return false; 
    } break;
    }
}

static bool carrayinsert0(void * ca, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);

	long length  = carraylength(ca);
	long volume  = carrayvolume(ca);
    ctype_t type = carraytype(ca);
    long step    = carraystep(ca);

    while (length * step + pc * step  > volume) {
		carraytelescope(&ca, true, 2);
		volume = carrayvolume(ca);
	}

    if (idx < 0) { idx = 0; } else if (idx < length + 1) { ; } else { idx = length; }

    memmove(ca + (idx + pc) * step, ca + idx * step, (length - idx) * step);

    switch (type) {
    case cschar: case cuchar: case csshort: case cushort: case csint: case cuint: {
        int temp[pc];
        for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, int); }
        for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
    } break;
    case cslong: case culong: {
        long temp[pc]; 
        for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, long); }
        for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
    } break;
    case cfloat: { // 防止出现整形数据按照整形存储
        double temp[pc];
        for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
        for (int i = 0; i < pc; i ++) { float value = (float)temp[i]; ((float *)ca)[i + idx] = value; }
    } break;
    case cdouble: { // 防止出现整形数据按照整形存储
        double temp[pc];
        for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, double); }
        for (int i = 0; i < pc; i ++) { double value = (double)temp[i]; ((double *)ca)[i + idx] = value; }
    } break;
    }
    setcarraylength(ca, length + pc);
	return true;
}

static bool carrayinsert1(void * ca, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);

	long length      = carraylength(ca);
	long volume      = carrayvolume(ca);
    ctype_t type = carraytype(ca);
    long step        = carraystep(ca);
    long total = 0;
    void * temp[pc];
    for (int i = 0; i < pc; i ++) {
        temp[i] = (void *)va_arg(list, unsigned long);
        total += carraylength(temp[i]);
    }
    while (length * step + total * step  > volume) {
		carraytelescope(&ca, true, 2);
		volume = carrayvolume(ca);
	}
    if (idx < 0) { idx = 0; } else if (idx < length + 1) { ; } else { idx = length; }

    for (int i = 0; i < pc; i ++) {
        if (carraytype(temp[i]) != type) {
            printf("information: type inconsistency!\n");
            return false;
        }
    }
    memmove(ca + (idx + total) * step, ca + idx * step, (length - idx) * step);
    void * start = ca + idx * step;
    for (int i = 0; i < pc; i ++) {
        long itemlength = carraylength(temp[i]);
        memcpy(start, temp[i], itemlength * step);
        start += itemlength * step;
    }
    setcarraylength(ca, length + total);
    va_end(list);
	return true;
}

void carraytelescope(void ** pca, bool ctl, long m) {
	if (!(*pca)) { return; }
	long volume = carrayvolume(* pca);
	long length = carraylength(* pca);
	
	volume = ctl == true ? volume * m : volume / m;

	if (volume < length) { printf("WARNNING: carray.volume(%ld) < carray.length(%ld), operation will lose information.\n", volume, length); }
	if (volume <= 1) { return; }

	char * space = malloc(4 * basesize() + volume);
	memcpy(space, *pca, 4 * basesize() + volume);
	printf("carray: (%p) -> (%p)\n", * pca, space);
	free(*pca - 4 * basesize());
	* pca = space + 4 * basesize();
	*(long *)(* pca - 2 * basesize()) = volume;
}

bool carrayremove(void * ca, rm_t t, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);
    long length  = carraylength(ca);
    long volume  = carrayvolume(ca);
    ctype_t type = carraytype(ca);
    long step    = carraystep(ca);
    switch (t) {
    case rmsin: {
        return true;
    } break;
    case rmdup: {
        void * temp[pc];
        for (int i = 0; i < pc; i ++) {
            temp[i] = (void *)va_arg(list, unsigned long);
        }
        for (int i = pc - 1; i >= 0; i --) {
            carrayinsert1(ca, idx, 1, temp[i]);
        }
        va_end(list);
        return false; 
    } break;
    case rmidx: {
        int temp[pc];
        for (int i = 0; i < pc; i ++) {
            temp[i] = va_arg(list, int);
        }
        int count = carrayunique(ca, csint, pc);
        for (int i = 0; i < count; i ++) {
            
        }
        return true;
    } break;
    }
}

// static bool carrayremove0(char * cstr, char * data) {
// 	if (!cstr) { return false; }
// 	long length = carraylength(cstr);
// 	long size = carraylength(data); 
// 	if (length <= 0 || size <= 0 || size > length) { return - 1; }
// 	int idxes[length / size];
// 	memset(idxes, -1, length / size * sizeof(int));
// 	int idx = 0, count = 0;
// 	int i = 0, j = 0;
// 	while (i < length && j < size) {
// 		if (cstr[i] == data[j]) {
// 			if (j == size - 1) {
// 				idxes[idx] = i; ++ idx; ++ count;
// 				i -= (j - 1); j = 0;
// 			} else {
// 				++ i; ++ j;
// 			}
// 		} else {
// 			i -= (j - 1); j = 0;
// 		}
// 	}
// 	for (int i = count - 1; i >= 0; i --) {
// 		memmove(cstr + idxes[i] - size + 1, cstr + idxes[i] + 1, length - idxes[i]);
// 	}
// 	setcarraylength(cstr, length - count * size);
// 	return true;
// }

// static bool carrayremove1(char * cstr, char c) {
// 	if (!cstr) { return false; }
// 	long length = carraylength(cstr);
// 	long count = 0;
// 	for (int i = 0; i < length; i ++) {
// 		if (c == cstr[i]) {
// 			++ count;
// 		}
// 	}
// 	long idxes[count];
// 	// 为了节省空间,所以采用了牺牲运行时间的方法处理
// 	({
// 		long idx = 0;
// 		for (int i = 0; i < length; i ++) {
// 			if (c == cstr[i]) {
// 				idxes[idx] = i;
// 				++ idx;
// 			}
// 		}
// 	});

// 	for (int i = 0; i < count; i ++) {
// 		memmove(cstr + idxes[i] - i, cstr + idxes[i] + 1 - i, length - idxes[i] - 1 + i);
// 		memmove(cstr + length - 1, &c, 1);
// 	}
// 	setcarraylength(cstr, length - count);
// 	return true;
// }

// static bool carrayremove2(void * ca, long idx) {
// 	if (!ca) { return false; }
// 	long length = carraylength(ca);
// 	if (idx > length - 1 || idx < 0) {
// 		return false;
// 	} else {
// 		memmove(ca + idx, ca + idx + 1, length - idx - 1);
// 		setcarraylength(ca, length - 1);
// 		return true;
// 	}
// }

void showcolor() {
	printf("\033[30m"); printf("\033[0m\r\n");
    printf("\033[31m"); printf("\033[0m\r\n");
    printf("\033[32m"); printf("\033[0m\r\n");
    printf("\033[33m"); printf("\033[0m\r\n");
    printf("\033[34m"); printf("\033[0m\r\n");
    printf("\033[35m"); printf("\033[0m\r\n");	
    printf("\033[36m"); printf("\033[0m\r\n");
    printf("\033[37m"); printf("\033[0m\r\n");	
    printf("\033[40m"); printf("\033[0m\r\n");
    printf("\033[41m"); printf("\033[0m\r\n");
    printf("\033[42m"); printf("\033[0m\r\n");
    printf("\033[43m"); printf("\033[0m\r\n");
    printf("\033[44m"); printf("\033[0m\r\n");
    printf("\033[45m"); printf("\033[0m\r\n");	
    printf("\033[46m"); printf("\033[0m\r\n");
    printf("\033[47m"); printf("\033[0m\r\n");	
}
 
void ASCII(ISO_IEC_646_t std, unsigned short flag) {
	int size = std == C89 ? 128 : 256;
	char * show = NULL;
	switch (flag) {
	case 0b111: show = "HEX:0x%02x  DEC:%03d  C:%c"; break;
	case 0b110: show = "HEX:0x%02x  DEC:%03d)"; break;
	case 0b101: show = "HEX:0x%02x  C:%c"; break;
	case 0b011: show = "DEC:%03d  C:%c)"; break;
	case 0b100: show = "HEX:0x%02x)"; break;
	case 0b010: show = "DEC:%03d)"; break;
	case 0b001: show = "C:%c)"; break;
	default:    show = "HEX:0x%02x  DEC:%03d  C:%c)"; break;
	}
	printf("ASCII STANDARDEC: %s\n", std == C89 ? "ISO/IEC 646:1991" : "ISO/IEC 646:1999");
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
    printf("[double].size = %lu Bype\n", sizeof(long double));

	printf("[void *].size = %lu Bype\n", sizeof(void *));
	printf("[char *].size = %lu Bype\n", sizeof(char *));
	printf("[short *].size = %lu Bype\n", sizeof(short *));
	printf("[int *].size = %lu Bype\n", sizeof(int *));
	printf("[long *].size = %lu Bype\n", sizeof(long *));
	printf("[long long *].size = %lu Bype\n", sizeof(long long *));
	printf("[float *].size = %lu Bype\n", sizeof(float *));
	printf("[double *].size = %lu Bype\n", sizeof(double *));
    printf("[long double *].size = %lu Bype\n", sizeof(long double *));
}

void carrayswap(void * n1, void * n2, int width) {
	char buf[width];
	memcpy(buf, n1, width);
	memcpy(n1, n2, width);
	memcpy(n2, buf, width);
}

int carraytypebyte(ctype_t t) {
	switch (t) {
	case cschar: case cuchar:
		return sizeof(char);
	case csshort: case cushort:
		return sizeof(short);
	case csint: case cuint:
		return sizeof(int);
	case cfloat:
		return sizeof(float);
	case cslong:case culong:
		return sizeof(long);
	case cdouble:
		return sizeof(double);
	}
}

long carrayunique(void * array, ctype_t t, long length) {
#if !defined (HANDLER)
    #define HANDLER(type, name)\
        type * src = name;\
        long count = 0;\
        for (int i = 0; i < length - 1; i ++) {\
            if (*(src + i) != *(src + i + 1)) { src[count] = src[i]; count ++; }\
        }\
        src[count] = src[length - 1];\
        return ++ count
#else
    #warning "information: duplicate define macro 'HANDLER'
#endif
    int width = carraytypebyte(t);
    carrayclassify(array, t, length, false);
    switch (t) {
    case cschar:   { HANDLER(char, array); } break;
    case cuchar:   { HANDLER(unsigned char, array); } break;
    case csshort:  { HANDLER(short, array); } break;
    case cushort:  { HANDLER(unsigned short, array); } break;
    case csint:    { HANDLER(int, array); } break;
    case cuint:    { HANDLER(unsigned int, array); } break;
    case cfloat:   { HANDLER(float, array); } break;
    case cslong:   { HANDLER(long, array); } break;
    case culong:   { HANDLER(unsigned long, array); } break;
    case cdouble:  { HANDLER(double, array); } break;
    }
#undef HANDLER
}

bool carrayclassify(void * array, ctype_t t, long length, bool flag) {
    if (!array || length < 0) {
        return false;
    }
    int width = carraytypebyte(t);
#if !defined (HANDLER)
    #define HANDLER(type, name)\
        type * src = array;\
        for (int i = 0; i < length - 1; i ++) {\
            for(int j = i + 1; j < length; j ++) {\
                if (!flag) {\
                    if (*(src + i) > *(src + j)) { carrayswap(src + i, src + j, width); }\
                } else {\
                    if (*(src + i) < *(src + j)) { carrayswap(src + i, src + j, width); }\
                }\
            }\
        }
#else
    #warning "information: duplicate define macro 'HANDLER'
#endif
    switch (t) {
    case cschar: {
        HANDLER(char, array);
    } break;
    case cuchar: {
        HANDLER(unsigned char, array);
    } break;
    case csshort: {
        HANDLER(short, array);
    } break;
    case cushort: {
        HANDLER(unsigned short, array);
    } break;
    case csint: {
        HANDLER(int, array);
    } break;
    case cuint: {
        HANDLER(unsigned int, array);
    } break;
    case cfloat: {
        HANDLER(float, array);
    } break;
    case cslong: {
        HANDLER(long, array);
    } break;
    case culong: {
        HANDLER(unsigned long, array);
    } break;
    case cdouble: {
        HANDLER(double, array);
    } break;
    }
#undef HANDLER
    return true;
}

#endif