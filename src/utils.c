#include "../headers/utils.h"

int random_gen()
{
	srand(time(NULL));
	return rand();
}

int hash_fun(const void* elem_addres, int num_buckets)
{
	long value = *(int*) elem_addres;

	return (value * 2654435761) % num_buckets;
}

void print_array(void* base, int n, int elem_size)
{
	void* elem_address;
	for (int i = 0; i < n; ++i) {
		elem_address = (char*)base + i*elem_size;
		printf("%d - %d\n", i, *(int*)elem_address);
	}
}

void string_free(void* elem)
{
	free(*(char**) elem);
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

int int_comparator(const void* left, const void* right)
{
	const int* i1 = (int*) left;
	const int* i2 = (int*) right;

	return *i1 - *i2;
}

int str_comparator(const void* left, const void* right)
{
	const char *str1 = *(char**) left;
	const char *str2 = *(char**) right;

	return strcmp(str1, str2);
//	return -1;
}

void list_print(list *l)
{
	for (int i = 0; i < l->logical_len; ++i) {
		void* source = (char*) l->elements + i*l->elem_size;
		printf(get_format(l), *(int*)source);
		printf(" - ");
	}
	printf("\n");
}

void print_int(void* elem_addr, const void* aux_data)
{
	printf("%d : ", *(int*) elem_addr);
}

char* get_format(list* l)
{
	switch (l->elem_size) {
		case 4:
			return "%d";
		case 8:
			return "%f";
		case 1:
			return "%c";
		default:
			return "%s";
	}
}
