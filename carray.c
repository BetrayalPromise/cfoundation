#ifndef __CARRAY_C__
#define __CARRAY_C__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "carray.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void carraytelescope(void ** pcarray, bool ctl, size_t m);

static long basesize(void) {
	return sizeof(long);
}

static void setcarraytype(void * ca, ctype_t value) {
    if (ca == NULL) { return; }
	*(size_t *)(ca - 4 * basesize()) = value;
}

ctype_t carraytype(void * ca) {
	if (ca == NULL) { return -1; }
    return *(ctype_t *)(ca - 4 * basesize());
}

static void setcarraystep(void * ca, size_t value) {
    if (ca == NULL) { return; }
	*(size_t *)(ca - 3 * basesize()) = value;
}

size_t carraystep(void * ca) {
	if (ca == NULL) { return -1; }
    return *(size_t *)(ca - 3 * basesize());
}

static void setcarrayvolume(void * ca, size_t value) {
    if (ca == NULL) { return; }
	*(size_t *)(ca - 2 * basesize()) = value;
}

size_t carrayvolume(void * ca) {
	if (ca == NULL) { return -1; }
    return *(size_t *)(ca - 2 * basesize());
}

static void setcarraylength(void * ca, size_t value) {
    if (ca == NULL) { return; }
	*(long *)(ca - 1 * basesize()) = value;
}

size_t carraylength(void * ca) {
	if (ca == NULL) { return -1; }
    return *(size_t *)(ca - 1 * basesize());
}

void * carrayinit(void * src, size_t length, ctype_t type) {
    if (!src || length < 0) { return NULL; }
    size_t step = 0;
    switch (type) {
    case cchar:   step = sizeof(char); break;
    case cuchar:  step = sizeof(unsigned char); break;
    case cshort:  step = sizeof(short); break;
    case cushort: step = sizeof(unsigned short); break;
    case cint:    step = sizeof(int); break;
    case cuint:   step = sizeof(unsigned int); break;
    case cfloat:  step = sizeof(float); break;
    case clong:   step = sizeof(long); break;
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
    case cchar: case cuchar: case cshort: case cushort: case cint: case cuint: case clong: case culong: {
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
    case cchar:   info = "char"; break;
    case cuchar:  info = "uchar"; break;
    case cshort:  info = "short"; break;
    case cushort: info = "ushort"; break;
    case cint:    info = "int"; break;
    case cuint:   info = "uint"; break;
    case cfloat:  info = "float"; break;
    case clong:   info = "long"; break;
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
        case cchar:   printf("    (%d  BIN:", ((char *)ca)[i]); BIT_DISPLAY(char, ((char *)ca)[i]); break;
        case cuchar:  printf("    (%d  BIN:", ((unsigned char *)ca)[i]); BIT_DISPLAY(unsigned char, ((unsigned char *)ca)[i]); break;
        case cshort:  printf("    (%d  BIN:", ((short *)ca)[i]); BIT_DISPLAY(short, ((short *)ca)[i]); break;
        case cushort: printf("    (%d  BIN:", ((unsigned short *)ca)[i]); BIT_DISPLAY(unsigned short, ((unsigned short *)ca)[i]); break;
        case cint:    printf("    (%d  BIN:", ((int *)ca)[i]); BIT_DISPLAY(int, ((int *)ca)[i]); break;
        case cuint:   printf("    (%d  BIN:", ((unsigned int *)ca)[i]); BIT_DISPLAY(unsigned int, ((unsigned int *)ca)[i]); break;
        case cfloat:  printf("    (%f  BIN:", ((float *)ca)[i]); BIT_DISPLAY(float, ((float *)ca)[i]); break;
        case clong:   printf("    (%ld  BIN:", ((long *)ca)[i]); BIT_DISPLAY(long, ((long *)ca)[i]); break;
        case culong:  printf("    (%ld  BIN:", ((unsigned long *)ca)[i]); BIT_DISPLAY(unsigned long, ((unsigned long *)ca)[i]); break;
        case cdouble: printf("    (%lf  BIN:", ((double *)ca)[i]); BIT_DISPLAY(double, ((double *)ca)[i]); break;
        }
		printf("),\n");
	}
	printf("]\n\n");
}

bool carrayinsert(void * ca, long idx, long pc, ...) {
    return false;
}

bool carrayinsert0(void * ca, long idx, long pc, ...) {
    if (!ca) { return false; }
    va_list list;
	va_start(list, pc);

	long length      = carraylength(ca);
	long volume      = carrayvolume(ca);
    ctype_t type = carraytype(ca);
    long step        = carraystep(ca);

    while (length * step + pc * step  > volume) {
		carraytelescope(&ca, true, 2);
		volume = carrayvolume(ca);
	}

    if (idx < 0) { idx = 0; } else if (idx < length + 1) { ; } else { idx = length; }

    memmove(ca + (idx + pc) * step, ca + idx * step, (length - idx) * step);

    switch (type) {
    case cchar: case cuchar: case cshort: case cushort: case cint: case cuint: {
        int temp[pc];
        for (int i = 0; i < pc; i ++) { temp[i] = va_arg(list, int); }
        for (int i = 0; i < pc; i ++) { memcpy(ca + idx + i * step, temp + i, step); }
    } break;
    case clong: case culong: {
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

bool carrayinsert1(void * ca, long idx, long pc, ...) {
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

void carraytelescope(void ** pcarray, bool ctl, size_t m) {
	if (!(*pcarray)) { return; }
	long volume = carrayvolume(* pcarray);
	long length = carraylength(* pcarray);
	
	volume = ctl == true ? volume * m : volume / m;

	if (volume < length) { printf("WARNNING: caing.volume(%ld) < caing.length(%ld), operation will lose information.\n", volume, length); }
	if (volume <= 1) { return; }

	char * space = malloc(4 * basesize() + volume);
	memcpy(space, *pcarray, 4 * basesize() + volume);
	printf("caing: (%p) -> (%p)\n", * pcarray, space);
	free(*pcarray - 4 * basesize());
	* pcarray = space + 4 * basesize();
	*(long *)(* pcarray - 2 * basesize()) = volume;
} 

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
 
void ASCII(ISO_IEC_646_t standard, unsigned short flag) {
	int size = standard == C89 ? 128 : 256;
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
	printf("ASCII STANDARDEC: %s\n", standard == C89 ? "ISO/IEC 646:1991" : "ISO/IEC 646:1999");
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

void swap(void * n1, void * n2, int width) {
	char buffer[width];
	memcpy(buffer, n1, width);
	memcpy(n1, n2, width);
	memcpy(n2, buffer, width);
}

int typebyte(ctype_t t) {
	switch (t) {
	case cchar: case cuchar:
		return sizeof(char);
	case cshort: case cushort:
		return sizeof(short);
	case cint: case cuint:
		return sizeof(int);
	case cfloat:
		return sizeof(float);
	case clong:case culong:
		return sizeof(long);
	case cdouble:
		return sizeof(double);
	}
}

int unique(void * idxes, ctype_t t, int length) {
    unsigned int width = typebyte(t);
    switch (t) {
    case cchar: {
        char * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cuchar: {
        unsigned char * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cshort: {
        short * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cushort: {
        unsigned short * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cint: {
        int * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cuint: {
        unsigned int * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cfloat: {
        float * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case clong: {
        long * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case culong: {
        unsigned long * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    case cdouble: {
        double * src = idxes;
        for (int i = 0; i < length - 1; i ++) {
            for(int j = i + 1; j < length; j ++){
                if (*(src + i) > *(src + j)) {
				    swap(src + i, src + j, width);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < length - 1; i ++) {
            if (*(src + i) != *(src + i + 1)) {
                src[count] = src[i];
                count ++;
            }
        }
        src[count] = src[length - 1];
        count ++;
        return count;
    } break;
    }
}

#endif