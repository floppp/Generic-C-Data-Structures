#include "../headers/students_utils.h"

int students_hash_fun(const void* elem_addres, int num_buckets)
{
	students_group* s = (struct students_group*) elem_addres;
	int result = 0;
	for (int i = 0; i < s->elem; ++i) {
		char* w = s->names[i];
		short w_len = strlen(w);
		for (int j = 0; j < w_len; ++j)
			result += w[j];
		result *= s->cal[i];
	}

	return result % num_buckets;
}

void students_group_free(void* elem)
{
	students_group* aux = (struct students_group*) elem;

	for (int i = 0; i < aux->elem; ++i) {
		free(aux->names[i]);
		aux->names[i] = NULL;
	}

	free(aux->names);
	free(aux->cal);

	aux->names = NULL;
	aux->cal = NULL;
}

int students_compare(const void* elem_addr_1, const void* elem_addr_2)
{
	students_group* s1 = (struct students_group*) elem_addr_1;
	students_group* s2 = (struct students_group*) elem_addr_2;

	int len = s1->elem;
	if (len != s2->elem)
		return 0;

	for (int i = 0; i < len; ++i)
		if (strcmp(s1->names[i], s2->names[i]) || s1->cal[i] != s2->cal[i])
			return 0;

	return 1;
}

students_group** get_students(int* size)
{
	students_group **groups = malloc(sizeof(students_group*) * N_GROUPS);

	for (int i = 0; i < N_GROUPS; i++) {
 		*(groups + i) = malloc(sizeof(students_group));
	}
	*(groups + 1) = malloc(sizeof(students_group));
	groups[0]->elem = 4;
	char* names_1[] = {"Al", "Bob", "Carl", "John"};
	const int notas_1[] = {3, 4, 5, 3};

	groups[0]->names = malloc(groups[0]->elem * (sizeof(char*)+1));
	groups[0]->cal = malloc(groups[0]->elem * sizeof(int));

	for (int j = 0; j < groups[0]->elem; ++j) {
		groups[0]->names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
		strcpy(groups[0]->names[j], names_1[j]);
		groups[0]->cal[j] = notas_1[j];
	}

	groups[1]->elem = 6;
	const char *names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
	const int notas_2[] = {1, 2, 3, 2, 0, 2};

	groups[1]->names = malloc(groups[1]->elem * sizeof(char*));
	groups[1]->cal = malloc(groups[1]->elem * sizeof(int));

	for (int j = 0; j < groups[1]->elem; ++j) {
		groups[1]->names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
		strcpy(groups[1]->names[j], names_2[j]);
		groups[1]->cal[j] = notas_2[j];
	}

	groups[2]->elem = 6;
	const char* names_3[] = {"zzzzzz", "xxxxxx", "yyyyyy", "wwwwww", "uuuuuuu", "pppppp"};
	const int notas_3[] = {1, 2, 3, 2, 0, 2};

	groups[2]->names = malloc(groups[2]->elem * sizeof(char*));
	groups[2]->cal = malloc(groups[2]->elem * sizeof(int));

	for (int j = 0; j < groups[2]->elem; ++j) {
		groups[2]->names[j] = malloc((strlen(names_3[j]) + 1)*sizeof(char));
		strcpy(groups[2]->names[j], names_3[j]);
		groups[2]->cal[j] = notas_3[j];
	}

	*size = N_GROUPS;

	return groups;
}

void free_students(students_group *students, int *size)
{
	for (int i = 0; i < *size; ++i) {
		students_group_free(&students[i]);
	}
	free(students);
}
