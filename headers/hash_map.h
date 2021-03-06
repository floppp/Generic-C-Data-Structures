/**
 * This implemention is based in:
 *     https://github.com/jamesroutley/write-a-hash-table
 *
 * My own 100% couldn't be compared with it, so I decided to adapt
 * it and using it as a base. All credits for the real author.
 *
 * Both (mine and this one) follow the explanation in 'Introduction to
 * Algorithms' (Cormen, Leiserson and Rivest). If you need some extra
 * explanation you could find it there.
 */

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash_utils.h"
#include "primes.h"

typedef struct hm_item {
	char* key;
	void* value;
	size_t value_size;
} hm_item;


typedef void (*free_item)(hm_item* item);
typedef int (*hash_generator)(const char* s, const int a, const int m);
typedef int (*key_comparator)(const void* key_1, const void* key_2);
/* typedef int (*key_comparator)(const char* key_1, const char* key_2); */

typedef struct hash_map {
	int size;
	int size_index;
	int count;
	hm_item** items;
	hash_generator hash_fun;
	free_item free_fun;
	key_comparator compare_fun;
} hash_map;

hash_map* hm_new(free_item free_it_fn, key_comparator comparator, hash_generator hash_fn);
void hm_dispose(hash_map* hm);
void hm_insert(hash_map* hm, const char* key, const void* value, size_t value_size);
void* hm_search(hash_map* hm, const char* key);
void hm_delete(hash_map* hm, const char* key);

#endif  // HASH_TABLE_H_
