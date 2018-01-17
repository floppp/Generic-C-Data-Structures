#include "test_vector.h"
#define N_STU 4

vector int_v;
vector str_v;
vector stu_v;
short N_INT = 12;
short N_STR = 7;
int xs[] = { 1, 2, 3, 4, 2, 5, 6, 7, 1, 2, 3, 0};
char** words_m;
students_group groups[N_STU];

void test_vector_new()
{
	vector_new(&int_v, sizeof(int), NULL, 10);
	vector_new(&str_v, sizeof(char*), string_free, 10);
	vector_new(&stu_v, sizeof(students_group), students_group_free, 10);

	assert(int_v.len == 0);
	assert(int_v.all_len == 10);

	assert(str_v.len == 0);
	assert(str_v.all_len == 10);

	assert(stu_v.len == 0);
	assert(stu_v.all_len == 10);
}

void test_vector_append()
{
	for (short i = 0; i < N_INT; ++i) {
		vector_append(&int_v, &xs[i]);
	}

	const char* words[] = { "casa", "mar", "mesa", "ropa", "luz", "lampara",
                            "fosforo" };
	words_m = malloc(N_STR * sizeof(char*));
	for (short i = 0; i < N_STR; ++i) {
		words_m[i] = malloc(strlen(words[i]) + 1);
		strcpy(words_m[i], words[i]);
		vector_append(&str_v, &words_m[i]);
	}

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

	groups[1].elem = 6;
	const char* names_2[] = {"Lou", "David", "Steve", "Logan", "Popi", "Juno"};
	const int notas_2[] = {1, 2, 3, 2, 0, 2};

	groups[1].names = malloc(groups[1].elem * sizeof(char*));
	groups[1].cal = malloc(groups[1].elem * sizeof(int));

	for (int j = 0; j < groups[1].elem; ++j) {
		groups[1].names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[1].names[j], names_2[j]);
		groups[1].cal[j] = notas_2[j];
	}


	groups[2].elem = 6;
	const char* names_3[] = {"Juno", "Lola", "Bimba", "Lia", "Bimba",
							 "Nina"};
	const int notas_3[] = {1, 2, 3, 2, 0, 2};

	groups[2].names = malloc(groups[2].elem * sizeof(char*));
	groups[2].cal = malloc(groups[2].elem * sizeof(int));

	for (int j = 0; j < groups[2].elem; ++j) {
		groups[2].names[j] = malloc((strlen(names_3[j]) + 1)*sizeof(char));
		strcpy(groups[2].names[j], names_3[j]);
		groups[2].cal[j] = notas_3[j];
	}

	vector_append(&stu_v, &groups[0]);
	vector_append(&stu_v, &groups[1]);
	vector_append(&stu_v, &groups[2]);

	assert(int_v.len == 12);
	assert(int_v.all_len == 20);
	assert(str_v.len == 7);
	assert(str_v.all_len == 10);
	assert(stu_v.len == 3);
	assert(stu_v.all_len == 10);
}

void test_vector_len()
{
	assert(vector_len(&int_v) == 12);
	assert(vector_len(&str_v) == 7);
	assert(vector_len(&stu_v) == 3);
}

void test_vector_get()
{
	int n;
	for (short i = 0; i < N_INT; i++) {
		vector_get(&int_v, i, &n);
		assert(n == xs[i]);
	}

	const char* word;
	for (short i = 0; i < N_STR; ++i) {
		vector_get(&str_v, i, &word);
		assert(string_compare(word, words_m[i], strlen(word)));
	}

	students_group group;
	for (short i = 0; i < N_STU-1; ++i) {
		vector_get(&stu_v, i, &group);
		assert(students_compare(&group, &groups[i]));
	}
}

void test_vector_insert()
{
	int n;
	const int N = 4;
	const int ys[] = {-1, -2, -3, -4};
	const int zs[] = {-1, 1, -2, 2, -3, 3, -4, 4, 2, 5, 6, 7, 1, 2, 3, 0};
	const char* words_res[] = { "casa", "casa", "mar", "mar", "mesa", "mesa",
                                "ropa", "ropa", "luz", "luz", "lampara",
                                "lampara", "fosforo", "fosforo" };
	const char* words[] = { "casa", "mar", "mesa", "ropa", "luz", "lampara",
                            "fosforo" };
	char** auxs = malloc(N_STR * sizeof(char*));

	for (int i = 0; i < N; ++i)
		vector_insert(&int_v, &ys[i], i*2);

	for (short i = 0; i <N_INT+N; i++) {
		vector_get(&int_v, i, &n);
		assert(n == zs[i]);
	}

	for (short i = 0; i < N_STR; ++i) {
		auxs[i] = malloc(strlen(words[i]) + 1);
		strcpy(auxs[i], words[i]);
		vector_insert(&str_v, &auxs[i], i*2);

	}
	free(auxs);

	const char* word;
	for (int i = 0; i < 2*N_STR; ++i) {
		vector_get(&str_v, i, &word);
		assert(string_compare(word, words_res[i], strlen(word)));
	}

	groups[3].elem = 5;
	const char* names_2[] = {"Juan", "Eva", "Bill", "Jon", "Liz"};
	const int notas_2[] = {1, 2, 3, 2, 0};

	groups[3].names = malloc(groups[3].elem * sizeof(char*));
	groups[3].cal = malloc(groups[3].elem * sizeof(int));

	for (int j = 0; j < groups[3].elem; ++j) {
		groups[3].names[j] =
			malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[3].names[j], names_2[j]);
		groups[3].cal[j] = notas_2[j];
	}

	vector_insert(&stu_v, &groups[3], 0);

	students_group group;
	vector_get(&stu_v, 0, &group);
	assert(students_compare(&group, &groups[3]));

	vector_get(&stu_v, 1, &group);
	assert(students_compare(&group, &groups[0]));

	vector_get(&stu_v, 2, &group);
	assert(students_compare(&group, &groups[1]));

	vector_get(&stu_v, 3, &group);
	assert(students_compare(&group, &groups[2]));
}

void test_vector_replace()
{
	int n;
	const int N = 4;
	const int ys[] = { 10, 100, 90, 1000 };
	const int zs[] = { 10, 1, 100, 2, 90, 3, 1000, 4, 2, 5, 6, 7, 1, 2, 3, 0 };
	// const char* aux;
	// const char* words[] = { "casa", "casa", "casa", "mar", "casa", "mesa", "mar", "ropa", "casa", "luz", "mesa", "lampara", "mar", "fosforo" };

	for (int i = 0; i < N; ++i)
		vector_replace(&int_v, &ys[i], i+i);

	for (short i = 0; i <N_INT+N; i++) {
		vector_get(&int_v, i, &n);
		assert(n == zs[i]);
	}

	// students_group group_2;
	// group_2.elem = 6;
	// const char* names_2[] = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF"};
	// const int notas_2[] = {1, 2, 3, 2, 0, 2};

	// group_2.names = malloc(group_2.elem * sizeof(char*));
	// group_2.cal = malloc(group_2.elem * sizeof(int));

	// for (int j = 0; j < group_2.elem; ++j) {
	// 	group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
	// 	strcpy(group_2.names[j], names_2[j]);
	// 	group_2.cal[j] = notas_2[j];
	// }

	// vector_replace(&stu_v, &group_2, 2);
}

void test_vector_dispose()
{

	vector_dispose(&int_v);
	vector_dispose(&str_v);
	vector_dispose(&stu_v);

	free(words_m);

	assert(int_v.elements == NULL);
	assert(int_v.len == 0);
	assert(int_v.all_len == 0);

	assert(str_v.elements == NULL);
	assert(str_v.len == 0);
	assert(str_v.all_len == 0);

	assert(stu_v.elements == NULL);
	assert(stu_v.len == 0);
	assert(stu_v.all_len == 0);
}

void vector_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  VECTOR TEST SUITE\n\t---------------------\n");

	launch_test(test_vector_new, "Vector creation --> OK");
	launch_test(test_vector_append, "Vector appending elements --> OK");
	launch_test(test_vector_len, "Vector length --> OK");
	launch_test(test_vector_get, "Vector get element --> OK");
	launch_test(test_vector_insert, "Vector insert --> OK");
	// launch_test(test_vector_replace, "Vector replace --> OK");
	launch_test(test_vector_dispose, "Vector dispose --> OK");
}
