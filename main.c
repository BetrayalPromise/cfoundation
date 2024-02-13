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
	
	struct array * array = array_init(0);
	int p = 8;
	array_insert(array, &p, 0);
	int p1 = 9;
	array_insert(array, &p1, 0);
	char c = 'a';
	array_insert(array, &c, 0);

	for (int i = 0; i < array->count; i ++) {
		if (i == 0) {
			printf("%p=%c\n", array->store[i], *(char *)array_index(array, i));
			continue;
		}
		printf("%p=%d\n", array->store[i], *(int *)array_index(array, i));
	}
	array_free(array);
	return EXIT_SUCCESS;
}