#include "../headers/test_hashset.h"

int get_random(double(*)(), int, int);

void test_int_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(int), 20, hash_fun, int_comparator, NULL);

	for (int i = 0; i < 10; ++i) {
//		int n = random_gen();
		int n = get_random(uniforme, 0, 150);
		printf("random number: %d\n", n);
		hashset_enter(&h, &n);
	}

	hashset_map(&h, print_int, NULL);
	hashset_dispose(&h);
}

int get_random(double (*generator_fun)(), int min, int max)
{
	double temp = generator_fun();

	return (min - 1) + ceil(temp*(max - min));
}
