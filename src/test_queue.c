#include "../headers/test_queue.h"


void test_queue_students()
{
	queue struct_queue;
	queue_new(&struct_queue, sizeof(students_group), students_group_free);


	// ENQUEUE
	{
		students_group group_1;
		group_1.elem = 4;

		char* names_1[] = {"Al", "Bob", "Carl", "John"};
		const int notas_1[] = {3, 4, 5, 3};

		group_1.names = malloc(group_1.elem * sizeof(char*));
		group_1.cal = malloc(group_1.elem * sizeof(int));

		for (int j = 0; j < group_1.elem; ++j) {
			group_1.names[j] = malloc((strlen(names_1[j]) + 1)*sizeof(char));
			strcpy(group_1.names[j], names_1[j]);
			group_1.cal[j] = notas_1[j];
		}
		queue_enqueue(&struct_queue, &group_1);
	}

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

		queue_enqueue(&struct_queue, &group_2);
	}

	// DEQUEUE
	students_group aux;
	queue_dequeue(&struct_queue, &aux);
	printf("First element\n");
	print_students(&aux, NULL);
	students_group_free(&aux);

	// DEQUEUE
	queue_dequeue(&struct_queue, &aux);
	printf("Second element\n");
	print_students(&aux, NULL);
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

		queue_enqueue(&struct_queue, &group_2);
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

		queue_enqueue(&struct_queue, &group_2);
	}

	// DEQUEUE
	queue_dequeue(&struct_queue, &aux);
	printf("Third element\n");
	print_students(&aux, NULL);
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

		queue_enqueue(&struct_queue, &group_2);
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

		queue_enqueue(&struct_queue, &group_2);
	}

	for (int i = 0; i < 3; ++i) {
		students_group aux;
		queue_dequeue(&struct_queue, &aux);
		printf("Inside 'for' element\n");
		print_students(&aux, NULL);
		students_group_free(&aux);
	}

	queue_dispose(&struct_queue);
}

void test_queue()
{
	queue q;
	queue_new(&q, sizeof(int), NULL);

	int xs[] = {4, 5, -2, 3, 1, 0, -6, -0, 5, 6, 5, -4, -2, 5, 7, 3, 9, 8};

	queue_enqueue(&q, &xs[0]);

	for (int i = 1; i < 17; ++i)
		queue_enqueue(&q, &xs[i]);

	queue_enqueue(&q, &xs[17]);

	printf("length of queue: %d\n", q.logical_len);

	int b;
	for (int i = 0; i < 9; ++i) {
		queue_dequeue(&q, &b);
		printf("int dequeue: %d -- still %d elements / pos: %d\n", b, q.logical_len, i);
	}

	int c = 11;
	queue_enqueue(&q, &c);

	for (int i = 9; i < 19; ++i) {
		queue_dequeue(&q, &b);
		printf("int dequeue: %d -- still %d elements / pos: %d\n", b, q.logical_len, i);
	}

	queue_dispose(&q);
}
