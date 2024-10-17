#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include "array.h"
#include "cstring.h"
#include "testcstring.h"
#include "number.h"

// 0x0;
// __asm__ __volatile__("movq %%## #r, %0" : "=r"(value))
//#define readdata(r)
//	printf("%%%s", #r);

int main(int argc, char ** argv) {
	// testcstringinit();
	// testcstringtelescope();
	// testcstringinsrt();
	// testcstringremove();
	// testcstringindex();
	// testcstringunique();

	// int x;
	// char x0, x1;
	// x = 0x1122;
	// x0 = ((char*)&x)[0];	//低地址单元
	// x1 = ((char*)&x)[1];	//高地址单元
	// printf("%x\n", x0);
	// printf("%x\n", x1);
	/*
		高
			22低
			11高
		低
	*/

	char2binary('c', original);
	short2binary(3, original);
	int2binary(3, original);
	long2binary(8, original);
	uchar2binary('c', original);
	ushort2binary(3, original);
	uint2binary(3, original);
	ulong2binary(8, original);
	float2binary(3.14, original);
	double2binary(3.14, original);


	return EXIT_SUCCESS;
}

// unsigned long read(char * rname) {
//     unsigned long value = 0x0;
//     __asm__ __volatile__("mov %%rbp, %0" : "=r"(value));
//     return value;
// }
