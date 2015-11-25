#include "../headers/students_group.h"

void print_students(void* addr, const void* aux_data)
{
	students_group* students = (struct students_group*) addr;

	for (int i = 0; i < students->elem; ++i) {
		printf("%s - ", students->names[i]);
		printf("%d\n", students->cal[i]);
	}
	printf("-------\n");
}
