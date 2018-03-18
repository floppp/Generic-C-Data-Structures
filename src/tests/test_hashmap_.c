#include "test_hashmap.h"

hashmap* int_hm; // integer -> char*

void test_hashmap_new()
{
  int_hm = hashmap_new(sizeof(char*), hm_int_compare_fun, NULL, NUMBER);
}

void hashmap_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  HASHMAP TEST SUITE\n\t--------------------\n");

	launch_test(test_hashmap_new, "Hashmap new     --> OK");
}
