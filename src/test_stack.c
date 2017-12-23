#include "../headers/test_stack.h"



void test_stack_heap()
{
	const char* friends[] = {"Al", "Bob", "Carl", "John"};
	stack string_stack;

	stack_new(&string_stack, (int)sizeof(char*), string_free);
	for (int i = 0; i < 4; ++i) {
		char* copy = strdup(friends[i]);
		stack_push(&string_stack, &copy);
	}

	const char* words[] = {"casa", "mar", "mesa", "ropa", "luz", "lampara", "fosforo"};

	for (int i = 0; i < 7; ++i) {
		char* copy = strdup(words[i]);
		stack_push(&string_stack, &copy);
	}

	char* word;
	for (int var = 0; var < 11; ++var) {
		stack_pop(&string_stack, &word);
		printf("%s\n", word);
		free(word);
	}

	stack_dispose(&string_stack);
}

void test_stack_students()
{
	stack struct_stack;
	stack_new(&struct_stack, sizeof(students_group), students_group_free);

	{
		students_group group_1;
		group_1.elem = 4;


		char* names_1[] = {"Al", "Bob", "Carl", "John"};
		const int notas_1[] = {3, 4, 5, 3};

		group_1.names = malloc(group_1.elem * sizeof(char*));
		group_1.cal = malloc(group_1.elem * sizeof(int));

		for (int j = 0; j < group_1.elem; ++j) {
			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
			strcpy(group_1.names[j], names_1[j]);
			group_1.cal[j] = notas_1[j];
		}
		stack_push(&struct_stack, &group_1);
	}

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

		stack_push(&struct_stack, &group_2);
	}
	students_group aux;
	stack_pop(&struct_stack, &aux);
//	print_students(&aux);
	students_group_free(&aux);

	stack_pop(&struct_stack, &aux);
	students_group_free(&aux);

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

		stack_push(&struct_stack, &group_2);
	}

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

		stack_push(&struct_stack, &group_2);
	}

	stack_pop(&struct_stack, &aux);
	students_group_free(&aux);

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

		stack_push(&struct_stack, &group_2);
	}

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

		stack_push(&struct_stack, &group_2);
	}

	for (int i = 0; i < 3; ++i) {
		students_group aux;
		stack_pop(&struct_stack, &aux);
		print_students(&aux, NULL);
		students_group_free(&aux);
	}

	stack_dispose(&struct_stack);
}
