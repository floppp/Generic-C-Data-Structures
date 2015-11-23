#include "../headers/queue.h"

static void queue_grow(queue* q);
static void queue_drecrease(queue* q);

void queue_new(queue *q, int e_size, void(*free_function)(void*))
{
	assert(e_size > 0);

	q->elem_size = e_size;
	q->last_pos = 0;
	q->logical_len = 0;
	q->allocat_len = 4;
	q->elements = malloc(4 * e_size);
	q->free_function = free_function;
	q->queue_pos = 0;

	assert(q->elements != NULL);
}

void queue_dispose(queue *q)
{
	if (q->free_function != NULL)
		for (int i = 0; i < q->logical_len; ++i)
			q->free_function((char*) q->elements + i*q->elem_size);

	free(q->elements);
	q->elements = NULL;
}

void queue_enqueue(queue *q, void *e_addr)
{
	queue_grow(q);

	void* target = (char*) q->elements + (q->last_pos++)*q->elem_size;
	memcpy(target, e_addr, q->elem_size);

	q->logical_len++;

}

void queue_dequeue(queue *q, void *e_addr)
{
	assert(q->logical_len > 0);

	void* source = (char*) q->elements + q->queue_pos*q->elem_size;
	memcpy(e_addr, source, q->elem_size);
	q->logical_len--;

	queue_drecrease(q);
}

static void queue_grow(queue* q)
{
	if (q->logical_len == q->allocat_len) {
		q->allocat_len += 4;
		q->elements = realloc(q->elements, q->allocat_len * q->elem_size);
	}
}

static void queue_drecrease(queue* q)
{
	if (q->queue_pos++ == (q->allocat_len/2)) {
		for (int i = 0; i < q->logical_len; ++i) {
			void* target = (char*) q->elements + i*q->elem_size;
			void* source = (char*) q->elements + (q->queue_pos + i)*q->elem_size;
			memcpy(target, source, q->elem_size);
		}
		q->allocat_len = q->logical_len + (4 - (q->logical_len % 4));
		q->queue_pos = 0;
		q->last_pos = q->logical_len;
		q->elements = realloc(q->elements, q->allocat_len * q->elem_size);
	}
}
