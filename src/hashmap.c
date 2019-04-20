#include "../headers/hashmap.h"

#define SHIFT 6

// 64 buckets as default val.
static const uint32_t N_BUCKETS_DEFAULT = 1 << SHIFT;
static void hm_init(hash_map* hm,
					hm_compare_fun compare_fun,
                    hm_free_fun free_fun);

hash_map* hash_map_new(hm_compare_fun compare_fun, hm_free_fun free_fun)
{
	hash_map* hm = malloc(sizeof(hash_map));
	hm_init(hm, compare_fun, free_fun);

	return hm;
}

static void hm_init(hash_map* hm, hm_compare_fun compare_fun,
                    hm_free_fun free_fun)
{
	assert(compare_fun != NULL);

	hm->n_mask = N_BUCKETS_DEFAULT;
	hm->n_buckets_used = 0;

	// Allocation of memory for all the vectors we are going to use.
	if ((hm->pairs = malloc((hm->n_mask + 1) * sizeof(pair))) == NULL) {
		printf("memory allocation error in hm->pairs creation.\n");
		exit(0);
	}

	hm->compare_fun = compare_fun;
	hm->free_fun = free_fun;
}

long hash_map_put(hash_map* hm, void* key, void* value)
{
	int i = 0;
	int j = 0;

	while (i != hm->n_mask) {
		j = hash(key, i);
		if ()
	}
}

// returns new dictionary object
// function PyDict_New:
// 	    allocate new dictionary object
// 	    clear dictionary's table
// 	    set dictionary's number of used slots + dummy slots (ma_fill) to 0
// 	    set dictionary's number of active slots (ma_used) to 0
// 	    set dictionary's mask (ma_value) to dictionary size - 1 = 7
// 	    set dictionary's lookup function to lookdict_string
// 	    return allocated dictionary object
