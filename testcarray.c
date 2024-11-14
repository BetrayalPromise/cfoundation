#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>

#define ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
	// if (true) {
	// 	char a[] = {8};
	// 	char * p = carrayinit(a, ARRAY_COUNT(a), cbasechar);
	// 	carrayinsert0$(p, 1, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	uchar a[] = {};
	// 	char * p = carrayinit(a, ARRAY_COUNT(a), cbaseuchar);
	// 	carrayinsert0$(p, 3, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	short a[] = {};
	// 	short * p = carrayinit(a, ARRAY_COUNT(a), cbaseshort);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	ushort a[] = {};
	// 	ushort * p = carrayinit(a, ARRAY_COUNT(a), cbaseushort);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	int a[] = {};
	// 	int * p = carrayinit(a, ARRAY_COUNT(a), cbaseint);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	uint a[] = {};
	// 	uint * p = carrayinit(a, ARRAY_COUNT(a), cbaseuint);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	long a[] = {};
	// 	long * p = carrayinit(a, ARRAY_COUNT(a), cbaselong);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	ulong a[] = {};
	// 	ulong * p = carrayinit(a, ARRAY_COUNT(a), cbaseulong);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	float a[] = { 4.00, 4 };
	// 	float * p = carrayinit(a, ARRAY_COUNT(a), cbasefloat);
	// 	carraydescribe(p);
	// 	carrayinsert0$(p, 0, 1.0);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	double a[] = {};
	// 	double * p = carrayinit(a, ARRAY_COUNT(a), cbasedouble);
	// 	carrayinsert0$(p, 0, 9.0);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	if (true) {
		for (int i = -1; i < 5; i ++) {
			double a[] = {1, 2, 5, 6};
			double b[] = {7.0, 8.0};
			double * p  = carrayinit(a, ARRAY_COUNT(a), cbasedouble);
			double * p1 = carrayinit(b, ARRAY_COUNT(b), cbasedouble);
			carrayinsert1$(p, i, p1);
			carraydescribe(p);
		}
	}
}

#endif