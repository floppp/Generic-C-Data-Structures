#include <string.h>
#include "../headers/lecture_5.h"

int linear_search(void* key, void* base, int n, int elem_size, int(*cmp_fn)(void*, void*))
{
	void* elem_addr;
	for (int i = 0; i < n; ++i) {
		elem_addr = (char*)base + i*elem_size;
		if (cmp_fn(elem_addr, key) == 0)
			return i;
	}
	return -1;
}

int binary_search_rec(void* key, void* base, const void* array,
					  int n, int elem_size, int (*cmp_fn)(void *, void *))
{
	if (n/2 == 0) return -1;

	void* elem_addr = (char*)base + n/2 * elem_size;

	if (cmp_fn(key, elem_addr) > 0)
		binary_search_rec(key, elem_addr, array, (n - n/2), elem_size, cmp_fn);
	else if (cmp_fn(key, elem_addr) < 0)
		binary_search_rec(key, base, array, n/2, elem_size, cmp_fn);
	else {
		int aux = (elem_addr - array)/4;
		return aux;
	}
}

int binary_search(void *key, void *base, int n, int elem_size, int (*cmp_fn)(void *, void *))
{
	void* elem_addr;
	int i = 0;
	int m = n / 2;
	int j = n - 1;

	while (i <= j)
	{
		m = i + (j-i)/2;
		elem_addr = (char*)base + m*elem_size;
		if (cmp_fn(key, elem_addr) > 0)
			i = m + 1;
		else if (cmp_fn(key, elem_addr) < 0)
			j = m - 1;
		else
			return m;

	}

	return -1;
}

int int_comparator(void* left, void* right)
{
	const int* i1 = (int*) left;
	const int* i2 = (int*) right;

	return *i1 - *i2;
}

int str_comparator(void* left, void* right)
{
	const char *str1 = *(char**) left;
	const char *str2 = *(char**) right;

	printf("%s\n", left);
	printf("%s\n", right);
//	return strcmp(str1, str2);
	return -1;
}
