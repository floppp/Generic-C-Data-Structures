#include "../headers/test_list.h"

void test_list_students()
{
	list l;
	list_new(&l, sizeof(students_group), students_group_free);

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

		list_add(&l, &group_1);
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

		list_add(&l, &group_2);
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

		list_add(&l, &group_2);
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

		list_add_at(&l, 0, &group_2);
//		list_add_at(&l, 1, &group_2);
//		list_add(&l, &group_2);
	}

	for (int i = 0; i < l.logical_len; ++i) {
		students_group temp1;
		list_get(&l, i, &temp1);
		print_students(&temp1, NULL);
	}

	list_remove(&l, 1);

	printf("\n---------\nerasing position 1\n----------\n\n");
	for (int i = 0; i < l.logical_len; ++i) {
		students_group temp1;
		list_get(&l, i, &temp1);
		print_students(&temp1, NULL);
	}

	// Add in 4
//	{
//		students_group group_2;
//		group_2.elem = 6;
//		const char* names_2[] = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF"};
//		const int notas_2[] = {1, 2, 3, 2, 0, 2};

//		group_2.names = malloc(group_2.elem * sizeof(char*));
//		group_2.cal = malloc(group_2.elem * sizeof(int));

//		for (int j = 0; j < group_2.elem; ++j) {
//			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
//			strcpy(group_2.names[j], names_2[j]);
//			group_2.cal[j] = notas_2[j];
//		}

//		list_add(&l, &group_2);
//	}

	list_dispose(&l);
}

void test_list()
{
	list l;
	list_new(&l, sizeof(int), NULL);

	int a = 4;
	list_add(&l, &a);
	a = 7;
	list_add(&l, &a);
	a = 9;
	list_add(&l, &a);
	a = -1;
	list_add(&l, &a);

	list_print(&l);
	a = 5;
	list_add_at(&l, 2, &a);

	list_print(&l);

	list_remove(&l, 1);
	list_print(&l);

	int c = 2;
	int pos = linear_search(&c, l.elements, l.logical_len, l.elem_size, int_comparator);
	printf("%d is in pos %d\n", c, pos);

	pos = linear_search(&a, l.elements, l.logical_len, l.elem_size, int_comparator);
	printf("%d is in pos %d\n", a, pos);

	list_dispose(&l);
}
