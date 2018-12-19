#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include "define.h"
#include "request.h"

struct queue_arr
{
    struct request queue[SIZE];
    int first;
    int last;
};

void init_queue_arr(struct queue_arr *queue);

int qin_arr(struct queue_arr *queue, struct request new);

struct request qout_arr(struct queue_arr *queue);

int is_empty_queue_arr(struct queue_arr *queue);

struct request create_new_request_arr(float t1, float t2, float t3, float t4);

void waiting_in_queue_arr(struct queue_arr *que, float t);

void array();

#endif
