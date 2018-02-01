#ifndef HASHMAP_H_
#define HASHMAP_H_

/**
  * Vector over hashset because allows depency reduction and an easier
  * implementation of compare and free fun if we have full control over it,
  * and not give full responsability to hashset.
  */
#include "vector.h"


typedef enum KEY_TYPE { NUMBER, CHARACTER, WORD } key_type;

/**
 * Pair of elements, with the limitation that the key must be one of the types
 * defined in KEY_TYPE.
 */
typedef struct pair {
	key_type k_type;
	void* key;
	void* value;
} pair;

typedef int (*hashmap_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef unsigned long long (*hashmap_hash_fun)(const void* elem_addr, int num_buckets);
typedef void (*hashmap_map_fun)(void* elem_addr, const void* aux_data);
typedef void (*hashmap_free_fun)(void* elem_addr);

typedef struct {
	key_type k_type; // We must put this again for simplicy.
	int num_buckets;
	int value_size;
	vector* pairs;
	vector* used_buckets;
	hashmap_free_fun free_fun;
	hashmap_hash_fun hash_fun;
	hashmap_compare_fun compare_fun;
} hashmap;

/**
 * Function that creates a new hashmap
 */
void hashmap_new(hashmap* hm, int elem_size, int num_buckets, hashmap_hash_fun hash_fun, hashmap_compare_fun compare_fun, hashmap_free_fun free_fun, key_type type);
void hashmap_dispose(hashmap* hm);
int hashmap_count(hashmap* hm);
void hashmap_enter(hashmap* hm, void* key, void* value);
void* hashmap_get_value(const hashmap* hm, const void* key);

/**
 * @brief Function that gives us all the stored values.
 *
 * It's very important dealloc the memory returned from this method in the
 * calling one.
 *
 * @param hm Hashmap that stores the values we want.
 *
 * @return   Values stored in source hashmap.
 */
vector* hashmap_get_values(hashmap* hm);
void hashmap_map(hashmap* hm, hashmap_map_fun map_fun, const void* aux_data);
#endif
