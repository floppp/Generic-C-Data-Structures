#include "../headers/stack.h"

static void stack_grow(stack *s);
static void stack_decrease(stack* s);
const int ALLOCAT_DEFAULT_SIZE = 4;
const int LOGICAL_DEFAULT_SIZE = 0;

void stack_new(stack* s, int e_size, void(*free_function)(void*))
{
	assert(e_size > 0);

	s->elem_size = e_size;
	s->logical_len = LOGICAL_DEFAULT_SIZE;
	s->allocat_len = ALLOCAT_DEFAULT_SIZE;
	s->elements = malloc(s->allocat_len * e_size);
	s->free_function = free_function;

	assert(s->elements != NULL);
}

void stack_dispose(stack* s)
{
	if (s->free_function != NULL)
		for (short i = 0; i < s->logical_len; ++i)
			s->free_function((char*)s->elements + i*s->elem_size);

	s->logical_len = LOGICAL_DEFAULT_SIZE;
	s->allocat_len = 0;

	free(s->elements);
	s->elements = NULL;
}

void stack_pop(stack *s, void *e_addr)
{
	assert(s->logical_len > 0);

	void* source = (char*)s->elements + --s->logical_len*s->elem_size;
	memcpy(e_addr, source, s->elem_size);

	stack_decrease(s);
}

// if the struct we pass has pointer on it, we maybe need to change this method
// for copying the values; if we don't we will have problems in some
// tests (explained at the blog).
void stack_push(stack* s, void* e_addr)
{
	stack_grow(s);
	void* target = (char*) s->elements + s->logical_len*s->elem_size;
	memcpy(target, e_addr, s->elem_size);

	s->logical_len++;
}

/**
 * Auxiliary function to increase the memory allocated.
 *
 * @param s stack we want to increase.
 */
static void stack_grow(stack *s)
{
	if (s->logical_len == s->allocat_len) {
		s->allocat_len += ALLOCAT_DEFAULT_SIZE;
		s->elements = realloc(s->elements, s->allocat_len * s->elem_size);
	}
}

/**
 * Counterpart of the stack_grow, deallocation of the extra unused memory.
 *
 * @param s stack we want to reduce.
 */
static void stack_decrease(stack* s)
{
	if (s->allocat_len  == (s->logical_len + 6)) {
		s->allocat_len -= ALLOCAT_DEFAULT_SIZE;
		s->elements = realloc(s->elements, s->allocat_len * s->elem_size);
	}
}
