#include "../headers/queue.h"

void fill_second_stack(queue* q, void* e_addr);

void queue_new(queue *q, int e_size, void(*free_fun)(void*))
{
	assert(e_size > 0);

	stack* s1 = malloc(sizeof(stack));
	stack* s2 = malloc(sizeof(stack));

	q->fst_s = s1;
	q->scd_s = s2;

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

	q->len = q->fst_s->logical_len + q->scd_s->logical_len;
	q->a_len = q->fst_s->allocat_len + q->scd_s->allocat_len;
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

void fill_second_stack(queue* q, void* e_addr)
{
	while (q->fst_s->logical_len > 0) {
		stack_pop(q->fst_s, e_addr);
		stack_push(q->scd_s, e_addr);
	}
}
