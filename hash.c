#include "hash.h"

int tests_run = 0;

static int is_prime(const int x) {
  if (x < 2) { return -1; }
  if (x < 4) { return 1; }
  if ((x % 2) == 0) {
    return 0;
  }

  for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
    if ((x % i) == 0) {
      return 0;
    }
  }

  return 1;
}

static int next_prime(int x) {
  while (is_prime(x) != 1)
    x++;

  return x;
}

static ht_item HT_DELETED_ITEM = {NULL, NULL};
static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;

static ht_item* ht_new_item(const char* k, const char* v) {
  ht_item* i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);
  return i;
}

static void ht_del_item(ht_item* i) {
  free(i->key);
  free(i->value);
  free(i);
}

static ht_hash_table* ht_new_sized(const int size_index) {
  ht_hash_table* ht = malloc(sizeof(ht_hash_table));
  ht->size_index = size_index;

  const int base_size = 50 << ht->size_index;
  ht->size = next_prime(base_size);

  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
  return ht;
}

ht_hash_table* ht_new() {
  return ht_new_sized(0);
}

void ht_del_hash_table(ht_hash_table* ht) {

  for (int i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM) {
      ht_del_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

static void ht_resize(ht_hash_table* ht, const int direction) {
  const int new_size_index = ht->size_index + direction;
  if (new_size_index < 0) {
    return;
  }

  ht_hash_table* new_ht = ht_new_sized(new_size_index);

  for (int i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM) {
      ht_insert(new_ht, item->key, item->value);
    }
  }

  ht->size_index = new_ht->size_index;
  ht->count = new_ht->count;

  const int tmp_size = ht->size;
  ht->size = new_ht->size;
  new_ht->size = tmp_size;

  ht_item** tmp_items = ht->items;
  ht->items = new_ht->items;
  new_ht->items = tmp_items;

  ht_del_hash_table(new_ht);
}

static int ht_generic_hash(const char* s, const int a, const int m) {
  long hash = 0;
  const int len_s = strlen(s);
  for (int i = 0; i < len_s; i++) {
    hash += (long)pow(a, len_s - (i+1)) * s[i];
    hash = hash % m;
  }

  return (int)hash;
}


static int ht_hash(const char* s, const int num_buckets, const int attempt) {
  const int hash_a = ht_generic_hash(s, HT_PRIME_1, num_buckets);
  const int hash_b = ht_generic_hash(s, HT_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
  const int load = ht->count * 100 / ht->size;
  if (load > 70) {
    ht_resize(ht, 1);
  }
  ht_item* item = ht_new_item(key, value);

  int index = ht_hash(item->key, ht->size, 0);
  ht_item* cur_item = ht->items[index];
  int i = 1;
  while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
    if (strcmp(cur_item->key, key) == 0) {
      ht_del_item(cur_item);
      ht->items[index] = item;

      return;
    }
    index = ht_hash(item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }

  ht->items[index] = item;
  ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key) {
  int index = ht_hash(key, ht->size, 0);
  ht_item* item = ht->items[index];

  int i = 1;
  while (item != NULL && item != &HT_DELETED_ITEM) {
    if (strcmp(item->key, key) == 0) {
      return item->value;
    }
    index = ht_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }
  return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key) {
  const int load = ht->count * 100 / ht->size;
  if (load < 10) {
    ht_resize(ht, -1);
  }

  int index = ht_hash(key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;
  while (item != NULL && item != &HT_DELETED_ITEM) {
    if (strcmp(item->key, key) == 0) {
      ht_del_item(item);
      ht->items[index] = &HT_DELETED_ITEM;
    }
    index = ht_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }
  ht->count--;
}

int main()
{
  ht_hash_table* ht = ht_new();

  printf("Number of elements before insert: %d (%d)\n", ht->count, ht->size);
  ht_insert(ht, "a", "alce");

  for (short i = 0; i < ht->size; ++i) {
    if (ht->items[i] != NULL) {
      ht_item* current_item = ht->items[i];
      printf("Key [%s] has [%s] value\n", current_item->key, current_item->value);
    }
  }
  printf("Number of elements after insert: %d (%d)\n", ht->count, ht->size);

  ht_delete(ht, "a");

  char* value = ht_search(ht, "a");
  printf("Key [%s] has [%s] value\n", "a", value);

  printf("Number of elements after delete: %d (%d)\n", ht->count, ht->size);

  ht_del_hash_table(ht);

  /* char* words[] = {"casa", "rezar", "alegre", "lola", "comedia", "espantapajaro", "abc", "asdf", "cajon"}; */
  /* for (int i = 0; i < 9; ++i) { */
  /*   printf("%d ", ht_hash(words[i], 19, 9)); */
  /* } */

  return 0;
}
