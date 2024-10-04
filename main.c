#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include "cchars.h"
#include "array.h"

void a(int array[]);

int main(int argc, char ** argv) {
	// printf("sizeof(void) = %lu\n", sizeof(void));
	// printf("sizeof(void *) = %lu\n", sizeof(void *));
	// printf("sizeof(void **) = %lu\n", sizeof(void * *));
	
	// struct array * array = array_init(0);
	// int p = 8;
	// array_insert(array, &p, 0);
	// int p1 = 9;
	// array_insert(array, &p1, 0);
	// char c = 'a';
	// array_insert(array, &c, 0);
	// for (int i = 0; i < array->count; i ++) {
	// 	if (i == 0) {
	// 		printf("%p=%c\n", array->store[i], *(char *)array_index(array, i));
	// 		continue;
	// 	}
	// 	printf("%p=%d\n", array->store[i], *(int *)array_index(array, i));
	// }
	// array_free(array);

	// struct array * array = array_init(sizeof(int));
	// int p = 1314;
	// for (int i = 0; i < 4; i ++) {
	// 	array_insert(array, &p, 0);
	// }
	// for (int i = 0; i < array->count; i ++) {
	// 	printf("%p=%d\n", array_index(array, i), *(int *)array_index(array, i));
	// }
	// for (int i = 0; i < array->count; i ++) {
	// 	printf("%d\n", *(int *)*(&array->store[0] + array->typesize * i));
	// }
	// array_free(array);

	// CCHARS(a, "\0\0\0");
	// printf("%ld\n", a);
	// 在栈中
	char array[] = "\09\0";
	cchars_t * cs = __CCHARS_INIT__(cs, array);

	// char * p0 = array;
	// printf("%lu\n", sizeof(array));
	// printf("%lu\n", strlen(p0));
	// cchars_t * t = cchars_init(p0, -1);
	// printf("%p\n", t);
	return EXIT_SUCCESS;
}