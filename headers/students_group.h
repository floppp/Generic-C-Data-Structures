#ifndef STUDENTS_GROUP_
#define STUDENTS_GROUP_

#include <stdio.h>

typedef struct students_group {
	char** names;
	int* cal;
	int elem;
} students_group;

void print_students(void*);

#endif

