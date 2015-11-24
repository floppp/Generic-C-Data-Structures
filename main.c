#include <stdio.h>
#include <string.h>
#include "headers/lecture_5.h"
#include "headers/students_group.h"
#include "headers/queue.h"
#include "headers/stack.h"
#include "headers/utils.h"
#include "headers/list.h"
#include "headers/linked_list.h"
#include "headers/test_stack.h"
#include "headers/test_queue.h"
#include "headers/test_list.h"
#include "headers/test_vector.h"
#include "headers/test_linked_list.h"

void linear_binary_search_tests();
void test_binary_search(void* base, int n, int elem_size);

char* get_format(list*);


int main()
{
//	printf("\nSTACK TEST --------------------------\n\n");
//	test_stack_heap();
//	test_stack_students();
//	printf("\nQUEUE TEST --------------------------\n\n");
//	test_queue();
//	test_queue_students();
//	printf("\nLIST TEST --------------------------\n\n");
//	test_list();
//	test_list_students();
//	printf("\nLINKED LIST TEST --------------------------\n\n");
//	test_linked_list();
//	test_linked_list_student();
	printf("\nVECTOR TEST --------------------------\n\n");
	test_int_vector();

	return 0;
}

void test_binary_search(void* base, int n, int elem_size)
{
	void* elem_addr;
	for (int i = 0; i < n; ++i)	{
		elem_addr = (char*)base + i*elem_size;
		int found = binary_search((int*)elem_addr, base, n, sizeof(int), int_comparator);
		printf("element: %2d - position: %2d \n", *(int*)elem_addr, found);
	}
}

void linear_binary_search_tests()
{
	int array[] = {4, 6, 3, 2, 8, 9, 7, 0, 10, 22};
	int size = 6;
	int number = 1;

	int found = linear_search(&number, array, size, sizeof(int), int_comparator);
	printf("%d\n", found);

	int sorted_array[] = {1, 3, 5, 7, 9, 11, 12, 14, 23, 34, 45, 47, 89};
	size = 13;
	int found_ = binary_search_rec(&number, sorted_array, sorted_array, size, sizeof(int), int_comparator);
	printf("%d\n", found_);
	test_binary_search(sorted_array, size, sizeof(int));

	char* notes[] = {"Ab", "F#", "B", "Gb", "D"};
	char* fav_note = "Gb";
	size = 5;
	int char_found = linear_search(&fav_note, notes, size, sizeof(char*), str_comparator);
	printf("%d\n", char_found);
}
