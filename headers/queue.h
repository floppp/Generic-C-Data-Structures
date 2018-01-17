#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

/**
 * @brief Generic Queue (FIFO).
 *
 * Generic Queue implemented with the classic two-stacks representation, the
 * first for queuing elements, the second one for dequeuing.
 *
 * @param fst_s    {stack} stack for queuing values. No pointers because of
 *                         instantiation problems. If we want ptr, we must use
 *                         same ideas than in linked_list
 * @param scd_s    {stack} stack for dequeuing values.
 * @param e_size   {int}   size of the elements to store.
 * @param len      {int}   number of elements actually stored in the queue.
 * @param a_len    {int}   space allocated in memory.
 * @param free_fun {void*} function for deallocating elements.
 */
typedef struct {
	stack* fst_s;
	stack* scd_s;
	int e_size;
	int len;
	int a_len;
	void (*free_fun)(void*);
} queue;

/**
 * @brief Creation of a queue.
 *
 * Creation of auxiliary data structures for the queue we are working with.
 *
 * @param q					memory position of the queue.
 * @param e_size			size of the elements to store.
 * @param *free_function	function for deallocation elements.
 */
void queue_new(queue* q, int e_size, void(*free_function)(void*));

/**
 * @brief Deallocation of all allocated memory used in the queue.
 *
 * Deallocation of the memory allocated in the stacks, their own dispose
 * methods are those that actually are freeing memory.
 *
 * @param q queue we want to deallocate.
 */
void queue_dispose(queue* s);

/**
 * @brief Adding an element at the end of the queue.
 *
 * Introduction of the element in e_addr in the last position of the
 * queue.
 *
 * @param q      queue we are working in.
 * @param e_addr memory where the element to store is.
 */
void queue_enqueue(queue* q, void* e_addr);

/**
 * @brief Getting the first element of the queue.
 *
 * Retrieve of the first element of the queue (FIFO), the function will store
 * this first element in e_addr direction.
 *
 * @param q      queue we are working in.
 * @param e_addr memory address where we'll store the element to retrieve.
 */
void queue_dequeue(queue* q, void* e_addr);

#endif
