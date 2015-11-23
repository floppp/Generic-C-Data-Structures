#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef enum TYPE { String, Char, Integer, Double, Boolean, Other, Nil } node_type;

typedef struct NODE node;
struct NODE {
	int elem_size;
	node_type type;
	void* element;
	node* next;
	void (*free_fun)(void*);
	void (*print_fun)(void*);
};

typedef struct
{
	int logical_len;
	node* head;
	node* tail;
} linked_list;

linked_list* linked_list_new();
void linked_list_add(linked_list*, node_type, int, void*, void(*)(void*), void(*)());
void linked_list_add_at(linked_list*, int, node_type, int, void*, void(*)(void*), void(*)());
void linked_list_get(linked_list*, int, void*);
void linked_list_remove_list(linked_list*);
void linked_list_remove_node(linked_list*, int);
void linked_list_print(linked_list*);
int linked_list_find(linked_list*, node_type, void*, bool(*)(void*, void*));
node* node_new(node_type, int, void*, void(*)(void*), void(*)(void*));
linked_list* linked_list_get_subtype(linked_list*, node_type);

#endif

