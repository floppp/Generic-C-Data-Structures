#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

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
 Function to create a new quee
*/
void queue_new(queue* q, int e_size, void(*)(void*));
void queue_dispose(queue* s);
void queue_enqueue(queue* q, void* e_addr);
void queue_dequeue(queue* q, void* e_addr);

#endif
