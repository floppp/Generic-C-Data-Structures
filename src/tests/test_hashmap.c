#include "test_hashmap.h"

#define N_ELEMS 15
#define N_GROUPS 3

void print_node(void* elem_addr, const void* aux_data);
void free_fun(void*);

hashmap* int_hm;
hashmap* str_hm;
hashmap* stu_hm;
int numbers[N_ELEMS];
char* ws[N_ELEMS] = { "casa", "borde", "leche", "vaca", "mesa", "pila",
                       "solo", "pared", "luz", "television", "dvd", "pata",
                       "plato", "vinilo", "amplificador" };
students_group groups[N_GROUPS];

static void data_preparation()
{
	int n;
	for (short i = 0; i < 15; ++i) {
		n = get_random(uniforme, 0, 150);
		numbers[i] = n;
	}

	groups[0].elem = 4;

	char* names_1[] = {"Al", "Bob", "Carl", "John"};
	const int notas_1[] = {3, 4, 5, 3};

	groups[0].names = malloc(groups[0].elem * (sizeof(char*)+1));
	groups[0].cal = malloc(groups[0].elem * sizeof(int));

	for (int j = 0; j < groups[0].elem; ++j) {
		groups[0].names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
		strcpy(groups[0].names[j], names_1[j]);
		groups[0].cal[j] = notas_1[j];
	}

	// students_group group_2;
	groups[1].elem = 6;
	const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
	const int notas_2[] = {1, 2, 3, 2, 0, 2};

	groups[1].names = malloc(groups[1].elem * sizeof(char*));
	groups[1].cal = malloc(groups[1].elem * sizeof(int));

	for (int j = 0; j < groups[1].elem; ++j) {
		groups[1].names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[1].names[j], names_2[j]);
		groups[1].cal[j] = notas_2[j];
	}

	// students_group group_2;
	groups[2].elem = 6;
	const char* names_3[] = {"zzzzzz", "xxxxxx", "yyyyyy", "wwwwww", "uuuuuuu", "pppppp"};
	const int notas_3[] = {1, 2, 3, 2, 0, 2};

	groups[2].names = malloc(groups[2].elem * sizeof(char*));
	groups[2].cal = malloc(groups[2].elem * sizeof(int));

	for (int j = 0; j < groups[2].elem; ++j) {
		groups[2].names[j] = malloc((strlen(names_3[j]) + 1)*sizeof(char));
		strcpy(groups[2].names[j], names_3[j]);
		groups[2].cal[j] = notas_3[j];
	}
}

void test_hashmap_new()
{
	int_hm = hashmap_new(sizeof(char*), hm_int_compare_fun, NULL, NUMBER);
	stu_hm = hashmap_new(sizeof(students_group*), hm_stu_compare_fun,
	                     students_group_free, NUMBER);
}

void test_hashmap_put()
{
	for (short i = 0; i < N_ELEMS; ++i)
		hashmap_put(int_hm, &numbers[i], ws[i]);

	for (int i = 0; i < N_GROUPS; ++i)
		hashmap_put(stu_hm, &groups[i], &groups[i]);
}

void test_hashmap_get()
{
	char* w;
	for (short i = 0; i < N_ELEMS; ++i) {
		w       = hashmap_get_value(int_hm, &numbers[i]);
		pair* p = hashmap_get_pair(int_hm, &numbers[i]);
		assert(w == ws[i] && w == ((char*) p->value));
		free(p);
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
	hashmap_dispose(stu_hm);
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
