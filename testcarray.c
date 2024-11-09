#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"
#include "cstring.h"

#define GET_ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
    int a[] = { };
	int * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseint);
	carraydescribe(p);
	// carrayfree(p);
	carrayinsert$(p, single, 0, 9, 8, 7, 6);
}

#endif