#ifndef UTILS_
#define UTILS_

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

typedef struct students_group {
	char** names;
	int* cal;
	int elem;
} students_group;

int random_gen();
void print_array(void* base, int n, int elem_size);
void string_free(void*);
void students_group_free(void*);
void list_print(list*);
char* get_format(list*);
int int_comparator(const void*, const void*);
int str_comparator(const void*, const void*);
int string_compare(const char* w1, const char* w2, int l);
// int students_hash_fun(const void*, int);
int students_compare(const void*, const void*);
void print_int(void* elem_addr, const void* aux_data);
void hm_int_print_pair(void* elem_addr, const void* aux_data);
int hm_int_compare_fun(const void*, const void*);

/**
 * @brief Comparation between two students group.
 *
 * Comparation between two students group, where we are comparing between a
 * pair (<b>elem_addr1</b>), and a simple direction (<b>elem_addr_2</b>).
 *
 * @param  elem_addr_1 first element to compare.
 * @param  elem_addr_2 second element to compare.
 *
 * @return             1 equal
 *                     0 otherwise
 */
int hm_stu_compare_fun(const void* elem_addr_1, const void* elem_addr_2);
int get_random(double(*)(), int, int);
void launch_test(void(*f)(), const char* msg);

#endif
