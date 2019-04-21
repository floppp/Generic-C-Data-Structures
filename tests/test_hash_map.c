#include "test_hash_map.h"

static char* keys[] = { "casa", "mar", "mesa", "ropa", "luz",
						"lampara", "fosforo" };
static char* values[] = { "en", "un", "lugar", "de", "la", "mancha", "de" };

static void char_to_char_del_item(hm_item* i)
{
  free(i->key);
  free(i->value);
  free(i);
}

static void test_char_char_creation_insertion_searching_deletion()
{
	hash_map* hm = hm_new(char_to_char_del_item,
						  strcmp,
						  hm_double_hash);
	for (short i = 0; i < 7; i++) {
		assert(hm->count == i);
		hm_insert(hm, keys[i], values[i]);
		assert(hm->count == i + 1);
	}

	for (short i = 6; i >= 0; --i) {
		assert(hm->count == i + 1);
		assert(hm->compare_fun(hm_search(hm, keys[i]), values[i]) == 0);
		hm_delete(hm, keys[i]);
		assert(hm->count == i);
	}

	hm_dispose(hm);
}

void hm_test_suite()
{
	printf("\t--------------------\n\tHASHMAP TEST SUITE\n\t--------------------\n");

	launch_test(test_char_char_creation_insertion_searching_deletion,
				"HM [char* -> char*] creation & insertion --> OK");

}
