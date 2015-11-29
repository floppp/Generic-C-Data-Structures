#include "../headers/test_hashset.h"

int get_random(double(*)(), int, int);

void test_int_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(int), 20, hash_fun, int_comparator, NULL);

//	for (int i = 0; i < 20; ++i) {
//		int n = get_random(uniforme, 0, 150);
//		hashset_enter(&h, &n);
//	}

	printf("\n");
	int a = 6;
//	hashset_enter(&h, &a);

	for (int i = 0; i < 20; i++) {
		vector* aux = (struct vector*) (h.elements + i*sizeof(vector*));
		printf("vector elements direction: %d - ", aux->elements);
		printf("vector direction: %d - ", aux);
		printf("alloc: %d\n", aux->allocat_len);
	}

//	hashset_map(&h, print_int, NULL);
	hashset_dispose(&h);
}

int get_random(double (*generator_fun)(), int min, int max)
{
	double temp = generator_fun();

	return (min - 1) + ceil(temp*(max - min));
}
