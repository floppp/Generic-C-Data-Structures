#include "../headers/test_linked_list.h"


void test_linked_list_student()
{
	linked_list* list = linked_list_new();

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

		linked_list_add(list, Other, sizeof(students_group), &group_1, students_group_free, print_students);
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

		linked_list_add(list, Other, sizeof(students_group), &group_2, students_group_free, print_students);
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

		linked_list_add(list, Other, sizeof(students_group), &group_2, students_group_free, print_students);
	}

	int a = 775;
	linked_list_add(list, Integer, sizeof(int), &a, NULL, NULL);
	int c = 998;
	linked_list_add(list, Integer, sizeof(int), &c, NULL, NULL);
	int d = -1000;
	linked_list_add(list, Integer, sizeof(int), &d, NULL, NULL);
	char* e = "casa";
	linked_list_add(list, String, sizeof(char*), &e, NULL, NULL);

	printf("\n------------------------------\nPRINT LINKED LIST\n----------------------------\n\n");
	linked_list_print(list);

	linked_list_remove_node(list, 2);

	printf("\n------------------------------\nPRINT LINKED LIST\n----------------------------\n\n");
	linked_list_print(list);

	int x = 444;
	linked_list_add_at(list, 4, Integer, sizeof(int), &x, NULL, NULL);

	char o = 'o';
	linked_list_add_at(list, 3, Char, sizeof(char), &o, NULL, NULL);

	char* y = "eeee";
	linked_list_add_at(list, 1, String, sizeof(char*), &y, NULL, NULL);

	printf("\n------------------------------\nPRINT LINKED LIST\n----------------------------\n\n");
	linked_list_print(list);

//	char* h = "casa";
//	double j = 4.5;
//	char n = "a";
	int m = 444;
	int pos = linked_list_find(list, Integer, &m, NULL);
	printf("pos %d: %d\n", m, pos);

	linked_list_remove_node(list, 0);

	linked_list* string_list = linked_list_get_subtype(list, String);
	linked_list_print(string_list);

	linked_list_remove_list(list);
	linked_list_remove_list(string_list);
}

void test_linked_list()
{
	linked_list* list = linked_list_new();
	int a = 775;
	linked_list_add(list, Integer, sizeof(int), &a, NULL, NULL);
	int c = 998;
	linked_list_add(list, Integer, sizeof(int), &c, NULL, NULL);
	int d = -1000;
	linked_list_add(list, Integer, sizeof(int), &d, NULL, NULL);
	char* e = "casa";
	linked_list_add(list, String, sizeof(char*), &e, NULL, NULL);


	linked_list_print(list);
	linked_list_remove_node(list, 2);
	linked_list_print(list);

	int z = 111;
	linked_list_add_at(list, 0, Integer, sizeof(int), &z, NULL, NULL);
	linked_list_print(list);

	double l = 4.5;
	linked_list_add_at(list, 3, Double, sizeof(double), &l, NULL, NULL);
	linked_list_print(list);


	int x = 444;
	linked_list_add_at(list, 4, Integer, sizeof(int), &x, NULL, NULL);
	linked_list_print(list);

	char o = 'o';
	linked_list_add_at(list, 3, Char, sizeof(char), &o, NULL, NULL);
	linked_list_print(list);

	char* y = "eeee";
	linked_list_add_at(list, 2, String, sizeof(char*), &y, NULL, NULL);
	linked_list_print(list);

//	char* h = "casa";
//	double j = 4.5;
//	char n = "a";
	int m = 444;
	int pos = linked_list_find(list, Integer, &m, NULL);
	printf("pos %d: %d\n", m, pos);

	linked_list_remove_node(list, 0);
	linked_list_print(list);

	linked_list* string_list = linked_list_get_subtype(list, String);
	linked_list_print(string_list);

	linked_list_remove_node(list, 6);
	linked_list_print(list);

	linked_list_remove_list(list);
	linked_list_remove_list(string_list);
}
