#ifndef ARRSTACK_H
#define ARRSTACK_H
#include <stdio.h>
#define STACKSIZE 6
#define LEFT -1
#define RIGHT 1

struct stack
{
   float data[STACKSIZE * 2];
   int pos_l;
   int pos_r;
};

int push_l(float num, float stack[], int pos, int side);
int pop_l(float *num, float stack[], int pos, int side);

#endif
