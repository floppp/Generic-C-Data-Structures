#include "../headers/test_hashmap.h"


void print_node(void* elem_addr, const void* aux_data);


void test_int_hashmap()
{
	hashmap hm;
	hashmap_new(&hm, sizeof(char*), 20, hashmap_int_hash_fun, hashmap_int_compare_fun, NULL, Number);
	char* words[] = { "casa", "borde", "leche", "vaca", "mesa", "pila",
					  "solo", "pared", "luz", "television", "dvd", "pata",
					  "plato", "vinilo", "amplificador"};

	for (int i = 0; i < 15; ++i) {
		int n = get_random(uniforme, 0, 150);
		hashmap_enter(&hm, &n, words[i]);
	}

	const int k = 88;
	void* result = hashmap_get_value(&hm, &k);
	hashmap_map(&hm, hashmap_int_print_fun, NULL);

//	hashmap_dispose(&hs);
}


void print_node(void* elem_addr, const void* aux_data)
{
	hs_element* node = (struct hs_element*) elem_addr;
	printf("key: %d - value: %s\n", *(int*) node->key, (char*) node->value);
}
