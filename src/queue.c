#include "../headers/queue.h"

static void fill_second_stack(queue* q, void* e_addr);

void queue_new(queue *q, int e_size, void(*free_fun)(void*))
{
	assert(e_size > 0);

	q->fst_s = malloc(sizeof(stack));
	q->scd_s = malloc(sizeof(stack));

	stack_new(q->fst_s, e_size, free_fun);
	stack_new(q->scd_s, e_size, free_fun);

	q->e_size = e_size;
	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
	q->free_fun = free_fun;
}

void queue_dispose(queue *q)
{
	stack_dispose(q->fst_s);
	stack_dispose(q->scd_s);

	free(q->fst_s);
	free(q->scd_s);

	q->fst_s = NULL;
	q->scd_s = NULL;

	q->len = 0;
	q->a_len = 0;
}

void queue_enqueue(queue* q, void* e_addr)
{
	stack_push(q->fst_s, e_addr);
	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
}

void queue_dequeue(queue* q, void* e_addr)
{
	assert(q->len > 0);

	if (q->scd_s->logical_len == 0)
		fill_second_stack(q, e_addr);

	stack_pop(q->scd_s, e_addr);
	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
}

static void fill_second_stack(queue* q, void* e_addr)
{
	while (q->fst_s->logical_len > 0) {
		stack_pop(q->fst_s, e_addr);
		stack_push(q->scd_s, e_addr);
	}
}
