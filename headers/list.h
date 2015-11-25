#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*
 * This structure should not be use. If you need a data structure with this array-like
 * implementation, use 'vector'. If you need linked-like implementation, use 'linked-list'.
 */

typedef struct
{
	void* elements;
	int elem_size;
	int logical_len;
	int allocat_len;
	void (*free_function)(void*);
} list;

void list_new(list* l, int e_size, void(*)(void*));
void list_dispose(list* l);
void list_add(list* l, void* e_addr);
void list_add_at(list* l, int pos, void* e_addr);
void list_get(list* l, int pos, void* e_addr);
void list_remove(list* l, int pos);


#endif
