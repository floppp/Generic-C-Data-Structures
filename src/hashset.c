#include "../headers/hashset.h"

void hashset_new(hashset *h, int elem_size, int num_buckets, hashset_hash_fun hash_fun, hashset_compare_fun compare_fun, hashset_free_fun free_fun)
{
	assert (elem_size > 0 || num_buckets > 0 || hash_fun != NULL || compare_fun != NULL);


	if ((h->elements = malloc(num_buckets * elem_size)) == NULL) {
		printf("memory allocation error\n");
		return ;
	}

	vector* v1 = malloc(sizeof(vector));
	vector_new(v1, elem_size, NULL, 4);
	vector* v2 = malloc(sizeof(vector));
	vector_new(v2, elem_size, free_fun, 4);

	h->len = 0;
	h->elem_size = elem_size;
	h->num_buckets = num_buckets;
	h->compare_fun = compare_fun;
	h->free_fun = free_fun;
	h->hash_fun = hash_fun;
	h->used_buckets = v1;
	h->collitions = v2;
}

void hashset_dispose(hashset* h)
{
	if (h->free_fun != NULL) {
		for (int i = 0; i < h->num_buckets; ++i)
			h->free_fun((char*) h->elements + i*h->elem_size);
		vector_dispose(h->collitions);
	}


	free(h->collitions->elements);
	h->collitions->elements = NULL;
	free(h->collitions);

	free(h->used_buckets->elements);
	h->used_buckets->elements = NULL;
	free(h->used_buckets);

	free(h->elements);

	h->used_buckets = NULL;
	h->collitions = NULL;
	h->elements = NULL;
}

int hashset_count(hashset* h)
{
	return h->len;
}

void hashset_enter(hashset* h, const void* elem_addr)
{
	assert (elem_addr != NULL);

	int pos = h->hash_fun(elem_addr, h->num_buckets);
	printf("%d\n", pos);
	assert (pos >= 0 && pos < h->num_buckets);

	void* target = (char*) h->elements + pos*h->elem_size;

	if (h->compare_fun(target, elem_addr) == 0) {
		vector_append(h->collitions, elem_addr);

	} else {
		h->len++;
		vector_append(h->used_buckets, target);
	}

//	printf("n_coll: %d - n_elem: %d\n", h->collitions->len, h->used_buckets->len);
	// The implementation replace elements that has same hash_fun
	memcpy(target, elem_addr, h->elem_size);

}

void* hashset_lookup(const hashset* h, const void* elem_addr)
{
	int pos = h->hash_fun(elem_addr, h->num_buckets);
	void* target = (char*) h->elements + pos*h->elem_size;

	if (h->compare_fun(target, elem_addr) == 0)
		return target;
	else
		return NULL;
}

void hashset_map(hashset* h, hashset_map_fun map_fun, const void* aux_data)
{
	for (int i = 0; i < h->len; ++i) {
		int vector_pos = *(int*) vector_get(h->used_buckets, i);
		void* target = (char*) h->elements + vector_pos*h->elem_size;
		map_fun(target, aux_data);
	}
}
