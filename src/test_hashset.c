#include "../headers/test_hashset.h"

int get_random(double(*)(), int, int);

void test_int_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(int), 20, hash_fun, int_comparator, NULL);

	for (int i = 0; i < 20; ++i) {
		int n = get_random(uniforme, 0, 150);
		hashset_enter(&h, &n);
	}

	hashset_map(&h, print_int, NULL);
	hashset_dispose(&h);
}

void test_students_hashset()
{
	hashset h;
	hashset_new(&h, sizeof(students_group), 20, NULL, NULL, students_group_free);

	// Add
	{
		students_group group_1;
		group_1.elem = 4;

		char* names_1[] = {"Al", "Bob", "Carl", "John"};
		const int notas_1[] = {3, 4, 5, 3};

		group_1.names = malloc(group_1.elem * (sizeof(char*)+1));
		group_1.cal = malloc(group_1.elem * sizeof(int));

		for (int j = 0; j < group_1.elem; ++j) {
			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
			strcpy(group_1.names[j], names_1[j]);
			group_1.cal[j] = notas_1[j];
		}

		hashset_enter(&h, &group_1);
	}


	hashset_dispose(&h);
}

int get_random(double (*generator_fun)(), int min, int max)
{
	double temp = generator_fun();

	return (min - 1) + ceil(temp*(max - min));
}
