#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cchars.h"
#include "array.h"

int main(int argc, char ** argv) {
	// printf("sizeof(void) = %lu\n", sizeof(void));
	// printf("sizeof(void *) = %lu\n", sizeof(void *));
	// printf("sizeof(void **) = %lu\n", sizeof(void * *));
	int p = 8;
	printf("%p\n", &p);
	struct array * array = array_init(sizeof(int));
	array_insert(array, &p, 0);
	int p1 = 9;
	printf("%p\n", &p1);
	array_insert(array, &p1, 0);

	for (int i = 0; i < array->count; i ++) {
		printf("%p=%d\n", array->store[i], *(int *)array_index(array, i));
	}
	return EXIT_SUCCESS;
}