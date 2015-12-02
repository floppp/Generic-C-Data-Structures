#include "../headers/hashset.h"
#include "../headers/utils.h"

static void* search_element(const vector* target, const void* elem_addr, hashset_compare_fun compare_fun);

void hashset_new(hashset *h, int elem_size, int num_buckets, hashset_hash_fun hash_fun, hashset_compare_fun compare_fun, hashset_free_fun free_fun)
{
	assert (elem_size > 0 || num_buckets > 0 || hash_fun != NULL || compare_fun != NULL);


	if ((h->elements = malloc(num_buckets * sizeof(vector))) == NULL) {
		printf("memory allocation error\n");
		exit(0) ;
	}

	for (int i = 0; i < num_buckets; ++i)
		vector_new(h->elements + i, elem_size, free_fun, 4);

	if ((h->used_buckets = malloc(sizeof(vector))) == NULL) {
		printf("memory allocation error\n");
		return ;
	}
	vector_new(h->used_buckets, sizeof(int), NULL, 4);

	h->elem_size = elem_size;
	h->num_buckets = num_buckets;
	h->compare_fun = compare_fun;
	h->free_fun = free_fun;
	h->hash_fun = hash_fun;
}

void hashset_dispose(hashset* h)
{
	for (int i = 0; i < h->num_buckets; ++i)
		vector_dispose(h->elements + i);

	vector_dispose(h->used_buckets);
	free(h->used_buckets);
	free(h->elements);
	h->used_buckets = NULL;
	h->elements = NULL;
}

int hashset_count(hashset* h)
{
	int len = 0;
	for (int i = 0; i < h->num_buckets; ++i)
		len += vector_len(h->elements + i);

	return len;
}

void hashset_enter(hashset* h, void* elem_addr)
{
	assert (elem_addr != NULL);
	int pos = h->hash_fun(elem_addr, h->num_buckets);
	assert (pos >= 0 && pos < h->num_buckets);
	vector* target = (struct vector*) (h->elements + pos);

	if (target->len == 0) {
		vector_append(target, elem_addr);
		vector_append(h->used_buckets, &pos);
	}
	else
// if we want to store sort elements in each vector because they will have a lot of collitions,
// we can use vector_sort and, in hashset_lookup -> search_element, make a binary search changing
// 'false' by 'true'.
// vector_sort(target, h->compare_fun);
		if (search_element(target, elem_addr, h->compare_fun) == NULL)
			vector_append(target, elem_addr);
		else
			h->free_fun(elem_addr);
}

void* hashset_lookup(const hashset* h, const void* elem_addr)
{
	int pos = h->hash_fun(elem_addr, h->num_buckets);
	vector* target = (struct vector*) (h->elements + pos);

	return search_element(target, elem_addr, h->compare_fun);
}

void hashset_map(hashset* h, hashset_map_fun map_fun, const void* aux_data)
{
	for (int i = 0; i < h->used_buckets->len; ++i) {
		int pos = *(int*) vector_get(h->used_buckets, i);
		vector* v_bucket = h->elements + pos;
		vector_map(v_bucket, map_fun, aux_data);
	}
	printf("\n");

}

static void* search_element(const vector* target, const void* elem_addr, hashset_compare_fun compare_fun)
{
	int exists = vector_search(target, elem_addr, compare_fun, 0, false);
	printf("%d", exists);
	return exists == -1 ? NULL : &exists;
}
