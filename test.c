#ifndef __TEST_C__
#define __TEST_C__

#include "test.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void testcstringinit() {
	char * p0 = cstringinit(0x00);
	// p1, p2等价
	char * p1 = cstringinit("");
	char * p2 = cstringinit("\0000");

	cstringdescribe(p0, 0b100);
	cstringdescribe(p1, 0b100);
	cstringdescribe(p2, 0b100);
}

void testcstringinsrt() {
    char * p0 = cstringinit("hhh");
	char * p1 = cstringinit("01");
	// char * p2 = cstringinit("01");
	// cstringdescribe(p0, 0b101);

	printf("p0 == %p\n", p0);
	printf("p1 == %p\n", p1);
	// printf("p2 == %p\n", p2);
	cstringinsert(p0, 5, p1);
	cstringdescribe(p0, 0b111);
}

void testcstringtelescope() {
    char * p = cstringinit(0x00);
	cstringtelescope(&p, true, 2);
	cstringdescribe(p, 0b100);
}

#endif

