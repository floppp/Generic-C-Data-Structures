#include "../headers/test_hashset.h"

int get_random(double(*)(), int, int);

void test_int_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(vector), 20, hash_fun, int_comparator, NULL);

	printf("GENERATED NUMBERS\n");
	for (int i = 0; i < 10; ++i) {
		int n = get_random(uniforme, 0, 150);
		hashset_enter(&h, &n);
//		printf("%d : ", n);
	}
	printf("\n");

	hashset_map(&h, print_int, NULL);
	hashset_dispose(&h);
}

int get_random(double (*generator_fun)(), int min, int max)
{
	double temp = generator_fun();

	return (min - 1) + ceil(temp*(max - min));
}
