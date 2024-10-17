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

	// int a = 9;
	// int b = 6;
	// int c = 6;
	// int * p = &a;
	// printf("%p, %p, %p\n", &a, &b, &c);

	// char string[4] = "123";
	// char * p = string;

	// for (int i = 0; i < 4; i ++) {
	// 	printf("%p\n", p ++);
	// }

	int x;
	char x0, x1;
	x = 0x1122;
	x0 = ((char*)&x)[0]; //低地址单元
	x1 = ((char*)&x)[1]; //高地址单元
	

	printf("%x\n", x0);
	printf("%x\n", x1);


	return EXIT_SUCCESS;
}



// unsigned long read(char * rname) {
//     unsigned long value = 0x0;
//     __asm__ __volatile__("mov %%rbp, %0" : "=r"(value));
//     return value;
// }
