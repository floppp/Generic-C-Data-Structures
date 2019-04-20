#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "lookup3.h"

typedef struct pair {
	void* key;
	void* value;
} pair;

typedef int  (*hm_compare_fun)(const void* e_addr_1, const void* e_addr_2);
typedef void (*hm_map_fun)(void* e_addr, const void* aux_data);
typedef void (*hm_free_fun)(void* e_addr);

typedef struct hash_map {
	int n_mask;
	int n_buckets_used;
	pair* pairs;
	hm_free_fun free_fun;
	hm_compare_fun compare_fun;
} hash_map;


hash_map* hash_map_new(hm_compare_fun compare_fun, hm_free_fun free_fun);
long hash_map_put(hash_map hm, void* key, void* value);

#endif
