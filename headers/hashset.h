#ifndef HASHSET_H_
#define HASHSET_H_

#include "vector.h"

typedef int (*hashset_compare_fun)(const void* elem_addr_1, const void* elem_addr_2);
typedef int (*hashset_hash_fun)(const void* elem_addr, int num_buckets);
typedef void (*hashset_map_fun)(void* elem_addr, const void* aux_data);
typedef void (*hashset_free_fun)(void* elem_addr);

typedef struct {
	int elem_size;
	int alloc_size;
	int len;
	int num_buckets;
	void* elements;
	vector* used_buckets;
	hashset_free_fun free_fun;
	hashset_hash_fun hash_fun;
	hashset_compare_fun compare_fun;
} hashset;

void hashset_new(hashset*, int, int, hashset_hash_fun, hashset_compare_fun, hashset_free_fun);
void hashset_dispose(hashset*);
int hashset_count(hashset*);
void hashset_enter(hashset*, const void*);
void* hashset_lookup(const hashset*, const void*);
void hashset_map(hashset*, hashset_map_fun, const void*);

#endif
