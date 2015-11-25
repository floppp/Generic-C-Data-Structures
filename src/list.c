#include "../headers/list.h"

static void list_grow(list* l);
static void list_decrease(list* l);

void list_new(list *l, int e_size, void(*free_function)(void*))
{
	l->elem_size = e_size;
	l->logical_len = 0;
	l->allocat_len = 4;
	l->elements = malloc(l->allocat_len * l->elem_size);
	l->free_function = free_function;

	assert(l->elements != NULL);
}

void list_dispose(list* l)
{
	for (int i = 0; i < l->logical_len; ++i)
		if (l->free_function != NULL)
			l->free_function((char*) l->elements + i*l->elem_size);

	free(l->elements);
	l->elements = NULL;
}

void list_add(list *l, void *e_addr)
{
	list_grow(l);

	void* target = (char*) l->elements + l->logical_len*l->elem_size;
	memcpy(target, e_addr, l->elem_size);

	l->logical_len++;
}

void list_add_at(list *l, int pos, void *e_addr)
{
	list_grow(l);

	for (int i = l->logical_len; i > pos; --i) {
		void* next = (char*) l->elements + i*l->elem_size;
		void* prev = (char*) l->elements + (i - 1)*l->elem_size;

		memcpy(next, prev, l->elem_size);
	}

	void* target = (char*) l->elements + pos*l->elem_size;
	memcpy(target, e_addr, l->elem_size);

	l->logical_len++;
}

void list_get(list *l, int pos, void *e_addr)
{
	assert(l->logical_len > 0 && pos < l->logical_len);

	void* source = (char*) l->elements + pos*l->elem_size;
	memcpy(e_addr, source, l->elem_size);
}

void list_remove(list *l, int pos)
{
	if (l->free_function != NULL)
		l->free_function((char*) l->elements + pos*l->elem_size);

	for (int i = pos; i < l->logical_len - 1; ++i) {
		void* prev = (char*) l->elements + i*l->elem_size;
		void* next = (char*) l->elements + (i + 1)*l->elem_size;
		memcpy(prev, next, l->elem_size);
	}

	l->logical_len--;
	list_decrease(l);
}

static void list_decrease(list *l)
{
	if (l->allocat_len == (l->logical_len + 6)) {
		l->allocat_len -= 4;
		l->elements = realloc(l->elements, l->allocat_len * l->elem_size);
	}
}

static void list_grow(list* l)
{
	if (l->logical_len == l->allocat_len) {
		l->allocat_len += 4;
		l->elements = realloc(l->elements, l->allocat_len * l->elem_size);
	}
}
