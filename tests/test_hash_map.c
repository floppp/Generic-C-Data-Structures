#include "test_hash_map.h"

students_group groups[N_GROUPS];

static void data_preparation()
{
	// students_group group_1;
	groups[0].elem = 4;

	char* names_1[] = {"Al", "Bob", "Carl", "John"};
	const int notas_1[] = {3, 4, 5, 3};

	groups[0].names = malloc(groups[0].elem * (sizeof(char*)+1));
	groups[0].cal = malloc(groups[0].elem * sizeof(int));

	for (int j = 0; j < groups[0].elem; ++j) {
		groups[0].names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
		strcpy(groups[0].names[j], names_1[j]);
		groups[0].cal[j] = notas_1[j];
	}

	// students_group group_2;
	groups[1].elem = 6;
	const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
	const int notas_2[] = {1, 2, 3, 2, 0, 2};

	groups[1].names = malloc(groups[1].elem * sizeof(char*));
	groups[1].cal = malloc(groups[1].elem * sizeof(int));

	for (int j = 0; j < groups[1].elem; ++j) {
		groups[1].names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[1].names[j], names_2[j]);
		groups[1].cal[j] = notas_2[j];
	}

	// students_group group_2;
	groups[2].elem = 6;
	const char* names_3[] = {"zzzzzz", "xxxxxx", "yyyyyy", "wwwwww", "uuuuuuu", "pppppp"};
	const int notas_3[] = {1, 2, 3, 2, 0, 2};

	groups[2].names = malloc(groups[2].elem * sizeof(char*));
	groups[2].cal = malloc(groups[2].elem * sizeof(int));

	for (int j = 0; j < groups[2].elem; ++j) {
		groups[2].names[j] = malloc((strlen(names_3[j]) + 1)*sizeof(char));
		strcpy(groups[2].names[j], names_3[j]);
		groups[2].cal[j] = notas_3[j];
	}

}

static char* keys[] = { "casa", "mar", "mesa", "ropa", "luz",
						"lampara", "fosforo" };
static char* values[] = { "en", "un", "lugar", "de", "la", "mancha", "de" };

static void char_to_char_del_item(hm_item* i)
{
  free(i->key);
  free((char*) i->value);
  free(i);
}

static void string_to_student_del_item(hm_item* i)
{
	free(i->key);
	students_group_free(i->value);
	free(i);
}
void print_students_group(students_group *group)
{
	printf("%d\n", group->elem);
	for (int i = 0; i < group->elem; i++) {
		printf("%s: %d\n", group->names[i], group->cal[i]);
	}
}

static void test_string_students_group()
{
	int size = 0;
	/* students_group **students = get_students(&size); */
	hash_map* hm = hm_new(string_to_student_del_item,
						  students_compare,
						  hm_double_hash);

	for (int i = 0; i < size; i++) {
		assert(hm->count == i);
		hm_insert(hm, keys[i], &groups[i], sizeof(students_group*));
	}

	for (short i = size - 1; i >= 0; --i) {
		assert(hm->count == i + 1);
		students_group *value = *(students_group**) hm_search(hm, keys[i]);
		assert(hm->compare_fun(value, &groups[i]) == 0);
		hm_delete(hm, keys[i]);
		assert(hm->count == i);
	}

	hm_dispose(hm);
}

static void test_string_string_creation_insertion_searching_deletion()
{
	hash_map* hm = hm_new(char_to_char_del_item,
						  str_comparator,
						  hm_double_hash);
	for (short i = 0; i < 7; i++) {
		assert(hm->count == i);
		hm_insert(hm, keys[i], values[i], sizeof(char*));
		assert(hm->count == i + 1);
	}

	for (short i = 6; i >= 0; --i) {
		assert(hm->count == i + 1);
		char* value = (char*) hm_search(hm, keys[i]);
		assert(hm->compare_fun(value, values[i]) == 0);
		hm_delete(hm, keys[i]);
		assert(hm->count == i);
	}

	hm_dispose(hm);
}

void hm_test_suite()
{
	printf("\t--------------------\n\tHASHMAP TEST SUITE\n\t--------------------\n");

	launch_test(test_string_string_creation_insertion_searching_deletion,
				"HM [char* -> char*] creation & insertion          --> OK");
	launch_test(test_string_students_group,
				"HM [char* -> students_group] creation & insertion --> OK");
}
