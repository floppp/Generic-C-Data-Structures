#include "../headers/vector.h"

static void vector_grow(vector*);
static void vector_decrease(vector *v);
static int vector_binary_search(const vector*, const void*, vector_compare_fun, int);
static int vector_linear_search(const vector*, const void*, vector_compare_fun, int);


void vector_new(vector *v, int elem_size, vector_free_fun free_fun, int init_allocation)
{
	if ((v->elements = malloc(init_allocation * elem_size)) == NULL) {
		printf("memory allocation error\n");
		return;
	}

	v->len = 0;
	v->allocat_len = init_allocation;
	v->elem_size = elem_size;
	v->free_fun = free_fun;
}

void vector_dispose(vector *v)
{
	if (v->free_fun != NULL)
		for (int var = 0; var < v->len; ++var)
			v->free_fun((char*) v->elements + var*v->elem_size);

	free(v->elements);
	v->elements = NULL;
}

int vector_len(vector *v)
{
	return v->len;
}

// Return a potiner to the vector storage. If we want return a copy, only need
// uncomment the lines commented -> in this case, we must free the returned element.
void* vector_get(vector *v, int pos)
{
	assert(v->len > 0 && pos < v->len);

	void* source = (char*) v->elements + pos*v->elem_size;
//	void* valu = malloc(v->elem_size);
//	memcpy(valu, source, v->elem_size);
//	return value;
	return source;

}

void vector_insert(vector* v, const void* elem_addr, int pos)
{
	assert(pos < v->len);

	for (int i = v->len; i > pos; --i) {
		void* next = (char*) v->elements + i*v->elem_size;
		void* prev = (char*) v->elements + (i - 1)*v->elem_size;

		memcpy(next, prev, v->elem_size);
	}

	void* target = (char*) v->elements + pos*v->elem_size;
	memcpy(target, elem_addr, v->elem_size);

	v->len++;
	vector_grow(v);
}

void vector_append(vector *v, const void *elem_addr)
{
	void* target = (char*) v->elements + v->len*v->elem_size;
	memcpy(target, elem_addr, v->elem_size);

	v->len++;
	vector_grow(v);
}

void vector_replace(vector *v, const void *elem_addr, int pos)
{
	assert(v->len > 0 && pos < v->len);

	void* target = (char*) v->elements + pos*v->elem_size;
	if (v->free_fun != NULL)
		v->free_fun(target);
	memcpy(target, elem_addr, v->elem_size);
}

void vector_delete(vector *v, int pos)
{
	assert(v->len > 0 && pos < v->len);

	if (v->free_fun != NULL)
		v->free_fun((char*) v->elements + pos*v->elem_size);

	for (int i = pos; i < v->len - 1; ++i) {
		void* prev = (char*) v->elements + i*v->elem_size;
		void* next = (char*) v->elements + (i + 1)*v->elem_size;
		memcpy(prev, next, v->elem_size);
	}

	v->len--;
	vector_decrease(v);
}

int vector_search(const vector *v, const void *key, vector_compare_fun search_fun, int start_idx, bool is_sorted)
{
	assert(start_idx >= 0 && start_idx < v->len);

	if (is_sorted)
		return vector_binary_search(v, key, search_fun, start_idx);
	else
		return vector_linear_search(v, key, search_fun, start_idx);
}

void vector_map(vector *v, vector_map_fun map_fn, const void *aux_data)
{
	for (int i = 0; i < v->len; ++i) {
		void* target = (char*) v->elements + i*v->elem_size;
		map_fn(target, aux_data);
	}
}

void vector_sort(vector *v, vector_compare_fun compare_fun)
{
	qsort(v->elements, v->len, v->elem_size, compare_fun);
}

static int vector_linear_search(const vector* v, const void* key, vector_compare_fun search_fun, int start_idx)
{
	for (int i = start_idx; i < v->len; ++i) {
		void* candidate = (char*) v->elements + i*v->elem_size;
		if (search_fun(candidate, key) == 0)
			return i;
	}

	return -1;
}

static int vector_binary_search(const vector* v, const void* key, vector_compare_fun search_fun, int start_idx)
{
	void* init = (char*) v->elements + start_idx*v->elem_size;
	void* res = bsearch(key, init, v->len, v->elem_size, search_fun);

	return res == NULL ? -1 : (res - init)/v->elem_size;
}

static void vector_decrease(vector *v)
{
	if (v->allocat_len == (v->len * 2)) {
		v->allocat_len = v->allocat_len / 3;
		v->elements = realloc(v->elements, v->allocat_len * v->elem_size);
	}
}

static void vector_grow(vector* v)
{
	if (v->len == v->allocat_len) {
		v->allocat_len *= 2;
		printf("vector size after grow: %d\n", v->len);
		v->elements = realloc(v->elements, v->allocat_len * v->elem_size);
	}
}
