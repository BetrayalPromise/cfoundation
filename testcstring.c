#ifndef __TESTCSTRING_C__
#define __TESTCSTRING_C__

#include "testcstring.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testcstringinit() {
	// if (true) {
	// 	char * p0 = cstringinit(0x00, true);
	// 	char * p1 = cstringinit(0x00, false);
	// 	char * p2 = cstringinit(0, true);
	// 	char * p3 = cstringinit(0, false);
	// 	char * p4 = cstringinit(NULL, true);
	// 	char * p5 = cstringinit(NULL, false);
	// 	cstringdescribe(p0, 0b100);
	// 	cstringdescribe(p1, 0b100);
	// 	cstringdescribe(p2, 0b100);
	// 	cstringdescribe(p3, 0b100);
	// 	cstringdescribe(p4, 0b100);
	// 	cstringdescribe(p5, 0b100);
	// }

	if (true) {
		char * p0 = cstringinit("", true);
		char * p1 = cstringinit("", false);
		char * p2 = cstringinit("\00000", true);
		char * p3 = cstringinit("\00000", false);
		cstringdescribe(p0, 0b100);
		cstringdescribe(p1, 0b100);
		cstringdescribe(p2, 0b100);
		cstringdescribe(p3, 0b100);
	}

	if (true) {
		char * p = CHAR2CSTRING(p, 'y');
		long length = cstringlength(p);
		long volume = cstringvolume(p);
		cstringdescribe(p, 0b100);
	}
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

void testcstringindex() {
	// if (true) {
	// 	char * p0 = cstringinit$(NULL);
	// 	char c  = 0x00;
	// 	cstringindex(p0, 0, c);
	// 	cstringdescribe(p0, 0b001);
	// }

	// if (true) {
	// 	char * p0 = cstringinit$("\0");
	// 	char c  = 0x00;
	// 	cstringindex(p0, 1, c);
	// 	cstringdescribe(p0, 0b001);
	// }

	// if (true) {
	// 	char * p0 = cstringinit$("\0");
	// 	char * p1 = cstringinit$("\0");
	// 	cstringindex(p0, 1, p1);
	// 	cstringdescribe(p0, 0b001);
	// }

	// if (true) {
	// 	char * p0 = cstringinit$("9900990099");
	// 	char * p1 = cstringinit$("99");
	// 	long index = cstringindex$(p0, , p1, false);
	// 	printf("index = %ld\n", index);
	// }

	// if (true) {
	// 	for (int i = -9; i < 8; i++) {
	// 		char * p0 = cstringinit$("00000000000000");
	// 		char * p1 = cstringinit$("00");
	// 		long index = cstringindex(p0, i, p1, true);
	// 		printf("times = %d  index = %ld\n", i, index);
	// 	}
	// }
	
	if (true) {
		char * p0 = cstringinit$("0000000");
		char * p1 = cstringinit$("00");
		for (int i = -1; i < 10; i ++) {
			long index = cstringindex(p0, i, p1, true);
			printf("i = %d, index = %ld\n", i, index);
		}
		
		for (int i = -1; i < 10; i ++) {
			long index = cstringindex(p0, i, p1, false);
			printf("i = %d, index = %ld\n", i, index);
		}
	}

}

void testcstringindexes() {
	
}

void testcstringremove() {
	// if (true) {
	// 	char * p0 = cstringinit$("12321");
	// 	cstringremove(p0, 5);
	// 	cstringdescribe(p0, 0b001);
	// }

	char * p0 = cstringinit$("900900099");
	char * p1 = cstringinit$("00");
	long index = cstringclean(p0, p1);
	cstringdescribe(p0, 0b100);
}

void testcstringclean() {
	if (true) {
		char * p0 = cstringinit$(NULL);
		char c  = 0x00;
		cstringclean(p0, c);
		cstringdescribe(p0, 0b001);
	}
	if (true) {
		char * p0 = cstringinit$(0x00);
		char c  = 0x00;
		cstringclean(p0, c);
		cstringdescribe(p0, 0b001);
	}
	if (true) {
		char * p0 = cstringinit$(0x00);
		char c  = 0x00;
		cstringclean(p0);
		cstringdescribe(p0, 0b001);
	}
}

void testcstringunique() {
	char * p0 = cstringinit$("0523541007840000");
	cstringunique(p0, false);
	cstringdescribe(p0, 0b001);
}

#endif

