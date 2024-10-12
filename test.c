#ifndef __TEST_C__
#define __TEST_C__

#include "test.h"
#include "cstring.h"
#include <stdio.h>

void testcstringdescribe() {
	char * p0 = tocstring(0x00);
	// p1, p2等价
	char * p1 = tocstring("");
	char * p2 = tocstring("\0000");

	cstringdescribe(p0, 0b100);
	cstringdescribe(p1, 0b100);
	cstringdescribe(p2, 0b100);
}

void testcstringinsrt() {
    char * p0 = tocstring(0x00);
	char * p = "xxx";
	cstringinsert(p0, -1, p);
    printf("%p\n", &p);
}

#endif

