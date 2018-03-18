#ifndef HASHMAP_H_
#define HASHMAP_H_

/**
  * Vector over hashset because allows depency reduction and an easier
  * implementation of compare and free fun if we have full control over it,
  * and not give full responsability to hashset.
  */
#include "vector.h"
#include "lookup3.h"

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

typedef int (*hm_compare_fun)(const void* e_addr_1, const void* e_addr_2);
typedef void (*hm_map_fun)(void* e_addr, const void* aux_data);
typedef void (*hm_free_fun)(void* e_addr);

typedef struct {
	key_type k_type; // We must put this again for simplicy.
	int n_buckets;   // the n_buckets are the elements the map will have.
	int value_size;
	vector* pairs; // here we are to store data. Each key will give us a hash
	               // value between 0 and n_buckets, and with this value the
	               // data will be stored in the right position.
	vector* used_buckets; // vector we are going to use for store the positions
	                      // already in use in the pairs vector.
	hm_free_fun free_fun;
	hm_compare_fun compare_fun;
} hashmap;


/**
 * @brief Hashmap allocation and creation.
 *
 * Function that allocates the memrory a hashmap needs, initialize the data
 * structures it needs, and returns a pointer to the allocated map.
 *
 * @param  e_size      size of the elements.
 * @param  n_buckets   number of elements buckets the map contains.
 * @param  compare_fun function to compare key values.
 * @param  free_fun    function for pair deallocation.
 * @param  type        type of the keys we are going to use.
 *
 * @return             pointer to the created hashmap.
 */
hashmap* hashmap_new(int e_size, hm_compare_fun compare_fun,
                     hm_free_fun free_fun, key_type type);

/**
 * @brief Hashmap dealloation.
 *
 * Hashmap dealloation.
 *
 * @param hm hashmap we want to deallocate.
 */
void hashmap_dispose(hashmap* hm);

/**
 * @brief Total number of elements in the map.
 *
 * Total number of elements that a map contains, computed with the sum of all
 * the elements for each key.
 *
 * @param  hm map we want to know the elements it contains.
 *
 * @return total number of elements in the map.
 */
int hashmap_count(hashmap* hm);

void hashmap_put(hashmap* hm, void* key, void* value);

/**
 * @brief Key associated pair getter.
 *
 * Function that returns the value associated with <b>key</b> from the <b>
 * hashmap</b> we are searching in. We must free the memory of the returned
 * pair, so we are not working directly with the memory inside the hashmap.
 *
 * Example:
 *
 *   pair* p = hashmap_get(hm, k);
 *   int a = v->value;
 *   printf("%d", a);
 *   free(p);
 *
 * If we free'd before using the value, maybe it will work maybe not, but of
 * course Valgring will compain.
 *
 * @param  hm  hashmap we are searching in.
 * @param  key key we are searching for.
 *
 * @return     pair containing the value we are searching for.
 */
pair* hashmap_get_pair(const hashmap* hm, const void* key);

/**
 * @brief Key associated pair getter.
 *
 * Function that returns a pointer in the right vector to the value associated
 * with <b>key</b> from the <b> hashmap</b> we are searching in, so we will
 * be working to the memory allocated inside the hashmap.
 * pair.
 *
 * @param  hm  hashmap we are searching in.
 * @param  key key we are searching for.
 *
 * @return     pair containing the value we are searching for.
 */
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
hashmap* hashmap_map(hashmap* hm, hm_map_fun map_fun, const void* aux_data);
#endif
