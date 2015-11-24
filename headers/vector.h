#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "lecture_5.h"

/**
 * This data structure is done because an assignment of Paradigms of Computer
 * Programming from Stanford. The 'list' was created before, so this one is based
 * partially in that code.
 */

typedef int (*vector_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef void (*vector_map_fun)(void* elem_addr, const void* aux_data);
typedef void (*vector_free_fun)(void* elem_addr);

typedef struct
{
	int len;
	int allocat_len;
	int elem_size;
	void* elements;
	vector_free_fun free_fun;
} vector;

void vector_new(vector* v, int elem_size, vector_free_fun free_fun, int init_allocation);
void vector_dispose(vector* v);
int vector_len(vector* v);
void* vector_get(vector* v, int pos);
void vector_insert(vector* v, const void* elem_addr, int pos);
void vector_append(vector* v, const void* elem_addr);
void vector_replace(vector* v, const void* elem_addr, int pos);
void vector_delete(vector* v, int pos);
int vector_search(const vector* v, const void* key, vector_compare_fun search_fun, int start_idx, bool is_sorted);
void vector_sort(vector* v, vector_compare_fun compare_fun);
void vector_map(vector* v, vector_map_fun map_fn, const void* aux_data);


#endif
