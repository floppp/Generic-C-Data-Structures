#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "hashset.h"

typedef enum KEY_TYPE { Number, Character, Word } key_type;
typedef int (*hashmap_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef int (*hashmap_hash_fun)(const void* elem_addr, int num_buckets);
typedef void (*hashmap_map_fun)(void* elem_addr, const void* aux_data);
typedef void (*hashmap_free_fun)(void* elem_addr);

typedef struct hs_element {
	void* key;
	void* value;
} hs_element;

typedef struct {
	key_type k_type;
	hashset* pairs;
} hashmap;

void hashmap_new(hashmap* hm, int elem_size, int num_buckets, hashmap_hash_fun hash_fun, hashmap_compare_fun compare_fun, hashmap_free_fun free_fun, key_type type);
void hashmap_dispose(hashmap* hm);
int hashmap_count(hashmap* hm);
void hashmap_enter(hashmap* hm, void* key, void* value);
void* hashmap_get_value(const hashmap* hm, const void* key);
vector* hashmap_get_values(hashmap* hm);
void hashmap_map(hashmap* hm, hashmap_map_fun map_fun, const void* aux_data);
#endif
