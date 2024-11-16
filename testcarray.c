#ifndef __TESTCARRAY_C__
#define __TESTCARRAY_C__

#include "carray.h"
#include "cstring.h"
#include <stdbool.h>
#include <stdio.h>

#define COUNT(a) sizeof(a) / sizeof(a[0])

void testcarrayinit() {
	// if (true) {
	// 	char a[] = {8};
	// 	char * p = carrayinit(a, COUNT(a), cchar);
	// 	carrayinsert0$(p, 1, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	uchar a[] = {};
	// 	char * p = carrayinit(a, COUNT(a), cuchar);
	// 	carrayinsert0$(p, 3, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	short a[] = {};
	// 	short * p = carrayinit(a, COUNT(a), cshort);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	ushort a[] = {};
	// 	ushort * p = carrayinit(a, COUNT(a), cushort);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	int a[] = {};
	// 	int * p = carrayinit(a, COUNT(a), cint);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	uint a[] = {};
	// 	uint * p = carrayinit(a, COUNT(a), cuint);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	long a[] = {};
	// 	long * p = carrayinit(a, COUNT(a), clong);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	ulong a[] = {};
	// 	ulong * p = carrayinit(a, COUNT(a), culong);
	// 	carrayinsert0$(p, 0, 0, 9, 8, 7, 6);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	float a[] = { 4.00, 4 };
	// 	float * p = carrayinit(a, COUNT(a), cfloat);
	// 	carraydescribe(p);
	// 	carrayinsert0$(p, 0, 1.0);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	double a[] = {};
	// 	double * p = carrayinit(a, COUNT(a), cdouble);
	// 	carrayinsert0$(p, 0, 9.0);
	// 	carraydescribe(p);
	// 	carrayfree(p);
	// }
	// if (true) {
	// 	for (int i = -1; i < 5; i ++) {
	// 		double a[] = {1, 2, 5, 6};
	// 		double b[] = {7.0, 8.0};
	// 		double * p  = carrayinit(a, COUNT(a), cdouble);
	// 		double * p1 = carrayinit(b, COUNT(b), cdouble);
	// 		carrayinsert1$(p, i, p1);
	// 		carraydescribe(p);
	// 	}
	// }

	float a[] = {0, 3.1, 0, 8, 3, 8};
	int b = unique(a, cfloat, 6);

	int c = sizeof(long double);

}

#endif