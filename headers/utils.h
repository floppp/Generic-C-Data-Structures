#ifndef UTILS_
#define UTILS_

#include <time.h>
#include <stdlib.h>
#include "students_group.h"
#include "list.h"

int random_gen();
void print_array(void* base, int n, int elem_size);
void string_free(void*);
void students_group_free(void*);
void list_print(list*);
char* get_format(list*);
int int_comparator(const void*, const void*);
int str_comparator(const void*, const void*);
int hash_fun(const void*, int);
void print_int(void* elem_addr, const void* aux_data);

#endif
