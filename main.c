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
	// testcstringremove();
	testcstringindex();

	return EXIT_SUCCESS;
}



// unsigned long read(char * rname) {
//     unsigned long value = 0x0;
//     __asm__ __volatile__("mov %%rbp, %0" : "=r"(value));
//     return value;
// }
