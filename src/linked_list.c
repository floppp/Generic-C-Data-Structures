#include "../headers/linked_list.h"

static void print_node(node*);
static bool get_position(node*, node_type, void*, bool(*)(void*, void*));

/**
 * Creation of an empty linked list.
 *
 * @return Pointer to the linked list.
 */
linked_list* linked_list_new()
{
	linked_list* list = malloc(sizeof(linked_list));
	list->head = NULL;
	list->tail = NULL;
	list->logical_len = 0;

	assert(list != NULL);

	return list;
}

void linked_list_add(linked_list* l, node_type type, int elem_size, void* address, void(*free_fun)(void*), void(*print_fun)(void*))
{
	node* n;
	if (l->logical_len == 0) {
		n = node_new(type, elem_size, address, free_fun, print_fun);
		l->head = n;
		l->tail = n;
	} else {
		n = node_new(type, elem_size, address, free_fun, print_fun);
		node* current = l->head;

		for (int i = 0; i < l->logical_len-1; ++i)
			current = current->next;

		current->next = n;
		l->tail = n;
	}

	l->logical_len++;
}

void linked_list_add_at(linked_list *l, int pos, node_type type, int elem_size, void *address, void(*free_fun)(void*), void(*print_fun)(void*))
{
	if (pos <= l->logical_len) {
		l->logical_len++;
		node* n = node_new(type, elem_size, address, free_fun, print_fun);

		if (pos == 0) {
			n->next = l->head;
			l->head = n;
		} else if (pos < l->logical_len - 1) {
			node* current = l->head;
			node* prev;

			for (int i = 0; i < pos; ++i) {
				prev = current;
				current = current->next;
			}

			prev->next = n;
			n->next = current;
		} else {
			l->tail->next = n;
			l->tail = n;
		}
	}
}

void linked_list_get(linked_list* l, int pos, void* address)
{
	node* current = l->head;
	for (int i = 0; i < pos; ++i) {
		current = current->next;
	}

	memcpy(address, current->element, current->elem_size);
}

// do not reuse remove_node because performance issues
void linked_list_remove_list(linked_list *list)
{
	for (int i = 0; i < list->logical_len; ++i) {
		node* aux = list->head;

		if (aux->free_fun != NULL)
			aux->free_fun(aux->element);
		if (i < list->logical_len - 1)
			list->head = aux->next;

		free(aux->element);
		free(aux);
	}
	free(list);
}

void linked_list_remove_node(linked_list *l, int pos)
{
	if (pos < l->logical_len--) {
		node* current = l->head;
		node* prev;

		for (int i = 0; i < pos; ++i) {
			prev = current;
			current = current->next;
		}

		if (pos > 0 && pos < l->logical_len)
			prev->next = current->next;
		else if (pos == 0)
			l->head = current->next;
		else if (pos == l->logical_len)
			l->tail = prev;

		if (current->free_fun != NULL)
			current->free_fun(current->element);

		free(current->element);
		free(current);
	}
}

node* node_new(node_type t, int elem_size, void* address, void(*free_fun)(void*), void(*print_fun)(void*))
{
	node* n;
	n = malloc(sizeof(node));
	n->type = t;
	n->elem_size = elem_size;
	n->element = malloc(n->elem_size);
	n->free_fun = free_fun;
	n->print_fun = print_fun;
	memcpy(n->element, address, n->elem_size);

	return n;
}

void linked_list_print(linked_list *list)
{
	node* current = list->head;
	for (int i = 0; i < list->logical_len; ++i) {
		print_node(current);
		current = current->next;
	}
	printf("\n");
}

int linked_list_find(linked_list* list, node_type type, void* value, bool(*compare_fun)(void*, void*))
{
	node* current = list->head;

	for (int i = 0; i < list->logical_len; ++i) {
		if (get_position(current, type, value, compare_fun))
			return i;

		current = current->next;
	}

	return -1;
}

linked_list* linked_list_get_subtype(linked_list* origin, node_type type)
{
	node* current = origin->head;
	linked_list* copy = linked_list_new();

	for (int i = 0; i < origin->logical_len; ++i) {
		if (current->type == type)
			linked_list_add(copy, current->type, current->elem_size, current->element, current->free_fun, current->print_fun);
		current = current->next;
	}

	return copy;
}

static bool get_position(node* current, node_type type, void* value, bool(*compare_fun)(void*, void*))
{
	if (current->type == type) {
		switch (type) {
			case Integer:
				if (*(int*) current->element == *(int*) value)
					return true;
			break;
			case String:
				if (*(char**) current->element == *(char**) value)
					return true;
			break;
			case Char:
				if (*(char*) current->element == *(char*) value)
					return true;
			break;
			case Double:
				if (*(double*) current->element == *(double*) value)
					return true;
			break;
			case Other:
				return compare_fun == NULL ? false : compare_fun(current->element, value);
			break;
			case Boolean:
				break;
			case Nil:
				break;
		}
	}
	return false;
}

static void print_node(node* node)
{
	switch(node->type) {
		case Integer:
			printf("%d - ", *(int*) node->element); break;
		case String:
			printf("%s - ", *(char**) node->element); break;
		case Char:
			printf("%c - ", *(char*) node->element); break;
		case Double:
			printf("%lf - ", *(double*) node->element); break;
		case Other:
			node->print_fun(node->element); break;
		case Boolean:
			break;
		case Nil:
			 break;
	}
}
