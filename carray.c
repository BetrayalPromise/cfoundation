#ifndef __carray_C__
#define __carray_C__

#include <stddef.h>
#include <stdio.h>
#include "carray.h"
#include <math.h>
#include <stdlib.h>

static long basesize(void) {
	return sizeof(long);
}

static void setcarraytype(void * cs, cbasetype_t value) {
    if (cs == NULL) { return; }
	*(size_t *)(cs - 4 * basesize()) = value;
}

cbasetype_t carraytype(void * cs) {
	if (cs == NULL) { return -1; }
    return *(cbasetype_t *)(cs - 4 * basesize());
}

static void setcarraystep(void * cs, size_t value) {
    if (cs == NULL) { return; }
	*(size_t *)(cs - 3 * basesize()) = value;
}

size_t carraystep(void * cs) {
	if (cs == NULL) { return -1; }
    return *(size_t *)(cs - 3 * basesize());
}

static void setcarrayvolume(void * cs, size_t value) {
    if (cs == NULL) { return; }
	*(size_t *)(cs - 2 * basesize()) = value;
}

size_t carrayvolume(void * cs) {
	if (cs == NULL) { return -1; }
    return *(size_t *)(cs - 2 * basesize());
}

static void setcarraylength(void * cs, size_t value) {
    if (cs == NULL) { return; }
	*(long *)(cs - 1 * basesize()) = value;
}

size_t carraylength(void * cs) {
	if (cs == NULL) { return -1; }
    return *(size_t *)(cs - 1 * basesize());
}

void * carrayinit(void * src, cbasetype_t type, size_t length) {
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
    while (volume <= length) {
		volume *= 2;
	}
    void * space = malloc(base + step * length);
    void * cs = space + base;
	for (long i = 0; i < length * step; i ++) {
		((char *)cs)[i] = ((char *)src)[i];
	}
    setcarraytype(cs, type);
    setcarraystep(cs, step);
	setcarraylength(cs, length);
	setcarrayvolume(cs, volume);
    return cs;
}

void carrayfree(void * cs) {
    free(cs - 4);
}

void carraydescribe(void * cs) {
	if (!cs) { return; }
    printf("\n[type(8 Byte)|step(8 Bytpe)|volume(8 Byte)|length(8 Byte)|data...]: (%p)\n[\n", cs);
    cbasetype_t type = carraytype(cs);
    char * info = NULL;
    switch (type) {
    case cchar:   info = "char"; break;
    case cuchar:  info = "unsigned char"; break;
    case cshort:  info = "short"; break;
    case cushort: info = "unsigned short"; break;
    case cint:    info = "int"; break;
    case cuint:   info = "unsigned int"; break;
    case cfloat:  info = "float"; break;
    case clong:   info = "long"; break;
    case culong:  info = "unsigned long"; break;
    case cdouble: info = "double"; break;
    }
    printf("    (%ld Byte  H:0x%016x  D:%032u  Array.type = %s),\n", sizeof(long), type, type, info);

    long step = carraystep(cs);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Array.step = %ld),\n", sizeof(long), step, step, step);

    long volume = carrayvolume(cs);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Array.volume = %ld),\n", sizeof(long), volume, volume, volume);

    long length = carraylength(cs);
	printf("    (%ld Byte  H:0x%016lx  D:%032ld  Array.length = %ld)", sizeof(long), length, length, length);
	
	if (length != 0) {
		printf(",");
	}
	printf("\n");

	for (int i = 0; i < length; i ++) {
        switch (type) {
        case cchar:   printf("    %d", ((char *)cs)[i]); break;
        case cuchar:  printf("    %d", ((unsigned char *)cs)[i]); break;
        case cshort:  printf("    %d", ((short *)cs)[i]); break;
        case cushort: printf("    %d", ((unsigned short *)cs)[i]); break;
        case cint:    printf("    %d", ((int *)cs)[i]); break;
        case cuint:   printf("    %d", ((unsigned int *)cs)[i]); break;
        case cfloat:  printf("    %f", ((float *)cs)[i]); break;
        case clong:   printf("    %ld", ((long *)cs)[i]); break;
        case culong:  printf("    %ld", ((unsigned long *)cs)[i]); break;
        case cdouble: printf("    %lf", ((double *)cs)[i]); break;
        }
		if (i != length - 1) {
			printf(",\n");
		} else {
			printf("\n");
		}
	}
	printf("]\n\n");
}

void char2binary(char value, format_t fmt) {
    switch (fmt) {
    case original: break;
    case inverse: break;
    case complement: break;
    }
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        if (i == sizeof(value) * 8 - 1) {
            printf("\033[31m%d\033[0m", (value >> i) & 1);
        } else {
            printf("%d", (value >> i) & 1);
        }
    }
    printf("\n");
}

void short2binary(short value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        if (i == sizeof(value) * 8 - 1) {
            printf("\033[31m%d\033[0m", (value >> i) & 1);
        } else {
            printf("%d", (value >> i) & 1);
        }
    }
    printf("\n");
}

void int2binary(int value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        if (i == sizeof(value) * 8 - 1) {
            printf("\033[31m%d\033[0m", (value >> i) & 1);
        } else {
            printf("%d", (value >> i) & 1);
        }
    }
    printf("\n");
}

void long2binary(long value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        if (i == sizeof(value) * 8 - 1) {
            printf("\033[31m%ld\033[0m", (value >> i) & 1);
        } else {
            printf("%ld", (value >> i) & 1);
        }
    }
    printf("\n");
}

void uchar2binary(unsigned char value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void ushort2binary(unsigned short value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
       printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void uint2binary(unsigned int value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void ulong2binary(unsigned long value, format_t fmt) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        printf("%ld", (value >> i) & 1);
    }
    printf("\n");
}

void float2binary(float value, format_t fmt) {
    // 将num转换为二进制
    int i;
    unsigned int *p = (unsigned int*)&value;
    unsigned int n = *p;
 
    // 处理符号位
    printf("\033[31m%u\033[0m", (n >> 31) & 1);
    // printf("%u", (n >> 31) & 1);
 
    // 处理指数位
    for (i = 23; i < 31; i ++) {
        printf("%u", (n >> i) & 1);
    }
 
    // 处理尾数位
    for (i = 0; i < 23; i ++) {
        printf("\033[0;33m%u\033[0m", (n >> i) & 1);
    }
    printf("\n");
}

void double2binary(double value, format_t fmt) {
    // 将num转换为二进制
    long i;
    unsigned long *p = (unsigned long*)&value;
    unsigned long n = *p;
 
    // 处理符号位
    printf("\033[31m%lu\033[0m", (n >> 63) & 1);
 
    // 处理指数位
    for (i = 52; i < 63; i ++) {
        printf("%lu", (n >> i) & 1);
    }
 
    // 处理尾数位
    for (i = 0; i < 52; i ++) {
        printf("\033[0;33m%lu\033[0m", (n >> i) & 1);
    }
    printf("\n");
}

void showcolor() {
	printf("\033[30m****Linux*****(30)\033[0m\r\n");
    printf("\033[31m****Linux*****(31)\033[0m\r\n");
    printf("\033[32m****Linux*****(32)\033[0m\r\n");
    printf("\033[33m****Linux*****(33)\033[0m\r\n");
    printf("\033[34m****Linux*****(34)\033[0m\r\n");
    printf("\033[35m****Linux*****(35)\033[0m\r\n");	
    printf("\033[36m****Linux*****(36)\033[0m\r\n");
    printf("\033[37m****Linux*****(37)\033[0m\r\n");	
    printf("\033[40m****Linux*****(40)\033[0m\r\n");
    printf("\033[41m****Linux*****(41)\033[0m\r\n");
    printf("\033[42m****Linux*****(42)\033[0m\r\n");
    printf("\033[43m****Linux*****(43)\033[0m\r\n");
    printf("\033[44m****Linux*****(44)\033[0m\r\n");
    printf("\033[45m****Linux*****(45)\033[0m\r\n");	
    printf("\033[46m****Linux*****(46)\033[0m\r\n");
    printf("\033[47m****Linux*****(47)\033[0m\r\n");	
}

void endian() {
    unsigned short test = 0x1122;
    if(*( (unsigned char*) &test ) == 0x11)
        printf("大端\n");
    else
        printf("小端\n");

    // unsigned char * p = (unsigned char*)&test;
    // for (short i = 0; i < 2; i ++ ) {
    //     printf("%x\n", p[i]);
    // }

    /*
    +
        11
        22
    -
    */
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