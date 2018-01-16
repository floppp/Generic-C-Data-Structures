#include "../headers/queue.h"

static void fill_second_queue();
// static void queue_grow(queue* q);
// static void queue_drecrease(queue* q);

void queue_new(queue *q, int e_size, void(*free_fun)(void*))
{
	assert(e_size > 0);

	stack_new(&q->fst_s, e_size, free_fun);
	stack_new(&q->scd_s, e_size, free_fun);

	q->e_size = e_size;
	q->len = QUEUE_LOGICAL_DEFAULT_SIZE;
	q->a_len = QUEUE_ALLOCATED_DEFAULT_SIZE;
	q->free_fun = free_fun;
}i

void queue_dispose(queue *q)
{
	stack_dispose(&q->fst_s);
	stack_dispose(&q->scd_s);
}

void queue_enqueue(queue *q, void *e_addr)
{
	stack_push(q->fst_s, e_addr);
	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
}

void queue_dequeue(queue *q, void *e_addr)
{
	assert(q->len > 0);

	if (q->scd_s->logical_len == 0) {
		fill_second_queue(q);
	}

	stack_pop(q->scd_s, e_addr);
	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
}

static void fill_second_queue(queue* q)
{
	int end = q->fst_s->logical_len;
	for (int i = 0; i < end; ++i) {
		void* e;
		stack_pop(q->fst_s->elements, &e);
		stack_push(q->scd_s, e);
	}
}
