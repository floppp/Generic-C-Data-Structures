#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef enum TYPE { STRING, CHAR, INTEGER, DOUBLE, BOOLEAN, OTHER, NIL } node_type;

// typedef struct NODE node;
// typedef struct NODE {

/**
 * Struct to store a generic node.
 *
 * @param e_size     size of the element stored.
 * @param type       type of the node, from the enum TYPE.
 * @param *element   memory address where the data is stored.
 * @param *next      pointer to contiguous node.
 * @param *free_fun  function for memory deallocation.
 * @param *print_fun function for printing the node info.
 */
typedef struct node {
	int e_size;
	node_type type;
	void* element;
	struct node* next;
	void (*free_fun)(void*);
	void (*print_fun)(void*, const void*);
} node;

/**
 * Data structure for linked_list storage, with the number of elements actually
 * stored, and with a pair of pointers to the head and the tail of the list.
 *
 * @param len   elements in the list.
 * @param *head pointer to the first element of the list.
 * @param *tail pointer to the last element of the list.
 */
typedef struct linked_list {
	int len;
	struct node* head;
	struct node* tail;
} linked_list;

/**
 * @brief Creation of empty linked list.
 *
 * Creation of an empty linked list, with NULL head and tail.
 *
 * @return Pointer to the linked list.
 */
linked_list* linked_list_new();

/**
 * @brief Data addition at the end of a list.
 *
 * Node addition in the final position of a list. We must pass the
 * characteristics of the node, we cannot create the node in the outside
 * of this method and pass directly the node. Log(N).
 *
 * @param *l         list where we are adding.
 * @param type       type of the node.
 * @param e_size     size of the element added.
 * @param *address   memory address where is the info we want to add.
 * @param *free_fun  deallocating function.
 * @param *print_fun printing function.
 */
void linked_list_append(linked_list* l, node_type type, int e_size, void* address, void(*free_fun)(void*), void(*print_fun)(void*, const void*));

/**
 * @brief Node addition at the end of the list.
 *
 * Addition of nodes made outside this function. The node must be created
 * before calling this function, and they will be added at the end of the
 * list.
 *
 * @param *l list where we are adding.
 * @param *n node with the info we want to add.
 */
void linked_list_append_node(linked_list* l, node* n);

void linked_list_add(linked_list*, int, node_type, int, void*, void(*)(void*), void(*)(void*, const void*));
void linked_list_get(linked_list*, int, void*);
void linked_list_remove_list(linked_list*);
void linked_list_remove_node(linked_list*, int);
void linked_list_print(linked_list*);
int linked_list_find(linked_list*, node_type, void*, bool(*)(void*, void*));
linked_list* linked_list_get_subtype(linked_list*, node_type);

/**
 * @brief Node creation
 *
 * Node creation. The bits in address aren't copied to a new memory address,
 * but the address itself is copied, so we don't have to free the data after
 * inserted in a node. Any change made in the original data structured which
 * was pointing originally to address will modify the node.
 *
 * @param t          type of the node.
 * @param *address   memory address we want to store inside the node.
 * @param *free_fun  pointer to a function for deallocate memory.
 * @param *print_fun function for printing the info inside the node.
 * @param e_size     size of the element we'll store in the node. We use this
 *   parameter instead of a variadic function because it makes a lot easier the
 *   code for the list.
 *
 * @return the memory address where the node is allocated.
 */
node* node_new(node_type t, void* address, void(*free_fun)(void*), void(*print_fun)(void*, const void*), int e_size);

/**
 * @brief Node deallocation.
 *
 * Deallocation of the memory used by a node.
 *
 * @param *n pointer to node to deallocate.
 */
void node_free(node* n);

#endif
