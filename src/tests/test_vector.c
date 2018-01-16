#include "test_vector.h"
#define N_STU 3

vector int_v;
vector str_v;
vector stu_v;
short N_INT = 12;
short N_STR = 7;
int xs[] = { 1, 2, 3, 4, 2, 5, 6, 7, 1, 2, 3, 0};
const char* words[] = { "casa", "mar", "mesa", "ropa", "luz", "lampara",
						"fosforo" };
students_group groups[N_STU];

void test_vector_new()
{
	vector_new(&int_v, sizeof(int), NULL, 10);
	vector_new(&str_v, sizeof(char*), string_free, 10);
	vector_new(&stu_v, sizeof(students_group), students_group_free, 10);

	assert(int_v.len == 0);
	assert(int_v.all_len == 10);

	assert(str_v.len == 0);
	assert(str_v.all_len == 10);

	assert(stu_v.len == 0);
	assert(stu_v.all_len == 10);
}

void test_vector_append()
{
	for (short var = 0; var < N_INT; ++var) {
		vector_append(&int_v, &xs[var]);
	}

	for (short var = 0; var < N_STR; ++var)
		vector_append(&str_v, &words[var]);

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

	groups[1].elem = 6;
	const char* names_2[] = {"Lou", "David", "Steve", "Logan", "Popi", "Juno"};
	const int notas_2[] = {1, 2, 3, 2, 0, 2};

	groups[1].names = malloc(groups[1].elem * sizeof(char*));
	groups[1].cal = malloc(groups[1].elem * sizeof(int));

	for (int j = 0; j < groups[1].elem; ++j) {
		groups[1].names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[1].names[j], names_2[j]);
		groups[1].cal[j] = notas_2[j];
	}


	groups[2].elem = 6;
	const char* names_3[] = {"Juno", "Lola", "Bimba", "Lia", "Bimba",
							 "Nina"};
	const int notas_3[] = {1, 2, 3, 2, 0, 2};

	groups[2].names = malloc(groups[2].elem * sizeof(char*));
	groups[2].cal = malloc(groups[2].elem * sizeof(int));

	for (int j = 0; j < groups[2].elem; ++j) {
		groups[2].names[j] = malloc((strlen(names_3[j]) + 1)*sizeof(char));
		strcpy(groups[2].names[j], names_3[j]);
		groups[2].cal[j] = notas_3[j];
	}

	vector_append(&stu_v, &groups[0]);
	vector_append(&stu_v, &groups[1]);
	vector_append(&stu_v, &groups[2]);

	assert(int_v.len == 12);
	assert(int_v.all_len == 20);
	assert(str_v.len == 7);
	assert(str_v.all_len == 10);
	assert(stu_v.len == 3);
	assert(stu_v.all_len == 10);
}

void test_vector_len()
{
	assert(vector_len(&int_v) == 12);
	assert(vector_len(&str_v) == 7);
	assert(vector_len(&stu_v) == 3);
}

void test_vector_get()
{
	int n;
	for (short i = 0; i < N_INT; i++) {
		vector_get(&int_v, i, &n);
		assert(n == xs[i]);
	}

	const char* word;
	for (short i = 0; i < N_STR; ++i) {
		vector_get(&str_v, i, &word);
		assert(string_compare(word, words[i], strlen(word)));
	}

	students_group group;
	for (short i = 0; i < N_STU; ++i) {
		vector_get(&stu_v, i, &group);
		assert(students_compare(&stu_v, &groups[i]));
	}
}

void test_vector_dispose()
{
	// const char* word;
	// for (short i = 0; i < N_STR; ++i) {
		// vector_get(&str_v, i, &word);
		// printf("%s - %s\n", word, words[i]);
		// assert(string_compare(word, words[i], strlen(word)));
	// }
	// vector_dispose(&int_v);
	vector_dispose(&str_v);
	vector_dispose(&stu_v);

	// assert(int_v.elements == NULL);
	// assert(int_v.len == 0);
	// assert(int_v.all_len == 0);

	// assert(str_v.elements == NULL);
	// assert(str_v.len == 0);
	// assert(str_v.all_len == 0);

	// assert(stu_v.elements == NULL);
	// assert(stu_v.len == 0);
	// assert(stu_v.all_len == 0);
}

// {
// 	vector_map(&v, print_int, NULL);
// 	printf("\n");

// 	int x = *(int*) vector_get(&v, 0);
// 	printf("pos 0: %d\n", x);

// 	printf("vector len: %d\n", vector_len(&v));

// 	int ys[] = {-1, -2, -3, -4};
// 	for (int var = 0; var < 4; ++var)
// 		vector_insert(&v, &ys[var], var*2);

// 	printf("vector len: %d\n", vector_len(&v));
// 	vector_map(&v, print_int, &x);
// 	printf("\n");

// 	x = 9999;
// 	vector_replace(&v, &x, 5);
// 	vector_map(&v, print_int, &x);
// 	printf("\n");

// 	vector_delete(&v, 0);
// 	vector_delete(&v, v.len - 1);
// 	vector_map(&v, print_int, &x);
// 	printf("\n");

// 	int s = 7;
// 	int pos = vector_search(&v, &s, int_comparator, 0, false);
// 	printf("LINEAR SEARCH: elem %d is in position %d\n", s, pos);
// 	vector_sort(&v, int_comparator);
// 	vector_map(&v, print_int, &x);
// 	printf("\n");
// 	pos = vector_search(&v, &s, int_comparator, 0, true);
// 	printf("BINARY SEARCH AFTER QSORT: elem %d is in position %d\n", s, pos);


// 	vector_dispose(&v);
// }


void test_students_vector()
{
//	vector v;
//	vector_new(&v, sizeof(students_group), students_group_free, 4);
	vector* v = malloc(sizeof(vector));
	vector_new(v, sizeof(students_group), students_group_free, 4);

	// Add in 0
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"----", ",,,,", "....", "????", "++++", "===="};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

//		vector_insert(&v, &group_2, 0);
		vector_insert(v, &group_2, 0);
	}

//	vector_map(&v, print_students, NULL);
//	vector_delete(&v, 1);
	vector_map(v, print_students, NULL);
	vector_delete(v, 1);

	printf("\n---------\nerasing position 1\n----------\n\n");
//	vector_map(&v, print_students, NULL);
	vector_map(v, print_students, NULL);

//	 Replace 2
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

//		vector_replace(&v, &group_2, 2);
		vector_replace(v, &group_2, 2);
	}

	printf("\n---------\nreplacing position 2\n----------\n\n");
//	vector_map(&v, print_students, NULL);
	vector_map(v, print_students, NULL);

//	vector_dispose(&v);
	vector_dispose(v);
	free(v);
	v = NULL;
}

void vector_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  VECTOR TEST SUITE\n\t---------------------\n");

	launch_test(test_vector_new, "Vector creation --> OK");
	launch_test(test_vector_append, "Vector appending elements --> OK");
	launch_test(test_vector_len, "Vector length --> OK");
	launch_test(test_vector_get, "Vector get element --> OK");
	launch_test(test_vector_dispose, "Vector dispose --> OK");
}
