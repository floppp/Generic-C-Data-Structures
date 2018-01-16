#include "../headers/queue.h"

static void queue_grow(queue* q);
static void queue_drecrease(queue* q);
const int Q_ALL_DEF_SIZE = 4;
const int Q_LOG_DEF_SIZE = 0;

void queue_new(queue *q, int e_size, void(*free_function)(void*))
{
	assert(e_size > 0);

	q->elem_size = e_size;
	q->last_pos = 0;
	q->len = Q_LOG_DEF_SIZE;
	q->all_len = Q_ALL_DEF_SIZE;
	q->elements = malloc(q->all_len * e_size);
	q->free_function = free_function;
	q->q_pos = 0;

	assert(q->elements != NULL);
}

void queue_dispose(queue *q)
{
	if (q->free_function)
		for (short i = 0; i < q->len; ++i)
			q->free_function((char*) q->elements + i*q->elem_size);

	free(q->elements);
	q->elements = NULL;
	q->len = Q_LOG_DEF_SIZE;
	q->all_len = 0;
}

void queue_enqueue(queue *q, void *e_addr)
{
	queue_grow(q);

	void* target = (char*) q->elements + (q->last_pos++)*q->elem_size;
	memcpy(target, e_addr, q->elem_size);

	q->len++;

}

void queue_dequeue(queue *q, void *e_addr)
{
	assert(q->len > 0);

	void* source = (char*) q->elements + q->q_pos*q->elem_size;
	memcpy(e_addr, source, q->elem_size);
	q->len--;

	queue_drecrease(q);
}

static void queue_grow(queue* q)
{
	if (q->len == q->all_len) {
		q->all_len += Q_ALL_DEF_SIZE;
		q->elements = realloc(q->elements, q->all_len * q->elem_size);
	}
}

static void queue_drecrease(queue* q)
{
	if (q->q_pos++ == (q->all_len/2)) {
		for (int i = 0; i < q->len; ++i) {
			void* target = (char*) q->elements + i*q->elem_size;
			void* source = (char*) q->elements + (q->q_pos + i)*q->elem_size;
			memcpy(target, source, q->elem_size);
		}

		q->all_len = q->len + (4 - (q->len % 4));
		q->q_pos = 0;
		q->last_pos = q->len;

		void* tmp = realloc(q->elements, q->all_len * q->elem_size);
		if (tmp)
		    q->elements = tmp;
		else
			exit(-1);
	}
}
