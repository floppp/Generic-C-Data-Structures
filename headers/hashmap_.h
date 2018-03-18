#ifndef HASHMAP__H_
#define HASHMAP__H_

#include "vector.h"
#include "lookup3.h"

typedef enum KEY_TYPE { NUMBER, CHARACTER, WORD } key_t;

typedef struct pair {
  void* k;
  void* v;
} pair;

typedef int (*hm_compare_fun)(const void* e_addr_1, const void* e_addr_2);
typedef void (*hm_map_fun)(void* e_addr, const void* aux_data);
typedef void (*hm_free_fun)(void* e_addr);
/**
 * @param n_buckets number of pairs the map will have.
 * @param size_v    size of the elements we're going to store.
 * @param buckets   vector for storing data, in each bucket we'll store all collitions for an specific hash.
 * @param used_buck vector to store the positions already in use in pairs vector.
 */
typedef struct {
  key_t k_t;
  int n_buckets;
  int size_v;
  vector* buckets;
  vector* used_buckets;
  hm_free_fun free_fun;
  hm_compare_fun compare_fun;
} hashmap;


/**
 * @brief Hashmap allocation and creation.
 *
 * Function that allocates the memory a hashmap needs, initialize the data
 * structures it needs, and returns a pointer to the allocated map.
 *
 * @param  size_e      size of the elements.
 * @param  n_buckets   number of elements buckets the map contains.
 * @param  compare_fun function to compare key values.
 * @param  free_fun    function for pair deallocation.
 * @param  type        type of the keys we are going to use.
 *
 * @return             pointer to the created hashmap.
 */
hashmap* hashmap_new(int size_e, hm_compare_fun compare_fun,
                     hm_free_fun free_fun, key_type type);


#endif
