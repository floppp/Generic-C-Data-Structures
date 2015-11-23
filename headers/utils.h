#ifndef UTILS_
#define UTILS_

#include <stdlib.h>
#include "students_group.h"
#include "list.h"

void print_array(void* base, int n, int elem_size);
void string_free(void*);
void students_group_free(void*);
void list_print(list*);
char* get_format(list*);


#endif
