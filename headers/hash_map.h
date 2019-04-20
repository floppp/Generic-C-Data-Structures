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

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash_utils.h"
#include "primes.h"

typedef struct hm_item {
  char* key;
  char* value;
} hm_item;

typedef void (*free_item)(hm_item* item);
typedef int (*hash_generator)(const char* s, const int a, const int m);
typedef int (*item_comparator)(hm_item* it_1, hm_item* it_2);

typedef struct hash_map {
  int size;
  int size_index;
  int count;
  hm_item** items;
  hash_generator hash_fun;
  free_item free_fun;
  item_comparator compare_fun;
} hash_map;

hash_map* hm_new(free_item free_it_fn, item_comparator comparator, hash_generator hash_fn);
void hash_map_dispose(hash_map* hm);
void hm_insert(hash_map* hm, const char* key, const char* value);
char* hm_search(hash_map* hm, const char* key);
void hm_delete(hash_map* hm, const char* key);

#endif  // HASH_TABLE_H_
