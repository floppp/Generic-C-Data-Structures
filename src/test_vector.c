#include "../headers/test_vector.h"

void print_int(const void* elem_addr, const void* aux_data);

void test_int_vector()
{
	vector v;
	vector_new(&v, sizeof(int), NULL, 4);

	printf("vector len: %d\n", vector_len(&v));
	int xs[] = { 1, 2, 3, 4, 2, 5, 6, 7, 1, 2, 3, 0};
	for (int var = 0; var < 12; ++var)
		vector_append(&v, &xs[var]);
	vector_map(&v, print_int, NULL);
	printf("\n");

	int x = *(int*) vector_get(&v, 0);
	printf("pos 0: %d\n", x);

	printf("vector len: %d\n", vector_len(&v));

	int ys[] = {-1, -2, -3, -4};
	for (int var = 0; var < 4; ++var)
		vector_insert(&v, &ys[var], var*2);

	printf("vector len: %d\n", vector_len(&v));
	vector_map(&v, print_int, &x);
	printf("\n");

	x = 9999;
	vector_replace(&v, &x, 5);
	vector_map(&v, print_int, &x);
	printf("\n");

	vector_delete(&v, 0);
	vector_delete(&v, v.len - 1);
	vector_map(&v, print_int, &x);
	printf("\n");

	int s = 7;
	int pos = vector_search(&v, &s, int_comparator, 0, false);
	printf("LINEAR SEARCH: elem %d is in position %d\n", s, pos);
	vector_sort(&v, int_comparator);
	vector_map(&v, print_int, &x);
	printf("\n");
	pos = vector_search(&v, &s, int_comparator, 0, true);
	printf("BINARY SEARCH AFTER QSORT: elem %d is in position %d\n", s, pos);


	vector_dispose(&v);
}

void print_int(const void* elem_addr, const void* aux_data)
{
	printf("%d : ", *(int*) elem_addr);
}
