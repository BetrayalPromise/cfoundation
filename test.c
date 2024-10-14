#ifndef __TEST_C__
#define __TEST_C__

#include "test.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testcstringinit$() {
	char * p0 = cstringinit$(0x00, 64);
	// p1, p2等价
	char * p1 = cstringinit$("");
	char * p2 = cstringinit$("\0000");

	cstringdescribe(p0, 0b100);
	cstringdescribe(p1, 0b100);
	cstringdescribe(p2, 0b100);
}

void testcstringinsrt() {
	if (true) {
		for (int i = -3; i < 4; i ++) {
			char * p0 = cstringinit$(NULL);
			cstringinsert(p0, i, '2');
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -3; i < 4; i ++) {
			char * p0 = cstringinit$("\0");
			cstringinsert(p0, i, '2');
			cstringdescribe(p0, 0b111);
		}
	}

    
	if (true) {
		for (int i = 0; i < 6; i ++) {
			char * p0 = cstringinit$("1234");
			cstringinsert(p0, i, 'A');
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -3; i < 4; i ++) {
			char * p0 = cstringinit$(NULL);
			char * p1 = cstringinit$(NULL);
			cstringinsert(p0, i, p1);
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -1; i < 2; i ++) {
			char * p0 = cstringinit$(NULL);
			char * p1 = cstringinit$("abc");
			cstringinsert(p0, 5, p1);
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -1; i < 2; i ++) {
			char * p0 = cstringinit$("\0");
			char * p1 = cstringinit$(NULL);
			cstringinsert(p0, i, p1);
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -1; i <= 0; i ++) {
			char * p0 = cstringinit$("\0");
			char * p1 = cstringinit$("abc");
			cstringinsert(p0, i, p1);
			cstringdescribe(p0, 0b111);
		}
	}

	if (true) {
		for (int i = -1; i <= 0; i ++) {
			char * p0 = cstringinit$("0");
			char * p1 = cstringinit$("abc");
			cstringinsert(p0, 2, p1);
			cstringdescribe(p0, 0b111);
		}
	}
}

void testcstringtelescope() {
    char * p = cstringinit$(0x00);
	cstringtelescope(&p, true, 2);
	cstringdescribe(p, 0b100);
}

void testcstringsearch() {
	char * p0 = cstringinit$("0980900");
	char c 	  = '0';

	long * value = cstringindexes(p0, c);
	long result[*(long *)value];

	for (int i = 0; i < *(long *)value; i ++) {
		result[i] = value[i + 1];
		printf("%ld\n", value[i + 1]);
	}
	free(value);
	
	
}

#endif

