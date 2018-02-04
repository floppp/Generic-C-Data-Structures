#include "../headers/hashmap.h"

#define SHIFT 6

static const uint32_t N_BUCKETS_DEFAULT = 1 << SHIFT; // 64 buckets as default val.
static void hm_init(hashmap* hm, int e_size, hm_compare_fun compare_fun,
                    hm_free_fun free_fun, key_type type);
static size_t get_key_size(key_type t);
static pair* create_pair(key_type t, void* k, void* v);

hashmap* hashmap_new(int e_size, hm_compare_fun compare_fun,
                     hm_free_fun free_fun, key_type type)
{
	hashmap* hm = malloc(sizeof(hashmap));
	hm_init(hm, e_size, compare_fun, free_fun, type);

	return hm;
}

static void hm_init(hashmap* hm, int e_size, hm_compare_fun compare_fun,
                    hm_free_fun free_fun, key_type type)
{
	assert(e_size > 0 && compare_fun != NULL);

	hm->n_buckets = N_BUCKETS_DEFAULT;

	// Allocation of memory for all the vectors we are going to use.
	if ((hm->pairs = malloc((hm->n_buckets) * sizeof(vector))) == NULL) {
		printf("memory allocation error in hm->pairs creation.\n");
		exit(0);
	}

	// To each bucket we are going to create a vector for store all the
	// colisions we could have. Vector instead of Linked List because
	// of performance issues.
	for (int i = 0; i < hm->n_buckets; ++i)
		vector_new(hm->pairs + i, sizeof(pair), free_fun, 4);

	if ((hm->used_buckets = malloc(sizeof(vector))) == NULL) {
		printf("memory allocation error in hm->used_buckets creation.\n");
		return ;
	}
	vector_new(hm->used_buckets, sizeof(int), NULL, 4);

	hm->k_type = type;
	hm->pairs->elem_size = sizeof(vector);
	hm->compare_fun = compare_fun;
	hm->free_fun = free_fun;
	hm->value_size = e_size;
}

void hashmap_put(hashmap* hm, void* key, void* value)
{
	assert(hm && key && value);

	// we get the positions where the data will be stored.
	uint32_t pos = hashlittle(&key, get_key_size(hm->k_type), key);
	pos = (pos & hashmask(SHIFT));

	// printf("%u - %u\n", pos, N_BUCKETS_DEFAULT);

	assert(pos >= 0 && pos < hm->n_buckets);

	vector* target = (struct vector*) (hm->pairs + pos);

	pair* p = create_pair(hm->k_type, key, value);

	// Each branch for the case of collition, or not
	if (target == 0) {
		// We have a collition.
		vector_append(target, p);
		vector_append(hm->used_buckets, &pos);
	} else
		vector_append(target, p);

	if (hm->free_fun)
		hm->free_fun(p);

	free(p);
	p = NULL;
}

static pair* create_pair(key_type t, void* k, void* v)
{
	pair* p;
	if ((p = malloc(sizeof(pair))) == NULL) {
		printf("memory allocation error in pair creation.\n");
		exit(0);
	}

	p->k_type = t;
	p->key = k;
	p->value = v;

	return p;
}

void* hashmap_get(const hashmap* hm, const void* key)
{
	uint32_t pos = hashlittle(&key, get_key_size(hm->k_type), key);
	pos = (pos & hashmask(SHIFT));

	assert(pos >= 0 && pos < hm->n_buckets);

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

void hashmap_dispose(hashmap *hm)
{
	for (int i = 0; i < hm->n_buckets; ++i)
		vector_dispose(hm->pairs + i);

	vector_dispose(hm->used_buckets);
	free(hm->pairs);
	free(hm->used_buckets);
	hm->pairs = NULL;
	hm->used_buckets = NULL;
	free(hm);
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

static size_t get_key_size(key_type t)
{
	assert(t == NUMBER || t == CHARACTER || t == WORD);

	switch (t) {
		case    NUMBER: return sizeof(int);
		case      WORD: return sizeof(char*);
		case CHARACTER: return sizeof(char);
	}

	return -1;
}


// void hashmap_map(hashmap* hm, hm_map_fun map_fun, const void* aux_data)
// {
// 	int pos;
// 	for (int i = 0; i < hm->used_buckets->len; ++i) {
// 		vector_get(hm->used_buckets, i, &pos);
// 		printf("Position %d\n", pos);
// 		vector_map(hm->pairs + pos, map_fun, aux_data);
// 	}
// 	printf("\n");
// }



// vector* hashmap_get_values(hashmap* hm)
// {
// 	vector* target = malloc(sizeof(vector));
// 	vector_new(target, hm->value_size, hm->free_fun, hm->used_buckets->len);

// 	int pos;
// 	pair* p = malloc(sizeof(pair));
// 	for (int i = 0; i < hm->used_buckets->len; ++i) {
// 		vector_get(hm->used_buckets, i, &pos);
// 		vector* v = (struct vector*) (hm->pairs + pos);
// 		for (int j = 0; j < v->len; ++j) {
// 			vector_get(v, j, p);
// 			vector_append(target, p->value);
// 		}
// 	}

// 	return target;
// }
