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

// ht_item is an item in the hash table
typedef struct ht_item {
    char* key;
    char* value;
} ht_item;


typedef struct {
    int size_index;
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table* ht);

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);

#endif  // HASH_TABLE_H_
