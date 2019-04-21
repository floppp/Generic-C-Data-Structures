#include "tests/test_stack.h"
#include "tests/test_queue.h"
#include "tests/test_vector.h"
#include "tests/test_linked_list.h"
#include "tests/test_utils.h"
#include "./tests/test_hash_map.h"


int main()
{
	stack_test_suite();
	queue_test_suite();
	vector_test_suite();
	linked_list_test_suite();
	hm_test_suite();

	return 0;
}
