#include "../headers/test_vector.h"

void test_students_vector()
{
//	vector v;
//	vector_new(&v, sizeof(students_group), students_group_free, 4);
	vector* v = malloc(sizeof(vector));
	vector_new(v, sizeof(students_group), students_group_free, 4);

	// Add in 0
	{
		students_group group_1;
		group_1.elem = 4;

		char* names_1[] = {"Al", "Bob", "Carl", "John"};
		const int notas_1[] = {3, 4, 5, 3};

		group_1.names = malloc(group_1.elem * (sizeof(char*)+1));
		group_1.cal = malloc(group_1.elem * sizeof(int));

		for (int j = 0; j < group_1.elem; ++j) {
			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
			strcpy(group_1.names[j], names_1[j]);
			group_1.cal[j] = notas_1[j];
		}

//		vector_append(&v, &group_1);
		vector_append(v, &group_1);
	}

	// Add in 1
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

//		vector_append(&v, &group_2);
		vector_append(v, &group_2);
	}

	// Add in 2
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"zzzzzz", "xxxxxx", "yyyyyy", "wwwwww", "uuuuuuu", "pppppp"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

//		vector_append(&v, &group_2);
		vector_append(v, &group_2);
	}

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


void test_int_vector()
{
	vector v;
	vector_new(&v, sizeof(int), NULL, 4);

	printf("vector len: %d\n", vector_len(&v));
	int xs[] = { 1, 2, 3, 4, 2, 5, 6, 7, 1, 2, 3, 0};
	for (int var = 0; var < 12; ++var)
		vector_append(&v, &xs[var]);
	vector_map(&v, print_int, NULL);
	printf("\n");

	int x = *(int*) vector_get(&v, 0);
	printf("pos 0: %d\n", x);

	printf("vector len: %d\n", vector_len(&v));

	int ys[] = {-1, -2, -3, -4};
	for (int var = 0; var < 4; ++var)
		vector_insert(&v, &ys[var], var*2);

	printf("vector len: %d\n", vector_len(&v));
	vector_map(&v, print_int, &x);
	printf("\n");

	x = 9999;
	vector_replace(&v, &x, 5);
	vector_map(&v, print_int, &x);
	printf("\n");

	vector_delete(&v, 0);
	vector_delete(&v, v.len - 1);
	vector_map(&v, print_int, &x);
	printf("\n");

	int s = 7;
	int pos = vector_search(&v, &s, int_comparator, 0, false);
	printf("LINEAR SEARCH: elem %d is in position %d\n", s, pos);
	vector_sort(&v, int_comparator);
	vector_map(&v, print_int, &x);
	printf("\n");
	pos = vector_search(&v, &s, int_comparator, 0, true);
	printf("BINARY SEARCH AFTER QSORT: elem %d is in position %d\n", s, pos);


	vector_dispose(&v);
}
