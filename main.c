#include <i386/_types.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_u_int16_t.h>
#include "cstring.h"
#include "testcstring.h"
#include "carray.h"
#include "testcarray.h"
#include "cutils.h"

// 0x0;
// __asm__ __volatile__("movq %%## #r, %0" : "=r"(value))
//#define readdata(r)
//	printf("%%%s", #r);

int main(int argc, char ** argv) {
	// testcstringinit();
	// testcstringtelescope();
	// testcstringinsrt();
	// testcstringindex();
	// testcstringunique();
	// testcstringremove();
	// testcstringsort();

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

	// char * p = STRING2CSTRING(p, "ABC");
	// long length = cstringlength(p);
	// long volume = cstringvolume(p);
	// cstringdescribe(p, 0b001);

	// printf("%d\n", ARGC(1, 2, 3, 4, 5, 6, 7, 8, 9, 0));

/*
	0xFFFFFFFFFFFFFFFF                  0x0000000000000000
	高------------------------>>>------------------------低
	0x01实际以10000000方式存储
*/

	// unsigned long temp = (unsigned long)0.1;
    // for (int i = 0; i < 8 * sizeof(long); i ++) {
	//     printf("%lu", BitGet(temp, i));
    // }
	
	// BitShow(char, 0x01);
	// BitShow(char, -1);
	// BitShow(short, 0x01);
	// BitShow(int, 0x01);
	// BitShow(long, 0x01);
	// BitShow(float, 12.5);
	// BitShow(double, 12.5);

	// float a = 12.5; 
    // int * p = (int *)&a;
    // int b = *p;
	// printf("b: %d\n",b);

	// testcarrayinit();

	store_t t = { 10 };

	printf("%d\n", t.scharvalue);
	printf("%d\n", t.ucharvalue);
	printf("%d\n", t.sshortvalue);
	printf("%d\n", t.ushortvalue);
	printf("%d\n", t.sintvalue);
	printf("%d\n", t.uintvalue);
	printf("%ld\n", t.slongvalue);
	printf("%ld\n", t.ulongvalue);
	printf("%f\n", t.floatvalue);
	printf("%lf\n", t.doublevalue);

	return EXIT_SUCCESS;
}

// unsigned long read(char * rname) {
//     unsigned long value = 0x0;
//     __asm__ __volatile__("mov %%rbp, %0" : "=r"(value));
//     return value;
// }