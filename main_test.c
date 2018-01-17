#include "src/tests/test_stack.h"
#include "src/tests/test_queue.h"
#include "src/tests/test_vector.h"

int main(int argc, char **argv)
{
	stack_test_suite();
	queue_test_suite();
	vector_test_suite();

	return 0;
}
