#ifndef STUDENTS_UTILS_H
#define STUDENTS_UTILS_H

#include "hash_map.h"
#include "utils.h"

#define N_GROUPS 3

typedef struct students_group {
	char** names;
	int* cal;
	int elem;
} students_group;

void free_students(students_group *students, int *size);
int students_hash_fun(const void* elem_addres, int num_buckets);
void students_group_free(void* elem);
students_group** get_students(int *size);

/**
 * @brief Comparation between two students group.
 *
 * Comparation between two students group, where we are comparing between two
 * items.
 *
 * @param  elem_addr_1 first element to compare.
 * @param  elem_addr_2 second element to compare.
 *
 * @return             1 equal
 *                     0 otherwise
 */
int students_compare(const void* elem_addr_1, const void* elem_addr_2);


#endif
