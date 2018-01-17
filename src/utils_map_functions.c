#include "../headers/utils_map_functions.h"

void odd_numbers(void* e_addr, const void* aux_data)
{
	int* n = (int*) e_addr;
	int* m = malloc(sizeof(int));
	*m = *n % 2 != 0 ? *n : 0;
	memcpy(e_addr, m, sizeof(int));
	free(m);
}

void removing_first_or_second_char(void* e_addr, const void* aux_data)
{
	int* n = (int*) aux_data;
	char* word = (char*) e_addr;

	if (*n) {

	}


}
