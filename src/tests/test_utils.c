#include "test_utils.h"

void test_lookup3_hashlittle()
{
	// const int N_COUNT = 10;
	// unsigned long long r = 0;
	// for (int i = 0; i < N_COUNT; ++i) {
	// 	r = hash_fun(&r, N_COUNT);
	// 	// r = hash_fun(&r, N_COUNT);
	// 	printf("%p\n", (void*) r);
	// 	printf("%llu\n", r);
	// }
	uint32_t h;
	for (int i = 0; i < 10000; ++i) {
		h = hashlittle(&i, sizeof(int), i);
		h = (h & hashmask(6));
		if (h == 64 || h == 0)
			printf("%u - ", h);
	}
}

void utils_test()
{
	launch_test(test_lookup3_hashlittle, "hashlittle --> OK");
}
