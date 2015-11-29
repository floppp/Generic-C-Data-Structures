#include "../headers/hashset.h"
#include "../headers/utils.h"

static void vector_in_bucket_initialization(hashset*, const int, const int, hashset_free_fun);
static void insert_element(const void*, hashset*, const void*, const int);


void hashset_new(hashset *h, int elem_size, int num_buckets, hashset_hash_fun hash_fun, hashset_compare_fun compare_fun, hashset_free_fun free_fun)
{
	assert (elem_size > 0 || num_buckets > 0 || hash_fun != NULL || compare_fun != NULL);


	if ((h->elements = malloc(num_buckets * sizeof(vector*))) == NULL) {
		printf("memory allocation error\n");
		return ;
	}

	vector* temp_used_buckets;
	if ((temp_used_buckets = malloc(sizeof(vector))) == NULL) {
		printf("memory allocation error\n");
		return ;
	}
	vector_new(temp_used_buckets, sizeof(int), NULL, 4);

	for (int i = 0; i < num_buckets; ++i)
		vector_in_bucket_initialization(h, i, elem_size, free_fun);

	h->len = 0;
	h->elem_size = elem_size;
	h->num_buckets = num_buckets;
	h->compare_fun = compare_fun;
	h->free_fun = free_fun;
	h->hash_fun = hash_fun;
	h->used_buckets = temp_used_buckets;
}

static void vector_in_bucket_initialization(hashset* h, const int pos, const int elem_size, hashset_free_fun free_fun)
{
	vector* target = (struct vector*) ((char*) h->elements + pos*sizeof(vector*));
	vector_new(target, elem_size, free_fun, 4);


//	vector* aux;
//	if ((aux = malloc(sizeof(vector))) == NULL) {
//		printf("memory allocation error\n");
//		exit(0);
//	}
//	vector_new(aux, elem_size, free_fun, 4);
//	printf("aux direcion: %d - aux->elements direction: %d\n", aux, aux->elements);
//	void* target = (char*) h->elements + pos*sizeof(vector*);
//	memcpy(target, aux, sizeof(vector*));

//	// this two lines, or the five below.
//	vector* target_vector = (struct vector*) target;
//	void* intermidiate = malloc(4 * elem_size);
//	intermidiate[0]
//	memcpy(intermidiate, aux->elements, 4 * elem_size);
//	target_vector->elements = intermidiate;

//	free(aux);
}


void hashset_dispose(hashset* h)
{
	if (h->free_fun != NULL) {
		for (int i = 0; i < h->num_buckets; ++i)
			h->free_fun((char*) h->elements + i*h->elem_size);
	}

	free(h->used_buckets->elements);
	h->used_buckets->elements = NULL;
	free(h->used_buckets);
	h->used_buckets = NULL;

	free(h->elements);
	h->elements = NULL;
}

int hashset_count(hashset* h)
{
	return h->len;
}

void hashset_enter(hashset* h, const void* elem_addr)
{
	assert (elem_addr != NULL);
	int pos = h->hash_fun(elem_addr, h->num_buckets);
	assert (pos >= 0 && pos < h->num_buckets);
	void* target = (char*) h->elements + pos*h->elem_size;

	if (h->compare_fun(target, elem_addr) == 0)
		printf("The element %d was already storaged.\n", *(int*) elem_addr);
	else {
		insert_element(target, h, elem_addr, pos);
	}
}

void* hashset_lookup(const hashset* h, const void* elem_addr)
{
	int pos = h->hash_fun(elem_addr, h->num_buckets);
	void* target = (char*) h->elements + pos*h->elem_size;

	vector* target_vector = (struct vector*) target;
	for (int i = 0; i < target_vector->len; ++i) {
		void* element = vector_get(target_vector, i);
		if (h->compare_fun(element, elem_addr) == 0)
			return element;
	}
	return NULL;
}

void hashset_map(hashset* h, hashset_map_fun map_fun, const void* aux_data)
{

	for (int i = 0; i < h->num_buckets; ++i) {
//		int hash_position = *(int*) vector_get(h->used_buckets, i);
//		void* target = (char*) h->elements + hash_position*h->elem_size;
//		vector* target_vector = (struct vector*) target;
		vector* target_vector = (struct vector*) ((char*)h->elements + i*h->elem_size);
		printf("%d\n", target_vector);
		for (int j = 0; j < target_vector->len; ++j){
//			printf("vector direction: %d\n", target_vector);
//			printf("position in vector of elements: %d - number of elements: %d\n", j, target_vector->len);
			void* element = vector_get(target_vector, j);
			printf("%d\n", element);
//			map_fun(vector_get(target_vector, j), aux_data);
//			map_fun(element, aux_data);
		}
	}
}



static void insert_element(const void* target, hashset* h, const void* elem_addr, const int pos)
{
	vector_append((struct vector*) target, elem_addr);

	if (h->used_buckets->len == 0 || vector_search(h->used_buckets, &pos, int_comparator, 0, false) != 0) {
		vector_append(h->used_buckets, &pos);
	}

	h->len++;
}




































