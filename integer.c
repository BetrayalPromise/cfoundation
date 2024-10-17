#ifndef __INTEGER_C__
#define __INTEGER_C__

#include <stdio.h>
#include "integer.h"

void showbinary(long n) {
    for (int i = sizeof(n) * 8 - 1; i >= 0; i--) {
        printf("%ld", (n >> i) & 1);
    }
    printf("\n");
}

#endif