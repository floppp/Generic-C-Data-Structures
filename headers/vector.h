#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef int (*vector_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef void (*vector_map_fun)(void* e_addr, const void* aux_data);
typedef void (*vector_free_fun)(void* e_addr);

/**
 * Struct for the vector:
 *
 * 	len --> elements in the vector
 * 	all_len --> memory allocated
 * 	elem_size --> size of the elements we'll store
 * 	elements --> memory where elements will be stored
 * 	free_fun --> function for elements memory deallocation
 */
typedef struct vector
{
	int len;
	int all_len;
	int elem_size;
	void* elements;
	vector_free_fun free_fun;
} vector;

/**
 * [vector_new description]
 * @param v               memory position for the vector.
 * @param elem_size       size of elements we'll store
 * @param free_fun        function for deallocating elements.
 * @param init_allocation initial size we'll give to the vector.
 */
void vector_new(vector* v, int elem_size, vector_free_fun free_fun, int init_allocation);

/**
 * Deallocation of all the elements and memory used by the vector.
 *
 * @param v vector to deallocate.
 */
void vector_dispose(vector* v);

/**
 * Addition of elements to the end of the vector.
 *
 * @param v         vector where we are appending.
 * @param e_addr memory direction of the element to add.
 */
void vector_append(vector* v, const void* e_addr);

/**
 * Getter that gives us the quantity of elements stored in the vector.
 *
 * @param  v vector we want to know the len.
 * @return   number of elements in the vector.
 */
int vector_len(vector* v);

/**
 * Function that returns the element in an address we pass as a parameter.
 *
 * @param v   		vector we work in.
 * @param pos 		position of the element we want to return.
 * @param e_addr 	position of the element we'll copy the element.
 */
void vector_get(vector* v, int pos, void* e_addr);

/**
 * [vector_insert description]
 * @param v         [description]
 * @param e_addr [description]
 * @param pos       [description]
 */
void vector_insert(vector* v, const void* e_addr, int pos);

/**
 * [vector_replace description]
 * @param v         [description]
 * @param e_addr [description]
 * @param pos       [description]
 */
void vector_replace(vector* v, const void* e_addr, int pos);

/**
 * [vector_delete description]
 * @param v   [description]
 * @param pos [description]
 */
void vector_delete(vector* v, int pos);

/**
 * [vector_search description]
 * @param  v          [description]
 * @param  key        [description]
 * @param  search_fun [description]
 * @param  start_idx  [description]
 * @param  is_sorted  [description]
 * @return            [description]
 */
int vector_search(const vector* v, const void* key, vector_compare_fun search_fun, int start_idx, bool is_sorted);

/**
 * [vector_sort description]
 * @param v           [description]
 * @param compare_fun [description]
 */
void vector_sort(vector* v, vector_compare_fun compare_fun);

/**
 * [vector_map description]
 * @param v        [description]
 * @param map_fn   [description]
 * @param aux_data [description]
 */
void vector_map(vector* v, vector_map_fun map_fn, const void* aux_data);

#endif
