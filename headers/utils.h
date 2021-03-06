#ifndef UTILS_
#define UTILS_

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include "students_utils.h"

int random_gen();
void print_array(void* base, int n, int elem_size);
void string_free(void*);
void students_group_free(void*);
void list_print(list*);
char* get_format(list*);
int int_comparator(const void*, const void*);
int str_comparator(const void*, const void*);
int string_compare(const char* w1, const char* w2, int l);
void print_int(void* elem_addr, const void* aux_data);
void hm_int_print_pair(void* elem_addr, const void* aux_data);
int hm_int_compare_fun(const void*, const void*);
int get_random(double(*)(), int, int);
void launch_test(void(*f)(), const char* msg);

#endif
