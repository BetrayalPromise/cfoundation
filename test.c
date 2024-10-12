#ifndef __TEST_C__
#define __TEST_C__

#include "test.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
	// cstringinsert(p0, -1, 'a', 'b', 'c', 'd', 'e', 'f', 'g');
	cstringinsert(p0, 0, (void *)'b');
}

void testcstringtelescope() {
    char * p = tocstring(0x00);
	cstringtelescope(&p, true, 2);
	cstringdescribe(p, 0b100);
}

#endif

