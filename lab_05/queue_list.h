#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include "define.h"
#include "request.h"

struct queue_list
{
	int length;
	struct request *in, *out;
};

int fragmentation(void);

void init_queue_list(struct queue_list *queue);

void qin_list(struct queue_list *queue, struct request *new);

int is_empty_queue_list(struct queue_list *queue);

struct request qout_list(struct queue_list *queue);

void create_new_request_list(struct  request *new, float t1, float t2, float t3, float t4);

void waiting_in_queue_list(struct queue_list *queue, float t);

void list(void);

void print_table(struct queue_list *queue);

#endif
