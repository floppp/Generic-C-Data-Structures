#include "test_stack.h"

stack int_stack;
stack string_stack;

void test_stack_creation()
{
	stack_new(&int_stack, sizeof(int), NULL);

	assert(int_stack.logical_len == 0);
	assert(int_stack.allocat_len == 4);

	printf("Stack creation --> OK\n");
}

void test_adding_integers()
{
	int i = 2;
	stack_push(&int_stack, &i);

	assert(int_stack.logical_len == 1);

	i = 1;
	stack_push(&int_stack, &i);
	stack_push(&int_stack, &i);

	assert(int_stack.logical_len == 3);
	assert(int_stack.allocat_len == 4);

	printf("Adding integers to Stack --> OK\n");
}

void test_popping_integers()
{
	int i;

	assert(int_stack.logical_len == 3);

	stack_pop(&int_stack, &i);
	assert(i == 1 && int_stack.logical_len == 2);

	stack_pop(&int_stack, &i);
	assert(i == 1 && int_stack.logical_len == 1);

	stack_pop(&int_stack, &i);
	assert(i == 2 && int_stack.logical_len == 0);

	printf("Retriving integers from Stack --> OK\n");
}

void test_dispose_integer_stack()
{
	stack_dispose(&int_stack);

	assert(int_stack.elements == NULL);

	printf("Disposing elementary integers Stack --> OK\n");
}


void test_string_stack_creation_with_free_function()
{
	stack_new(&string_stack, (int) sizeof(char*), string_free);

	assert(string_stack.logical_len == 0);
	assert(string_stack.allocat_len == 4);

	printf("Stack of strings creation --> OK\n");
}

void test_adding_allocated_strings()
{
	int count = 0;
	const char* friends[] = {"Al", "Bob", "Carl", "John"};

	for (int i = 0; i < 4; ++i) {
		char* copy = strdup(friends[i]);
		stack_push(&string_stack, &copy);
		count += 1;
		assert(string_stack.logical_len == count);
	}

	assert(string_stack.logical_len == 4);
	assert(string_stack.allocat_len == 4);

	const char* words[] = {"casa", "mar", "mesa", "ropa", "luz", "lampara", "fosforo"};

	for (short i = 0; i < 7; ++i) {
		char* copy = strdup(words[i]);
		stack_push(&string_stack, &copy);
		count += 1;
		assert(string_stack.logical_len == count);
	}

	assert(string_stack.logical_len == 11);
	assert(string_stack.allocat_len == 12);

	printf("Adding strings to Stack --> OK\n");
}

void test_popping_strings()
{
	char* word;
	short idx = 0;
	const char* words[] = {	"fosforo", "lampara", "luz", "ropa", "mesa", "mar",
							"casa", "John", "Carl", "Bob", "Al"};

	for (short i = 0; i < 11; ++i) {
		stack_pop(&string_stack, &word);
		assert(string_compare(word, words[idx], strlen(word)));
		free(word);
		idx += 1;
	}

	assert(string_stack.allocat_len == 4 && string_stack.logical_len == 0);

	printf("Retriving strings from Stack --> OK\n");
}


void test_dispose_strings_stack()
{
	const char* friends[] = {"Al", "Bob", "Carl", "John", "Gregor"};

	for (int i = 0; i < 5; ++i) {
		char* copy = strdup(friends[i]);
		stack_push(&string_stack, &copy);
	}

	stack_dispose(&string_stack);

	assert(string_stack.elements == NULL);
	assert(string_stack.logical_len == 0);
	assert(string_stack.allocat_len == 4);

	printf("Disposing string Stack --> OK\n");
}

void stack_test_suite()
{
	printf("\t--------------------\n\t  STACK TEST SUITE\n\t--------------------\n");
	test_stack_creation();
	test_adding_integers();
	test_popping_integers();
	test_dispose_integer_stack();
	test_string_stack_creation_with_free_function();
	test_adding_allocated_strings();
	test_popping_strings();
	test_dispose_strings_stack();
}


// void test_stack_heap()
// {
// 	const char* friends[] = {"Al", "Bob", "Carl", "John"};
// 	stack string_stack;

// 	stack_new(&string_stack, (int)sizeof(char*), string_free);
// 	for (int i = 0; i < 4; ++i) {
// 		char* copy = strdup(friends[i]);
// 		stack_push(&string_stack, &copy);
// 	}

// 	const char* words[] = {"casa", "mar", "mesa", "ropa", "luz", "lampara", "fosforo"};

// 	for (int i = 0; i < 7; ++i) {
// 		char* copy = strdup(words[i]);
// 		stack_push(&string_stack, &copy);
// 	}

// 	char* word;
// 	for (int var = 0; var < 11; ++var) {
// 		stack_pop(&string_stack, &word);
// 		printf("%s\n", word);
// 		free(word);
// 	}

// 	stack_dispose(&string_stack);
// }

// void test_stack_students()
// {
// 	stack struct_stack;
// 	stack_new(&struct_stack, sizeof(students_group), students_group_free);

// 	{
// 		students_group group_1;
// 		group_1.elem = 4;


// 		char* names_1[] = {"Al", "Bob", "Carl", "John"};
// 		const int notas_1[] = {3, 4, 5, 3};

// 		group_1.names = malloc(group_1.elem * sizeof(char*));
// 		group_1.cal = malloc(group_1.elem * sizeof(int));

// 		for (int j = 0; j < group_1.elem; ++j) {
// 			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
// 			strcpy(group_1.names[j], names_1[j]);
// 			group_1.cal[j] = notas_1[j];
// 		}
// 		stack_push(&struct_stack, &group_1);
// 	}

// 	{
// 		students_group group_2;
// 		group_2.elem = 6;
// 		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
// 		const int notas_2[] = {1, 2, 3, 2, 0, 2};

// 		group_2.names = malloc(group_2.elem * sizeof(char*));
// 		group_2.cal = malloc(group_2.elem * sizeof(int));

// 		for (int j = 0; j < group_2.elem; ++j) {
// 			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
// 			strcpy(group_2.names[j], names_2[j]);
// 			group_2.cal[j] = notas_2[j];
// 		}

// 		stack_push(&struct_stack, &group_2);
// 	}
// 	students_group aux;
// 	stack_pop(&struct_stack, &aux);
// //	print_students(&aux);
// 	students_group_free(&aux);

// 	stack_pop(&struct_stack, &aux);
// 	students_group_free(&aux);

// 	{
// 		students_group group_2;
// 		group_2.elem = 6;
// 		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
// 		const int notas_2[] = {1, 2, 3, 2, 0, 2};

// 		group_2.names = malloc(group_2.elem * sizeof(char*));
// 		group_2.cal = malloc(group_2.elem * sizeof(int));

// 		for (int j = 0; j < group_2.elem; ++j) {
// 			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
// 			strcpy(group_2.names[j], names_2[j]);
// 			group_2.cal[j] = notas_2[j];
// 		}

// 		stack_push(&struct_stack, &group_2);
// 	}

// 	{
// 		students_group group_2;
// 		group_2.elem = 6;
// 		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
// 		const int notas_2[] = {1, 2, 3, 2, 0, 2};

// 		group_2.names = malloc(group_2.elem * sizeof(char*));
// 		group_2.cal = malloc(group_2.elem * sizeof(int));

// 		for (int j = 0; j < group_2.elem; ++j) {
// 			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
// 			strcpy(group_2.names[j], names_2[j]);
// 			group_2.cal[j] = notas_2[j];
// 		}

// 		stack_push(&struct_stack, &group_2);
// 	}

// 	stack_pop(&struct_stack, &aux);
// 	students_group_free(&aux);

// 	{
// 		students_group group_2;
// 		group_2.elem = 6;
// 		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
// 		const int notas_2[] = {1, 2, 3, 2, 0, 2};

// 		group_2.names = malloc(group_2.elem * sizeof(char*));
// 		group_2.cal = malloc(group_2.elem * sizeof(int));

// 		for (int j = 0; j < group_2.elem; ++j) {
// 			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
// 			strcpy(group_2.names[j], names_2[j]);
// 			group_2.cal[j] = notas_2[j];
// 		}

// 		stack_push(&struct_stack, &group_2);
// 	}

// 	{
// 		students_group group_2;
// 		group_2.elem = 6;
// 		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
// 		const int notas_2[] = {1, 2, 3, 2, 0, 2};

// 		group_2.names = malloc(group_2.elem * sizeof(char*));
// 		group_2.cal = malloc(group_2.elem * sizeof(int));

// 		for (int j = 0; j < group_2.elem; ++j) {
// 			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
// 			strcpy(group_2.names[j], names_2[j]);
// 			group_2.cal[j] = notas_2[j];
// 		}

// 		stack_push(&struct_stack, &group_2);
// 	}

// 	for (int i = 0; i < 3; ++i) {
// 		students_group aux;
// 		stack_pop(&struct_stack, &aux);
// 		print_students(&aux, NULL);
// 		students_group_free(&aux);
// 	}

// 	stack_dispose(&struct_stack);
// }
