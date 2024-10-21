#ifndef __NUMBER_C__
#define __NUMBER_C__

#include <stdio.h>
#include "number.h"
#include <math.h>
#include <stdlib.h>


static void setnumbersvolume(long * ns, size_t value) {
	*(size_t *)(ns - 2) = value;
}

size_t numbersvolume(long * ns) {
	if (ns == NULL) { return -1; }
    return *(size_t *)(ns - 2);
}

static void setnumberslength(long * ns, size_t value) {
	*(long *)(ns - 1) = value;
}

size_t numberslength(long * ns) {
	if (ns == NULL) { return -1; }
    return *(size_t *)(ns - 1);
}

long * numbersinit(long * n, long size) {
    long vstep = 1;
	long lstep = 1;
	long volume = 32;
	long length = 0;
    long * space = malloc(vstep + lstep + volume);
    long * ns = space + vstep + lstep;
	setnumberslength(ns, 0);
	setnumbersvolume(ns, volume);
    return ns;
}

void numbersfree(long * ns) {
    free(ns + 2);
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