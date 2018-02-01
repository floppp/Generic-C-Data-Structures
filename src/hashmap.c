#include "../headers/hashmap.h"


void hashmap_new(hashmap* hm, int elem_size, int num_buckets,
                 hashmap_hash_fun hash_fun, hashmap_compare_fun compare_fun,
                 hashmap_free_fun free_fun, key_type type)
{
	assert(elem_size > 0 && num_buckets > 0 && hash_fun != NULL
	       && compare_fun != NULL);

	if ((hm->pairs = malloc((num_buckets + 1) * sizeof(vector))) == NULL) {
		printf("memory allocation error in hm->pairs creation.\n");
		exit(0);
	}

	// Problem with position initilization at 0, so i use a dirty solution,
	// added 1 in some places, but no in hm->num_buckets, for simpliest code.
	for (int i = 1; i < num_buckets + 1; ++i)
		vector_new(hm->pairs + i, sizeof(pair), free_fun, 4);

	if ((hm->used_buckets = malloc(sizeof(vector))) == NULL) {
		printf("memory allocation error in hm->used_buckets creation.\n");
		return ;
	}
	vector_new(hm->used_buckets, sizeof(int), NULL, 4);

	hm->k_type = type;
	hm->pairs->elem_size = sizeof(vector);
	hm->num_buckets = num_buckets;
	hm->compare_fun = compare_fun;
	hm->free_fun = free_fun;
	hm->hash_fun = hash_fun;
	hm->value_size = elem_size;
}

void hashmap_enter(hashmap *hm, void *key, void *value)
{
	assert (key != NULL && value != NULL);
	int pos = hm->hash_fun(key, hm->num_buckets) + 1;
	printf("%d\n", pos);
	assert (pos > 0 && pos <= hm->num_buckets);
	vector* target = (struct vector*) (hm->pairs + pos);

	pair* p;
	if ((p = malloc(sizeof(pair))) == NULL) {
		printf("memory allocation error in pair creation.\n");
		exit(0);
	}
	p->k_type = hm->k_type;
	p->key = key;
	p->value = value;

	if (target->len == 0) {
		vector_append(target, p);
		vector_append(hm->used_buckets, &pos);
	} else {
		int exists = vector_search(target, key, hm->compare_fun, 0, false);
		if (exists == -1) {
			vector_append(target, p);
		} else {
		    // This is not fine, key may not be an int.
			printf("The key %d already exists.\n", *(int*) p->key);
		}
	}
	if (hm->free_fun != NULL)
		hm->free_fun(p);
	free(p);
	p = NULL;
}

void hashmap_map(hashmap* hm, hashmap_map_fun map_fun, const void* aux_data)
{
	int pos;
	for (int i = 0; i < hm->used_buckets->len; ++i) {
		vector_get(hm->used_buckets, i, &pos);
		printf("Position %d\n", pos);
		vector_map(hm->pairs + pos, map_fun, aux_data);
	}
	printf("\n");
}

void* hashmap_get_value(const hashmap* hm, const void* key)
{
	int pos = hm->hash_fun(key, hm->num_buckets) + 1;
	vector* target = (struct vector*) (hm->pairs + pos);

	int pos_in_vector = vector_search(target, key, hm->compare_fun, 0, false);

	pair* temp;
	if ((temp = malloc(sizeof(pair))) == NULL) {
		printf("memory allocation error in pair creation.\n");
		exit(0);
	}
	vector_get(target, pos_in_vector, temp);

	return temp->value;
}

vector* hashmap_get_values(hashmap* hm)
{
	vector* target = malloc(sizeof(vector));
	vector_new(target, hm->value_size, hm->free_fun, hm->used_buckets->len);

	int pos;
	pair* p = malloc(sizeof(pair));
	for (int i = 0; i < hm->used_buckets->len; ++i) {
		vector_get(hm->used_buckets, i, &pos);
		vector* v = (struct vector*) (hm->pairs + pos);
		for (int j = 0; j < v->len; ++j) {
			vector_get(v, j, p);
			vector_append(target, p->value);
		}
	}

	return target;
}

void hashmap_dispose(hashmap *hm)
{
	for (int i = 1; i <= hm->num_buckets; ++i)
		vector_dispose(hm->pairs + i);

	vector_dispose(hm->used_buckets);
	free(hm->pairs);
	free(hm->used_buckets);
	hm->pairs = NULL;
	hm->used_buckets = NULL;
}

int hashmap_count(hashmap* hm)
{
	int len = 0;
	int pos;
	for (int i = 0; i < hm->used_buckets->len; ++i) {
		vector_get(hm->used_buckets, i, &pos);
		len += vector_len(hm->pairs + pos);
	}

	return len;
}
