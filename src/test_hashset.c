#include "../headers/test_hashset.h"

void test_int_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(int), 20, hash_fun, int_comparator, NULL);

	for (int i = 0; i < 10; ++i) {
		int n = random_gen();
		hashset_enter(&h, &n);
	}

	hashset_map(&h, print_int, NULL);
	hashset_dispose(&h);
}
