#include "../headers/hash_map.h"

int tests_run = 0;

static hm_item HT_DELETED_ITEM = {NULL, NULL, -1};

/**
 * Method for creating a hash map item
 */
static hm_item* hm_new_item(const char* k, const void* v, size_t value_size)
{
	hm_item* it = malloc(sizeof(hm_item));
	it->key = strdup(k);
	it->value_size = value_size;
	it->value = malloc(value_size);
	memcpy(it->value, v, it->value_size);
	/* it->value = strdup(v); */

	return it;
}

/* static void hm_del_item(hm_item* i) */
/* { */
/*   free(i->key); */
/*   free((char*) i->value); */
/*   free(i); */
/* } */

static hash_map* hm_new_sized(const int size_index,
							  free_item free_it_fn,
							  key_comparator comparator,
							  hash_generator hash_fn)
{
	hash_map* hm = malloc(sizeof(hash_map));
	hm->size_index = size_index;

	const int base_size = 50 << hm->size_index;

	hm->size = next_prime(base_size);
	hm->count = 0;
	hm->items = calloc((size_t) hm->size, sizeof(hm_item*));
	hm->hash_fun = hash_fn;
	hm->free_fun = free_it_fn;
	hm->compare_fun = comparator;

	return hm;
}

hash_map* hm_new(free_item free_it_fn, key_comparator comparator, hash_generator hash_fn)
{
	return hm_new_sized(0, free_it_fn, comparator, hash_fn);
}

void hm_dispose(hash_map* hm)
{
	for (int i = 0; i < hm->size; i++) {
		hm_item* item = hm->items[i];
		if (item != NULL && item != &HT_DELETED_ITEM) {
			hm->free_fun(item);
		}
	}

	free(hm->items);
	free(hm);
}

static void hm_resize(hash_map* hm, const int direction)
{
	const int new_size_index = hm->size_index + direction;

	if (new_size_index < 0) return;

	hash_map* new_hm = hm_new_sized(new_size_index, NULL, NULL, NULL);

	for (int i = 0; i < hm->size; i++) {
		hm_item* item = hm->items[i];
		if (item != NULL && item != &HT_DELETED_ITEM) {
			hm_insert(new_hm, item->key, item->value, item->value_size);
		}
	}

	hm->size_index = new_hm->size_index;
	hm->count = new_hm->count;

	const int tmp_size = hm->size;
	hm->size = new_hm->size;
	new_hm->size = tmp_size;

	hm_item** tmp_items = hm->items;
	hm->items = new_hm->items;
	new_hm->items = tmp_items;

	hm_dispose(new_hm);
}

void hm_insert(hash_map* hm, const char* key, const void* value, size_t value_size)
{
	const int load = hm->count * 100 / hm->size;
	if (load > 70) {
		hm_resize(hm, 1);
	}

	hm_item* item = hm_new_item(key, value, value_size);

	int index = hm->hash_fun(item->key, hm->size, 0);
	hm_item* cur_item = hm->items[index];
	int i = 1;
	while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
		if (strcmp(cur_item->key, key) == 0) {
			hm->free_fun(cur_item);
			memcpy(hm->items[index], item, item->value_size);

			return;
		}
		index = hm->hash_fun(item->key, hm->size, i);
		cur_item = hm->items[index];
		i++;
	}

	hm->items[index] = item;
	hm->count++;
}

void* hm_search(hash_map* hm, const char* key)
{
	int index = hm->hash_fun(key, hm->size, 0);
	hm_item* item = hm->items[index];

	int i = 1;
	while (item != NULL && item != &HT_DELETED_ITEM) {
		if (strcmp(item->key, key) == 0) {
			return item->value;
		}
		index = hm->hash_fun(key, hm->size, i);
		item = hm->items[index];
		i++;
	}
	return NULL;
}

void hm_delete(hash_map* hm, const char* key)
{
	const int load = hm->count * 100 / hm->size;
	if (load < 10)
		hm_resize(hm, -1);

	int index = hm->hash_fun(key, hm->size, 0);
	hm_item* item = hm->items[index];

	int i = 1;
	while (item != NULL && item != &HT_DELETED_ITEM) {
		if (strcmp(item->key, key) == 0) {
			hm->free_fun(item);
			hm->items[index] = &HT_DELETED_ITEM;
		}
		index = hm->hash_fun(key, hm->size, i);
		item = hm->items[index];
		i++;
	}
	hm->count--;
}

/* int main() */
/* { */
/*   hash_map* ht = ht_new(); */

/*   printf("Number of elements before insert: %d (%d)\n", ht->count, ht->size); */
/*   ht_insert(ht, "a", "alce"); */

/*   for (short i = 0; i < ht->size; ++i) { */
/*     if (ht->items[i] != NULL) { */
/*       hm_item* current_item = ht->items[i]; */
/*       printf("Key [%s] has [%s] value\n", current_item->key, current_item->value); */
/*     } */
/*   } */
/*   printf("Number of elements after insert: %d (%d)\n", ht->count, ht->size); */

/*   ht_delete(ht, "a"); */

/*   char* value = hm_search(ht, "a"); */
/*   printf("Key [%s] has [%s] value\n", "a", value); */

/*   printf("Number of elements after delete: %d (%d)\n", ht->count, ht->size); */

/*   hash_map_dispose(ht); */

/*   /\* char* words[] = {"casa", "rezar", "alegre", "lola", "comedia", "espantapajaro", "abc", "asdf", "cajon"}; *\/ */
/*   /\* for (int i = 0; i < 9; ++i) { *\/ */
/*   /\*   printf("%d ", hm_hash(words[i], 19, 9)); *\/ */
/*   /\* } *\/ */

/*   return 0; */
/* } */
