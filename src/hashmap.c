#include "../headers/hashmap.h"


static int get_size(key_type);

void hashmap_new(hashmap* hm, int elem_size, int num_buckets, hashmap_hash_fun hash_fun, hashmap_compare_fun compare_fun, hashmap_free_fun free_fun, key_type type)
{
	assert(elem_size > 0 || num_buckets > 0 || hash_fun != NULL || compare_fun != NULL);

	hashset* hs = malloc(sizeof(hashset));
	hashset_new(hs, sizeof(hs_element), num_buckets, hash_fun, compare_fun, free_fun);

	hm->pairs = hs;
	hm->k_type = type;
}

void hashmap_dispose(hashmap* hm)
{
	hashset_dispose(hm->pairs);
}

int hashmap_count(hashmap *hm)
{
	return hashset_count(hm->pairs);
}

void hashmap_enter(hashmap* hm, void* key, void* value)
{
	hs_element* pair = malloc(sizeof(hs_element));
	pair->key = key;
	pair->value = value;
	hashset_enter(hm->pairs, pair);
}

static int get_size(key_type type)
{
	switch(type) {
		case Number: return 4;
		case Character: return 1;
	}
	return 0;
}

void* hashmap_get_value(const hashmap* hm, const void* key)
{
	int pos = hm->pairs->hash_fun(key, hm->pairs->num_buckets);
	vector* target = (struct vector*) (hm->pairs->elements + pos);
//	 vector* target = (struct vector*) vector_get(hm->pairs->elements, pos);

	int exists = vector_search(target, key, hm->pairs->compare_fun, 0, false);

	return exists == -1 ? NULL : &exists;
}

//vector* hashmap_get_values(hashmap *h)
//{
//	vector* v = malloc(sizeof(vector));
//	vector_new(v, h->value_size, h->free_fun, 4);

//	for (int i = 0; i < h->used_buckets->len; ++i) {
//		key_node* n = (struct key_node*) h->elements + i*sizeof(key_node);
//		vector_append(v, n->value);
//	}

//	return v;
//}

void hashmap_map(hashmap* hm, hashmap_map_fun map_fun, const void* aux_data)
{
	hashset_map(hm->pairs, map_fun, aux_data);
}
