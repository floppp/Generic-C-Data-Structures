#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct
{
	void* elements;
	int elem_size;
	int logical_len;
	int allocat_len;
	void (*free_function)(void*);
} stack;

void stack_new(stack*, int, void(*)(void*));
void stack_dispose(stack*);
void stack_push(stack*, void*);
void stack_pop(stack*, void*);

#endif
