#include "test_queue.h"

queue int_q;
queue str_q;
queue stu_q;

void test_queue_creation()
{
	queue_new(&int_q, sizeof(int), NULL);
	queue_new(&str_q, sizeof(char*), string_free);

	assert(str_q.len == 0);
	assert(str_q.all_len == 4);
	assert(int_q.len == 0);
	assert(int_q.all_len == 4);
}

void test_int_q_enqueue()
{
	int i = 2;
	queue_enqueue(&int_q, &i);

	assert(int_q.len == 1);

	i = 1;
	queue_enqueue(&int_q, &i);
	queue_enqueue(&int_q, &i);

	assert(int_q.len == 3);
	assert(int_q.all_len == 4);
}

void test_int_q_dequeue()
{
	int i;

	assert(int_q.len == 3);

	queue_dequeue(&int_q, &i);
	assert(i == 2 && int_q.len == 2);

	queue_dequeue(&int_q, &i);
	assert(i == 1 && int_q.len == 1);

	queue_dequeue(&int_q, &i);
	assert(i == 1 && int_q.len == 0);
}

void test_int_q_dispose()
{
	queue_dispose(&int_q);

	assert(int_q.elements == NULL);
}

void test_enqueue_string()
{
	int count = 0;
	const char* friends[] = {"Al", "Bob", "Carl", "John"};

	for (int i = 0; i < 4; ++i) {
		char* copy = strdup(friends[i]);
		queue_enqueue(&str_q, &copy);
		assert(str_q.len == ++count);
	}

	assert(str_q.len == 4);
	assert(str_q.all_len == 4);

	const char* words[] = {"casa", "mar", "mesa", "ropa", "luz", "lampara", "fosforo"};

	for (short i = 0; i < 7; ++i) {
		const char* copy = strdup(words[i]);
		queue_enqueue(&str_q, &copy);
		assert(str_q.len == ++count);
	}

	assert(str_q.len == 11);
	assert(str_q.all_len == 12);
}

void test_dequeue_string()
{
	char* word;
	short idx = 0;
	const char* words[] = {	"Al", "Bob", "Carl", "John", "casa", "mar",
							"mesa", "ropa", "luz", "lampara", "fosforo" };

	for (short i = 0; i < 11; ++i) {
		queue_dequeue(&str_q, &word);
		assert(string_compare(word, words[idx++], strlen(word)));
		free(word);
	}

	// assert(str_q.all_len == 4 && str_q.len == 0);
	assert(str_q.len == 0);
}


void test_str_q_dispose()
{
	int count = str_q.len;

	const char* words[] = {"casa", "mar", "mesa", "ropa", "luz", "lampara", "fosforo"};

	for (short i = 0; i < 7; ++i) {
		char* copy = strdup(words[i]);
		queue_enqueue(&str_q, &copy);
		assert(str_q.len == ++count);
	}

	queue_dispose(&str_q);

	assert(str_q.elements == NULL);
	assert(str_q.len == 0);
	assert(str_q.all_len == 0);
}


void test_queue_students_enqueue(const char* msg)
{
	queue_new(&stu_q, sizeof(students_group), students_group_free);

	assert(stu_q.len == 0);
	assert(stu_q.all_len == 4);

	printf("Queue students creation --> OK\n");

	{
		students_group group_1;
		group_1.elem = 4;

		char* names_1[] = {"Al", "Bob", "Carl", "John"};
		const int grades_1[] = {3, 4, 5, 3};

		group_1.names = malloc(group_1.elem * sizeof(char*));
		group_1.cal = malloc(group_1.elem * sizeof(int));

		for (int j = 0; j < group_1.elem; ++j) {
			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
			strcpy(group_1.names[j], names_1[j]);
			group_1.cal[j] = grades_1[j];
		}

		queue_enqueue(&stu_q, &group_1);

		assert(stu_q.len == 1);
		assert(stu_q.all_len == 4);
	}

	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = { "Lou", "David", "Steven", "Logan", "Popi",
								  "Juno" };
		const int grades_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = grades_2[j];
		}

		queue_enqueue(&stu_q, &group_2);

		assert(stu_q.len == 2);
		assert(stu_q.all_len == 4);
	}

	printf("%s\n", msg);
}

void test_queue_students_dequeue(const char* msg)
{
	// DEQUEUE
	students_group aux;
	queue_dequeue(&stu_q, &aux);
	// printf("First element\n");
	// print_students(&aux, NULL);
	students_group_free(&aux);

	// DEQUEUE
	queue_dequeue(&stu_q, &aux);
	// printf("Second element\n");
	// print_students(&aux, NULL);
	students_group_free(&aux);

	assert(stu_q.len == 0);
	assert(stu_q.all_len == 4);

	// ENQUEUE AGAIN
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

		queue_enqueue(&stu_q, &group_2);
	}

	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"zzzzzz", "xxxxxx", "yyyyyy", "wwwwww", "uuuuuuu", "pppppp"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

		queue_enqueue(&stu_q, &group_2);
	}

	// DEQUEUE
	queue_dequeue(&stu_q, &aux);
	// printf("Third element\n");
	// print_students(&aux, NULL);
	students_group_free(&aux);

	// ENQUEUE
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"Lou", "David", "Steven", "Logan", "Popi", "Juno"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

		queue_enqueue(&stu_q, &group_2);
	}

	// ENQUEUE
	{
		students_group group_2;
		group_2.elem = 6;
		const char* names_2[] = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF"};
		const int notas_2[] = {1, 2, 3, 2, 0, 2};

		group_2.names = malloc(group_2.elem * sizeof(char*));
		group_2.cal = malloc(group_2.elem * sizeof(int));

		for (int j = 0; j < group_2.elem; ++j) {
			group_2.names[j] = malloc((strlen(names_2[j]) + 1)*sizeof(char));
			strcpy(group_2.names[j], names_2[j]);
			group_2.cal[j] = notas_2[j];
		}

		queue_enqueue(&stu_q, &group_2);
	}

	for (int i = 0; i < 3; ++i) {
		students_group aux;
		queue_dequeue(&stu_q, &aux);
		// printf("Inside 'for' element\n");
		// print_students(&aux, NULL);
		students_group_free(&aux);
	}

	assert(stu_q.len == 0);
	assert(stu_q.all_len == 4);

	printf("%s\n", msg);
}

void test_queue_students_dispose(const char* msg)
{
	queue_dispose(&stu_q);

	assert(str_q.elements == NULL);
	assert(str_q.len == 0);
	assert(str_q.all_len == 0);

	printf("%s\n", msg);
}

void queue_test_suite()
{
	printf("\t--------------------\n\t");
	printf("  QUEUE TEST SUITE\n\t--------------------\n");

	launch_test(test_queue_creation, "Queue creation --> OK");
	launch_test(test_int_q_enqueue, "Queue adding integers --> OK");
	launch_test(test_int_q_dequeue, "Queue retrieving integers --> OK");
	launch_test(test_int_q_dispose, "Queue disposing integers --> OK");
	launch_test(test_enqueue_string, "Queue adding strings --> OK");
	launch_test(test_dequeue_string, "Retriving strings from Queue --> OK");
	launch_test(test_str_q_dispose, "Disposing string Queue --> OK");
	// launch_test(test_queue_students_enqueue, "Queue students enqueue --> OK");
	// launch_test(test_queue_students_dequeue, "Queue students dequeue --> OK");
	// launch_test(test_queue_students_dispose, "Queue students dispose --> OK");
}

