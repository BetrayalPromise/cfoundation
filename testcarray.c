#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"

void testcarrayinit() {
    int a[] = { 11, 12, 13 };
	int * p = carrayinit(a, cint, sizeof(a) / sizeof(int));
	carraydescribe(p);
}

#endif