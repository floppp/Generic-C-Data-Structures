#include "../headers/test_hashmap.h"

void print_node(void* elem_addr, const void* aux_data);
void free_fun(void*);


void test_students_hashmap()
{

}

void test_int_hashmap()
{
	hashmap hm;
	hashmap_new(&hm, sizeof(char*), 20, hashmap_int_hash_fun, hashmap_int_compare_fun, NULL, Number);
	char* words[] = { "casa", "borde", "leche", "vaca", "mesa", "pila",
					  "solo", "pared", "luz", "television", "dvd", "pata",
					  "plato", "vinilo", "amplificador"};
	int numbers[15];

	for (int i = 0; i < 15; ++i) {
		int n = get_random(uniforme, 0, 150);
		numbers[i] = n;
		hashmap_enter(&hm, &numbers[i], words[i]);
	}
	printf("\n");

	int k = 88;
	char* word = (char*) hashmap_get_value(&hm, &k);
	printf("word with key 88 is %s\n", word);

	vector* res = hashmap_get_values(&hm);
	for (int i = 0; i < res->len; ++i) {
		char* w = (char*) res->elements + i*hm.value_size;
		printf("%s\n", w);
	}

	hashmap_map(&hm, hashmap_int_print_pair, NULL);
	vector_dispose(res);
	free(res);
	res = NULL;
	hashmap_dispose(&hm);
}

void print_node(void* elem_addr, const void* aux_data)
{
	pair* p = (struct pair*) elem_addr;
	printf("key: %d - value: %s\n", *(int*) p->key, *(char**) p->value);
}