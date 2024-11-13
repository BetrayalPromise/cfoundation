#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>

#define GET_ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	// 		char a[] = {};
	// 		char * p = carrayinit(a, GET_ARRAY_COUNT(a), cbasechar);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	uchar a[] = {};
	// 		char * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseuchar);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	short a[] = {};
	// 		short * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseshort);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	ushort a[] = {};
	// 		char * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseushort);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	int a[] = {};
	// 		int * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseint);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	uint a[] = {};
	// 		uint * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseuint);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	long a[] = {};
	// 		long * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaselong);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	// if (true) {
	// 	for (int i = 0; i < 10000; i ++) {
	//     	ulong a[] = {};
	// 		ulong * p = carrayinit(a, GET_ARRAY_COUNT(a), cbaseulong);
	// 		carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 		carraydescribe(p);
	// 		carrayfree(p);
	// 	}
	// }
	if (true) {
		BitShow(double, 4.00);

	    double a[] = { 4.00 };
		double v = a[0];
		double * p = carrayinit(a, GET_ARRAY_COUNT(a), cbasedouble);
		carraydescribe(p);
		carrayinsert0$(p, 0, 1.0);
		carraydescribe(p);
		carrayfree(p);
	}
	// if (true) {
	//  double a[] = {};
	// 	double * p = carrayinit(a, GET_ARRAY_COUNT(a), cbasedouble);
	// 	carrayinsert$(p, single, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
}

#endif