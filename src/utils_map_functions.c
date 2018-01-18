#include "../headers/utils_map_functions.h"

void odd_numbers(void* e_addr, const void* aux_data)
{
	int* n = (int*) e_addr;
	int* m = malloc(sizeof(int));
	*m = *n % 2 != 0 ? *n : 0;
	memcpy(e_addr, m, sizeof(int));
	free(m);
}

void capitalize_word(void* e_addr, const void* aux_data)
{
	// char* s = (char*) e_addr;
	printf("%s - ", ((char*) e_addr));

	// c += 'A' - 'a';
}

void base_fail_grades(void* addr, const void* aux_data)
{
	students_group* students = (struct students_group*) addr;

	for (int i = 0; i < students->elem; ++i) {
		int n = students->cal[i];
		students->cal[i] = n > 2 ? 1 : 0;
	}
}

void print_students(void* addr, const void* aux_data)
{
	students_group* students = (struct students_group*) addr;

	for (int i = 0; i < students->elem; ++i) {
		printf("%s - ", students->names[i]);
		printf("%d\n", students->cal[i]);
	}
	printf("-------\n");
}