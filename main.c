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

	// cchars_t * cs = __CCHARS_INIT__("\090\080\080");
	// cchars_t * c = __CCHARS_INIT__("80");
	// cchars_t * cs = __CCHARS_INIT__("aaaaa");
	// cchars_t * c = __CCHARS_INIT__("aaaaa");
	// // cchars_description(cs);
	// cchars_description(c);
	// long * info = cchars_search_cchars(cs, c);
	// cchars_search_description(info);
	// cchars_description(cs);
	// cchars_remove_character(cs, 0x00);
	// cchars_description(cs);

	// char * p0 = array;
	// printf("%lu\n", sizeof(array));
	// printf("%lu\n", strlen(p0));
	// cchars_t * t = cchars_init(p0, -1);
	// printf("%p\n", t);

	// cchars_ascii();

	// printf("%lu\n", sizeof(int));
	// printf("%lu\n", sizeof(long));

	// cchars_t * cs = __CCHARS_INIT__("\090\080\080");
	// long * a = cchars_search_character(cs, '\0');

	// cchars_search_description(a);

	// cchars_t * cs = __CCHARS_INIT__("aaaaa");
	// cchars_t * cs = __CCHARS_INIT__("987654321");
	

	// cchars_change_cchars(cs, 5, c);
	// cchars_description(cs, 0b111);

	/*
	9876543210123456789
	         987654321
	        [
		      ]
	*/

	// cchars_remove_boundary(cs, 3, 3);
	// cchars_description(cs, 0b111);

	// cchars_description(cs, 0b011);

	cchars_t * c = __CCHARS_INIT__("aaaaa");
	// cchars_t * d = __CCHARS_INIT__("aa");
	// long * result = cchars_search_cchars(c, d, 0b01);
	// cchars_description(result, search_type, 0b111);

	char * cstring = cchars_mutate_cstring(c);
	cchars_description(cstring, string_type, 0b111);

	return EXIT_SUCCESS;
}