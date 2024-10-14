#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include "cchars.h"
#include "array.h"
#include "cstring.h"
#include "test.h"

	// 0x0;
    // __asm__ __volatile__("movq %%## #r, %0" : "=r"(value))
//#define readdata(r)
//	printf("%%%s", #r);


int main(int argc, char ** argv) {
	// testcstringinit();
	// testcstringtelescope();
	// testcstringinsrt();
	char * cstr = cstringinit$("0", 100);
	char * p = cstringinit$("0", 54);

	cstringdescribe(cstr, 0b101);
	cstringdescribe(p, 0b101);

	return EXIT_SUCCESS;
}



// unsigned long read(char * rname) {
//     unsigned long value = 0x0;
//     __asm__ __volatile__("mov %%rbp, %0" : "=r"(value));
//     return value;
// }
