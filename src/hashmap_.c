#include "../headers/headers_.h"

#define SHIFT 6

/* 64 buckets as default value */
static const uint32_t N_BUCKETS_DEFAULT = 1 << SHIFT;
static void hm_init(hashmap* hm, int size_e, hm_compare_fun cmp_fn, hm_free_fun free_fn, key_t t);

hashmap* hashmap_new(int size_e, hm_compare_fun compare_fun,
                     hm_free_fun free_fun, key_type type)
{
  hashmap* hm = malloc(sizeof(hashmap));
  hm_init(hm, size_e, compare_fun, free_fun, type);

  return hm;
}

static void hm_init(hashmap* hm, int size_e, hm_compare_fun cmp_fn, hm_free_fun free_fn, key_t t)
{
  assert(size_e > 0 && cmp_fn != NULL);

  hm->n_buckets = N_BUCKETS_DEFAULT;

  // Mem allocation for all vectors we're going to use.
  if ((hm->buckets = malloc((hm->n_buckets) * sizeof(vector))) == NULL) {
    printf("Memory allocation error in hm->pairs creation.\n");
    exit(-1);
  }

  // For each bucket, one vector for all collisions.
  for (int i = 0; i < hm->n_buckets; ++i)
    vector_new(hm->buckets+i, sizeof(pair), free_fn, 4);

  if ((hm->used_buckets = malloc(sizeof(vector))) == NULL) {
    printf("Memory allcoation error in hm->used_buckets creation.\n");
    exit(-1);
  }

  vector_new(hm->used_buckets, sizeof(int), NULL, 4);

  hm->k_t = t;
  hm->buckets->elem_size = sizeof(vector);
  hm->compare_fun = comp_fn;
  fm->free_fun = free_fn;
  hm->size_v = size_v;
}


