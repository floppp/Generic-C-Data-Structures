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
 * @brief Vector creation
 *
 * Vector creation
 *
 * @param v               memory position for the vector.
 * @param elem_size       size of elements we'll store
 * @param free_fun        function for deallocating elements.
 * @param init_allocation initial size we'll give to the vector.
 */
void vector_new(vector* v, int elem_size, vector_free_fun free_fun, int init_allocation);

/**
 * @brief Deallocation of vector.
 *
 * Deallocation of all the elements and memory used by the vector.
 *
 * @param v vector to deallocate.
 */
void vector_dispose(vector* v);

/**
 * Addition of elements to the end of the vector.
 *
 * @param v      vector where we are appending.
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
 * @brief Function that returns the element in an address we pass as a
 *        parameter.
 *
 * Function that makes a copy of the information that is stored in position
 * <b>pos</b> inside the vector <b>v</b>, in the memory <b>e_addr</b>. We must
 * ensure in the call moment the type of e_addr is the same the elements we
 * are storing in the vector.
 *
 * @param v   		vector we work in.
 * @param pos 		position of the element we want to return.
 * @param e_addr 	memory address where we'll copy the element in pos.
 */
void vector_get(vector* v, int pos, void* e_addr);

/**
 * @brief Inserting an element in an specific position.
 *
 * Function that inserts the content in the <b>e_addr</b> in the position
 * <b>pos</b> of the <b>v</b>, copying it. The <b>pos</b> must be between
 * 0 and v->len-1
 *
 * @param v      {vector*}     destination vector.
 * @param e_addr {const void*} memory direction of the element.
 * @param pos    {int{}        position where we want to insert.
 */
void vector_insert(vector* v, const void* e_addr, int pos);

/**
 * @brief Replacement of a vector element.
 *
 * Function that allow to replace the element <b>pos</pos> in <b>v</b> for the
 * element stored in the address <b>e_addr</b>. The original element can be
 * deallocated or not.
 *
 * @param v      {vector*} vector we are working with.
 * @param e_addr {void*}   memory direction of the new element.
 * @param pos    {int}     position we are goint to replace.
 * @param erase  {char}    deallocation flag, 1 for free, 0 not.
 */
void vector_replace(vector* v, const void* e_addr, int pos, char erase);

/**
 * @brief Deletion of vector element.
 *
 * Deletion and deallocation (if it must be) of the element in <b>pos</b>
 * in <b>v</b>.
 *
 * @param v   {vector*} vector we are working with.
 * @param pos {int}     position we want to erase.
 */
void vector_delete(vector* v, int pos);


/**
 * @brief Mapping values inside the vector.
 *
 * Function that apply <b>map_fn</b> to all values inside <b>v</b>, with
 * in-place modifications.
 *
 * @param v        {vector*}        vector we are working with.
 * @param map_fn   {vector_map_fun} function to apply on the elements.
 * @param aux_data {void*}          auxiliar data (NULL if don't needed).
 */
void vector_map(vector* v, vector_map_fun map_fn, const void* aux_data);

/**
 * @brief Searching elements inside the vector.
 *
 * Searching element <b>key</b> inside <b>v</b>, or inside the subvector
 * defined by <b>start_idx</b>. We must pass the comparator (<b>search_fun</b>)
 * and should specify if the vector <b>is_sorted</b> or not.
 *
 * @param v           {vector*} vector we are working with.
 * @param  key        {void*}   addres of the element to find.
 * @param  start_idx  {int}     index of the subvector, 0 in case we want
 *                              search in vector.
 * @param  is_sorted  {bool}    vector is sorted or not.
 * @param  search_fun {vectore_compare_fun} comparator function.
 *
 * @return            {int}                 position of the element in v.
 */
int vector_search(const vector* v, const void* key, vector_compare_fun search_fun, int start_idx, bool is_sorted);

/**
 * @brief
 *
 * [vector_sort description]
 *
 * @param v           [description]
 * @param compare_fun [description]
 */
void vector_sort(vector* v, vector_compare_fun compare_fun);

#endif
