#include "test_hashmap.h"

#define N_ELEMS 15

void print_node(void* elem_addr, const void* aux_data);
void free_fun(void*);

hashmap* int_hm;
hashmap* str_hm;
hashmap* stu_hm;
int numbers[N_ELEMS];
char* ws[N_ELEMS] = { "casa", "borde", "leche", "vaca", "mesa", "pila",
                       "solo", "pared", "luz", "television", "dvd", "pata",
                       "plato", "vinilo", "amplificador" };

static void data_preparation()
{
	int n;
	for (short i = 0; i < 15; ++i) {
		n = get_random(uniforme, 0, 150);
		numbers[i] = n;
	}
}

void test_hashmap_new()
{
	int_hm = hashmap_new(sizeof(char*), hm_int_compare_fun, NULL, NUMBER);
	// stu_hm = hashmap_new(sizeof(students_group*), hm_stu_compare_fun,
	                     // students_group_free, NUMBER);
}

void test_hashmap_put()
{
	for (short i = 0; i < N_ELEMS; ++i)
		hashmap_put(int_hm, &numbers[i], ws[i]);
}

void test_hashmap_get()
{
	char* w;
	for (short i = 0; i < N_ELEMS; ++i) {
		w = hashmap_get(int_hm, &numbers[i]);
		assert(w == ws[i]);
	}
}

// void test()
// {
// 	int_hm = hashmap_new(sizeof(char*), 20, hashmap_long_hash_fun, hashmap_int_compare_fun, NULL, NUMBER);
// 	char* words[] = { "casa", "borde", "leche", "vaca", "mesa", "pila",
// 					  "solo", "pared", "luz", "television", "dvd", "pata",
// 					  "plato", "vinilo", "amplificador"};
// 	int numbers[15];

// 	for (int i = 0; i < 15; ++i) {
// 		int n = get_random(uniforme, 0, 150);
// 		numbers[i] = n;
// 		hashmap_enter(&hm, &numbers[i], words[i]);
// 	}
// 	printf("\n");

// 	int k = 88;
// 	char* word = (char*) hashmap_get_value(&hm, &k);
// 	printf("word with key 88 is %s\n", word);

// 	vector* res = hashmap_get_values(&hm);
// 	for (int i = 0; i < res->len; ++i) {
// 		char* w = (char*) res->elements + i*hm.value_size;
// 		printf("%s\n", w);
// 	}

// 	hashmap_map(&hm, hashmap_int_print_pair, NULL);
// 	vector_dispose(res);
// 	free(res);
// 	res = NULL;
// 	hashmap_dispose(&hm);
// }

void print_node(void* elem_addr, const void* aux_data)
{
	pair* p = (struct pair*) elem_addr;
	printf("key: %d - value: %s\n", *(int*) p->key, *(char**) p->value);
}

void data_dispose()
{
	hashmap_dispose(int_hm);
	// hashmap_dispose(stu_hm);
}

void hashmap_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  HASHMAP TEST SUITE\n\t--------------------\n");

	data_preparation();

	launch_test(test_hashmap_new, "Hashmap new     --> OK");
	launch_test(test_hashmap_put, "Hashmap put     --> OK");
	launch_test(test_hashmap_get, "Hashmap get     --> OK");

	data_dispose();
}
