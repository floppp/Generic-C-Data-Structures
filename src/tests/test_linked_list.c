#include "test_linked_list.h"

#define N_GROUPS 3
#define N_STRINGS 7
#define N_INTEGERS 10

static int is[] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };
static char* words[] = { "casa", "mar", "mesa", "ropa", "luz",
                         "lampara", "fosforo" };
linked_list* stu_ll;
linked_list* int_ll;
linked_list* str_ll;
linked_list* mix_ll;
students_group groups[N_GROUPS];

void data_preparation()
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

void test_node_new()
{
	node* n = node_new(INTEGER, &is[9], NULL, NULL, sizeof(int));
	int i = *(int*) n->element;

	assert(n->e_size == sizeof(int));
	assert(i == 81);

	node_free(n);
}

void test_linked_list_new()
{
	stu_ll = linked_list_new();
	int_ll = linked_list_new();
	str_ll = linked_list_new();
	mix_ll = linked_list_new();

	assert(stu_ll->head == NULL);
	assert(int_ll->head == NULL);
	assert(str_ll->head == NULL);
	assert(mix_ll->head == NULL);
	assert(stu_ll->len == 0);
	assert(int_ll->len == 0);
	assert(str_ll->len == 0);
	assert(mix_ll->len == 0);
}

void test_linked_list_remove_list()
{
	linked_list_remove_list(stu_ll);
	linked_list_remove_list(int_ll);
	linked_list_remove_list(str_ll);
	linked_list_remove_list(mix_ll);

	/* We dont assert here; valgrind tell us everything was free, so
	we take that as a proof of validation. */
}

/* Both, linked_list_add and linked_list_add_node are tested with
   this test. */
void test_linked_list_add()
{
	for (int i = 0; i < N_GROUPS; ++i) {
		linked_list_append(stu_ll, OTHER, sizeof(students_group), &groups[i],
		                students_group_free, print_students);
	}

	for (int i = 0; i < N_INTEGERS; ++i) {
		linked_list_append(int_ll, INTEGER, sizeof(int), &is[i], NULL, NULL);
	}

	for (int i = 0; i < N_STRINGS; ++i) {
		linked_list_append(str_ll, STRING, sizeof(char*), &words[i], NULL, NULL);
	}

	assert(stu_ll->len == N_GROUPS);
	assert(int_ll->len == N_INTEGERS);
	assert(str_ll->len == N_STRINGS);
}

void test_linked_list_get()
{
	int n;
	char* word;
	students_group group;

	for (int i = 0; i < N_INTEGERS; ++i) {
		linked_list_get(int_ll, i, &n);
		assert(n == is[i]);
	}

	for (int i = 0; i < N_STRINGS; ++i) {
		linked_list_get(str_ll, i, &word);
		assert(string_compare(word, words[i], strlen(words[i])));
	}


	for (int i = 0; i < N_GROUPS; ++i) {
		linked_list_get(stu_ll, i, &group);
		assert(students_compare(&group, &groups[i]));
	}
}

// 	linked_list_print(list);
// 	linked_list_remove_node(list, 2);
// 	linked_list_print(list);
// 	int x = 444;
// 	linked_list_add(list, 4, Integer, sizeof(int), &x, NULL, NULL);
// 	char o = 'o';
// 	linked_list_add(list, 3, Char, sizeof(char), &o, NULL, NULL);
// 	char* y = "eeee";
// 	linked_list_add(list, 1, String, sizeof(char*), &y, NULL, NULL);
// //	char* h = "casa";
// //	double j = 4.5;
// //	char n = "a";
// 	int m = 444;
// 	int pos = linked_list_find(list, Integer, &m, NULL);
// 	linked_list_remove_node(list, 0);
// 	linked_list* string_list = linked_list_get_subtype(list, String);
// 	linked_list_remove_list(list);
// 	linked_list_remove_list(string_list);
// }

void test_mixed_linked_list()
{
	int a = 775;
	int c = 998;
	int d = -1000;
	char* e = "casa";
	linked_list_append(mix_ll, INTEGER, sizeof(int), &a, NULL, NULL);
	linked_list_append(mix_ll, INTEGER, sizeof(int), &c, NULL, NULL);
	linked_list_append(mix_ll, INTEGER, sizeof(int), &d, NULL, NULL);
	linked_list_append(mix_ll, STRING, sizeof(char*), &e, NULL, NULL);

	int q;
	char* word;
	linked_list_get(mix_ll, 2, &q);
	assert(q == -1000);
	linked_list_remove_node(mix_ll, 2);
	linked_list_get(mix_ll, 2, &word);
	assert(string_compare(word, e, sizeof(e)));

	int z = 111;
	double l = 4.5;
	int x = 444;
	linked_list_add(mix_ll, 0, INTEGER, sizeof(int), &z, NULL, NULL);
	linked_list_add(mix_ll, 3, DOUBLE, sizeof(double), &l, NULL, NULL);
	linked_list_add(mix_ll, 4, INTEGER, sizeof(int), &x, NULL, NULL);


	char o = 'o';
	char* y = "eeee";
	linked_list_add(mix_ll, 3, CHAR, sizeof(char), &o, NULL, NULL);
	linked_list_add(mix_ll, 2, STRING, sizeof(char*), &y, NULL, NULL);

	int m = 444;
	int pos = linked_list_find(mix_ll, INTEGER, &m, NULL);
	assert(pos == 6);
	linked_list* string_list = linked_list_get_subtype(mix_ll, STRING);
}

void dispose_data() { }

void linked_list_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  LINKED LIST TEST SUITE\n\t--------------------\n");

	data_preparation();

	launch_test(test_node_new,                "Node creation          --> OK");
	launch_test(test_linked_list_new,         "Linked list creation   --> OK");
	launch_test(test_linked_list_add,         "Linked list add [node] --> OK");
	launch_test(test_linked_list_get,         "Linked list get        --> OK");
	launch_test(test_mixed_linked_list,       "Linked list mixed      --> OK");
	launch_test(test_linked_list_remove_list, "Linked list remove     --> OK");

	dispose_data();
}
