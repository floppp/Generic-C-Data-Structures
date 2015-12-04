#include "../headers/test_hashmap.h"

void print_node(void* elem_addr, const void* aux_data);
void free_fun(void*);

void test_int_hashmap()
{
	hashmap hm;
	hashmap_new(&hm, sizeof(char*), 20, hashmap_int_hash_fun, hashmap_int_compare_fun, free_fun, Number);
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

	hashmap_map(&hm, hashmap_int_print_pair, NULL);
	hashmap_dispose(&hm);
}

void free_fun(void* elem_address)
{

}

void print_node(void* elem_addr, const void* aux_data)
{
	pair* p = (struct pair*) elem_addr;
	printf("key: %d - value: %s\n", *(int*) p->key, (char*) p->value);
}
