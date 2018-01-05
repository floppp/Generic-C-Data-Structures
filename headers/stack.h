#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 *  Struct that defines an stack. We can only pass single elements, or structs
 *  without pointers (memory allocated) in them.
 *
 * 		void* elements -> where data is store
 * 		elem_size -> size of the elements (all elements must be equal)
 * 		logical_len -> size that actually is store (number of elements)
 * 		allocat_len -> number of elements we can allocate
 * 		void (*free_function)(void*) -> for deallocating memory, only if we
 * 										need it
 *
 */
typedef struct
{
	void* elements;
	int elem_size;
	int logical_len;
	int allocat_len;
	void (*free_function)(void*);
} stack;

/**
 * Creation of a new stack.
 *
 * @param s					stack we want to initialize
 * @param e_size			size of elements
 * @param *free_function	function to deallocate elements. NULL if we don't
 *                       	need it
 */
void stack_new(stack* s, int e_size, void(*free_function)(void*));

/**
 * Deallocation of all allocated memory used in the stack.
 *
 * @param s stack we want to disponse.
 */
void stack_dispose(stack* s);

/**
 * Elements addition to the LIFO.
 *
 * @param s      stack we want to push in it.
 * @param e_addr pointer to the direction where are the elements to push.
 */
void stack_push(stack* s, void* e_addr);

/**
 * Function that copy in e_addr the firs element in the LIFO, and reduces it
 * in one element
 *
 * @param s      direction of the stack
 * @param e_addr direction where we want to copy the first element in the stack
 */
void stack_pop(stack* s, void* e_addr);

#endif
