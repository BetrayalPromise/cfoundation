#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>

#define ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
	if (true) {
		char a[] = {8};
		char * p = carrayinit(a, ARRAY_COUNT(a), cbasechar);
		printf("%d\n", p[0]);
		carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
		carraydescribe(p);
		carrayfree(p);
	}
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	uchar a[] = {};
	// 		char * p = carrayinit(a, ARRAY_COUNT(a), cbaseuchar);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	short a[] = {};
	// 		short * p = carrayinit(a, ARRAY_COUNT(a), cbaseshort);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	ushort a[] = {};
	// 		char * p = carrayinit(a, ARRAY_COUNT(a), cbaseushort);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	int a[] = {};
	// 		int * p = carrayinit(a, ARRAY_COUNT(a), cbaseint);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	uint a[] = {};
	// 		uint * p = carrayinit(a, ARRAY_COUNT(a), cbaseuint);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	long a[] = {};
	// 		long * p = carrayinit(a, ARRAY_COUNT(a), cbaselong);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	ulong a[] = {};
	// 		ulong * p = carrayinit(a, ARRAY_COUNT(a), cbaseulong);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	if (true) {
		// BitDisplay(float, 4.00);
		float a[] = { 4.00, 4 };
		float * p = carrayinit(a, ARRAY_COUNT(a), cbasefloat);
		printf("%f", p[0]);
		carraydescribe(p);
		carrayinsert0$(p, 0, 1.0);
		carraydescribe(p);
		carrayfree(p);
	}
	if (true) {
	 	double a[] = {};
		double * p = carrayinit(a, ARRAY_COUNT(a), cbasedouble);
		carrayinsert0$(p, 0, 9.0);
		carraydescribe(p);
		carrayfree(p);
	}
	// if (true) {
	// 	double a[] = {6};
	// 	double * p  = carrayinit(a, ARRAY_COUNT(a), cbasedouble);
	// 	double * p1 = carrayinit(a, ARRAY_COUNT(a), cbasedouble);
	// 	carrayinsert1$(p, 0, p1);
	// }
}

#endif