#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"

#define GET_ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
    int a[] = { 1, 2, 4, 10 };
	int * p = carrayinit(a, cbaseint, GET_ARRAY_COUNT(a));
	carraydescribe(p);
	carrayfree(p);
}

#endif