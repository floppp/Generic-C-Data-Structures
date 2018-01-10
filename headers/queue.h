#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

/**
 * Struct for queue (FIFO) representation.
 *
 * 		elements	--> data storage.
 * 		elem_size	--> size of the element to store.
 * 		logical_len	--> number of stored elements.
 * 		allocat_len	--> size of the allocated memory for elements.
 * 		queue_pos	-->	position of the first element we'll retrieve.
 * 		last_pos	-->	last element in the queue.
 *
 */
typedef struct
{
	void* elements;
	int elem_size;
	int logical_len;
	int allocat_len;
	int queue_pos;
	int last_pos;
	void (*free_function)(void*);
} queue;

/**
 * Creation of auxiliary data structures for the queue.
 *
 * @param q					memory position of the queue.
 * @param e_size			size of the elements to store.
 * @param *free_function	function for deallocation elements.
 */
void queue_new(queue* q, int e_size, void(*free_function)(void*));

/**
 * Deallocation of all allocated memory used in the queue.
 *
 * @param q queue we want to deallocate.
 */
void queue_dispose(queue* s);

/**
 * Introduction of the element in e_addr in the last position of the queue.
 *
 * @param q      queue we are working in.
 * @param e_addr memory where the element to store is.
 */
void queue_enqueue(queue* q, void* e_addr);

/**
 * Retrieve of the first element of the queue (FIFO).
 * The implementation moves to pointers, so in case of huge queues, it is
 * possible to ask for positions outside the memory assigned for the process.
 * The correct solution, moving all elements when we ask for one, we'll be
 * slower but safer.
 *
 * I'M ACTUALLY NOT PRETTY SURE ABOUT THE TEXT ABOVE.
 *
 * @param q      queue we are working in.
 * @param e_addr memory address where we'll store the element to retrieve.
 */
void queue_dequeue(queue* q, void* e_addr);

#endif
