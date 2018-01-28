#include "../headers/linked_list.h"

static void print_node(node*);
static bool get_position(node*, node_type, void*, bool(*)(void*, void*));

linked_list* linked_list_new()
{
	linked_list* list = malloc(sizeof(linked_list));
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;

	assert(list != NULL);

	return list;
}

void linked_list_append(linked_list* l, node_type type, int e_size, void* address, void(*free_fun)(void*), void(*print_fun)(void*, const void*))
{
	node* n = node_new(type, address, free_fun, print_fun, e_size);
	linked_list_append_node(l, n);
}

void linked_list_append_node(linked_list* l, node* n)
{
	if (l->len == 0) {
		l->head = n;
		l->tail = n;
	} else {
		node* current = l->tail;
		current->next = n;
		n->prev = current;
		l->tail = n;

		// for (int i = 0; i < l->len-1; ++i)
		// 	current = current->next;

		// current->next = n;
		// n->prev = current;
		// l->tail = n;
	}

	l->len++;
}

void linked_list_add(linked_list *l, int pos, node_type type, int e_size, void *address, void(*free_fun)(void*),
	void(*print_fun)(void*, const void*))
{
	if (pos <= l->len) {
		l->len++;
		node* n = node_new(type, address, free_fun, print_fun, e_size);

		if (pos == 0) {
			n->next = l->head;
			l->head = n;
		} else if (pos < l->len - 1) {
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

	memcpy(address, current->element, current->e_size);
}

// do not reuse remove_node because performance issues
void linked_list_remove_list(linked_list *list)
{
	for (int i = 0; i < list->len; ++i) {
		node* aux = list->head;

		if (aux->free_fun != NULL)
			aux->free_fun(aux->element);
		if (i < list->len - 1)
			list->head = aux->next;

		free(aux->element);
		free(aux);
		aux = NULL;
	}
	free(list);
}

void linked_list_remove_node(linked_list *l, int pos)
{
	assert(pos < l->len);

	node* current = l->head;
	node* prev;

	for (int i = 0; i < pos; ++i) {
		prev = current;
		current = current->next;
	}

	if (pos > 0 && pos < l->len)
		prev->next = current->next;
	else if (pos == 0)
		l->head = current->next;
	else if (pos == l->len)
		l->tail = prev;

	node_free(current);

	l->len--;
}

void node_free(node* n)
{
	if (n->free_fun)
		n->free_fun(n->element);

	free(n->element);
	free(n);
	n = NULL;
}

node* node_new(node_type t, void* address, void(*free_fun)(void*), void(*print_fun)(void*, const void*), int e_size)
{
	node* n;
	n = malloc(sizeof(node));
	n->type = t;
	n->free_fun = free_fun;
	n->print_fun = print_fun;
	n->e_size = e_size;
	n->element = malloc(n->e_size);
	n->next = NULL;
	n->prev = NULL;

	memcpy(n->element, address, n->e_size);

	return n;
}

void linked_list_print(linked_list *list)
{
	node* current = list->head;
	const char* separation = " - ";
	for (int i = 0; i < list->len; ++i) {
		print_node(current);
		current = current->next;
		if (current)
			printf("%s", separation);
	}
	printf("\n");
}

int linked_list_find(linked_list* list, node_type type, void* value, bool(*compare_fun)(void*, void*))
{
	node* current = list->head;

	for (int i = 0; i < list->len; ++i) {
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

	for (int i = 0; i < origin->len; ++i) {
		if (current->type == type)
			linked_list_append(copy, current->type, current->e_size, current->element, current->free_fun, current->print_fun);
		current = current->next;
	}

	return copy;
}

static bool get_position(node* current, node_type type, void* value, bool(*compare_fun)(void*, void*))
{
	if (current->type == type) {
		switch (type) {
			case INTEGER:
				if (*(int*) current->element == *(int*) value)
					return true;
			break;
			case STRING:
				if (*(char**) current->element == *(char**) value)
					return true;
			break;
			case CHAR:
				if (*(char*) current->element == *(char*) value)
					return true;
			break;
			case DOUBLE:
				if (*(double*) current->element == *(double*) value)
					return true;
			break;
			case OTHER:
				return compare_fun == NULL ? false : compare_fun(current->element, value);
			break;
			case BOOLEAN:
				break;
			case NIL:
				break;
		}
	}
	return false;
}

static void print_node(node* node)
{
	switch(node->type) {
		case INTEGER:
			printf("%d", *(int*) node->element); break;
		case STRING:
			printf("%s", *(char**) node->element); break;
		case CHAR:
			printf("%c", *(char*) node->element); break;
		case DOUBLE:
			printf("%lf", *(double*) node->element); break;
		case OTHER:
			node->print_fun(node->element, NULL); break;
		case BOOLEAN:
			break;
		case NIL:
			 break;
	}
}
