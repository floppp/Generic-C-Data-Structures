#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

/**
 * @brief Generic Queue (FIFO).
 *
 * Generic Queue implemented with the classic two-stacks representation, the
 * first for queing elements, the second one for dequeing.
 *
 * @param fst_s    {stack} stack for enqueing values. No pointers because of
 *                         insantiation problems. If we want ptr, we must use
 *                         same ideas than in linked_list
 * @param scd_s    {stack} stack for dequeing values.
 * @param e_size   {int}   size of the elements to store.
 * @param len      {int}   number of elements actually stored in the queue.
 * @param a_len    {int}   space allocated in memory.
 * @param free_fun {void*} function for deallocating elements.
 */
typedef struct {
	stack fst_s;
	stack scd_s;
	int e_size;
	int len;
	int a_len;
	void (*free_fun)(void*);
} queue;

/**
 * @brief Creation of auxiliary data structures for the queue.
 *
 * @param q					memory position of the queue.
 * @param e_size			size of the elements to store.
 * @param *free_function	function for deallocation elements.
 */
void queue_new(queue* q, int e_size, void(*free_function)(void*));

/**
 * @brief Deallocation of all allocated memory used in the queue.
 *
 * @param q queue we want to deallocate.
 */
void queue_dispose(queue* s);

/**
 * @brief Introduction of the element in e_addr in the last position of the
 * queue.
 *
 * @param q      queue we are working in.
 * @param e_addr memory where the element to store is.
 */
void queue_enqueue(queue* q, void* e_addr);

/**
 * @brief Retrieve of the first element of the queue (FIFO).
 *
 * @param q      queue we are working in.
 * @param e_addr memory address where we'll store the element to retrieve.
 */
void queue_dequeue(queue* q, void* e_addr);

#endif
