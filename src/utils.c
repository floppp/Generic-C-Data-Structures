#include "../headers/utils.h"

int get_random(double (*generator_fun)(), int min, int max)
{
	double temp = generator_fun();

	return (min - 1) + ceil(temp*(max - min));
}

int random_gen()
{
	srand(time(NULL));

	return rand();
}

void print_array(void* base, int n, int elem_size)
{
	void* elem_address;
	for (int i = 0; i < n; ++i) {
		elem_address = (char*) base + i*elem_size;
		printf("%d - %d\n", i, *(int*)elem_address);
	}
}

void string_free(void* elem)
{
	free(*(char**) elem);
}

int int_comparator(const void* left, const void* right)
{
	const int* i1 = (int*) left;
	const int* i2 = (int*) right;

	return *i1 - *i2;
}

int str_comparator(const void* left, const void* right)
{
	const char *str1 = (char*) left;//*(char**) left;
	const char *str2 = (char*) right;//*(char**) right;

	return strcmp(str1, str2);
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

int string_compare(const char* w1, const char* w2, int l)
{
	if (strlen(w1) != strlen(w2))
		return 0;

	for (int i = 0; i < l; i++)
		if (w1[i] != w2[i])
			return 0;

	return 1;
}

void launch_test(void(*f)(), const char* msg)
{
	f();
	printf("%s\n", msg);
}
