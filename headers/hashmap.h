#ifndef HASHMAP_H_
#define HASHMAP_H_

/**
  * Vector over hashset because allows depencies reduction and easier implement compare
  * fun and free fun if we have full control on it, and not give full responsability
  * to hashset.
  */
#include "vector.h"

typedef enum KEY_TYPE { Number, Character, Word } key_type;
typedef int (*hashmap_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef int (*hashmap_hash_fun)(const void* elem_addr, int num_buckets);
typedef void (*hashmap_map_fun)(void* elem_addr, const void* aux_data);
typedef void (*hashmap_free_fun)(void* elem_addr);

typedef struct pair {
	void* key;
	void* value;
} pair;

typedef struct {
	key_type k_type;
	int num_buckets;
	vector* pairs;
	vector* used_buckets;
	hashmap_free_fun free_fun;
	hashmap_hash_fun hash_fun;
	hashmap_compare_fun compare_fun;
} hashmap;

void hashmap_new(hashmap* hm, int elem_size, int num_buckets, hashmap_hash_fun hash_fun, hashmap_compare_fun compare_fun, hashmap_free_fun free_fun, key_type type);
void hashmap_dispose(hashmap* hm);
int hashmap_count(hashmap* hm);
void hashmap_enter(hashmap* hm, void* key, void* value);
void* hashmap_get_value(const hashmap* hm, const void* key);
vector* hashmap_get_values(hashmap* hm);
void hashmap_map(hashmap* hm, hashmap_map_fun map_fun, const void* aux_data);
#endif
