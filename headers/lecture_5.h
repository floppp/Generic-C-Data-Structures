#ifndef LECTURE_5
#define LECTURE_5

int linear_search(void* key, void* base, int n, int elem_size, int(*cmp_fn)(void*, void*));
int binary_search(void* key, void* base, int n, int elem_size, int(*cmp_fn)(void*, void*));
int binary_search_rec(void* key, void* base, const void* array, int n, int elem_size, int(*cmp_fn)(void*, void*));
int int_comparator(void*, void*);
int str_comparator(void*, void*);

#endif // LECTURE_5

