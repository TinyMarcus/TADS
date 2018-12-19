#include "arrstack.h"
#include "liststack.h"
#include "analisis.h"

static int max_l = STACKSIZE - 1;
static int max_r = 0;

int push_l1(float num, float stack[], int pos, int side)
{
    if(side == RIGHT)
    {
        if (pos > max_r)
        {
            pos--;
            stack[pos] = num;
            max_l--;
        }
    }
    else if(side == LEFT)
    {
        if(pos < max_l)
        {
            pos++;
            stack[pos] = num;
            max_r++;
        }
    }
    return pos;
}


int pop_l1(float *num, float stack[], int pos, int side)
{
    if(side == RIGHT)
    {
        if(pos != STACKSIZE)
        {
            *num = stack[pos];
            stack[pos] = 0;
            pos++;
            max_l++;
        }
    }
    else if(side == LEFT)
    {
        if (pos != -1)
        {
            *num = stack[pos];
            stack[pos] = 0;
            pos--;
            max_r--;
        }
    }
    return pos;
}

void analise()
{
    double duration1 = -1.0, duration2 = -1.0;
    clock_t t1, t2;
    struct stack stack_arr;
    stack_arr.pos_l = -1;
    stack_arr.pos_r = STACKSIZE;
    StackNode *stack_list = CreateStack();
    float num;
    t1 = clock();
    for(int i = 0; i < 100000000; i++) {
        stack_arr.pos_l = push_l1(NUM, stack_arr.data, stack_arr.pos_l, LEFT);
    }
    t2 = clock();
    duration1 = (double) (t2-t1)/CLOCKS_PER_SEC/2;

    t1 = clock();
    for(int i = 0; i < 100000000; i++)  {
        push(&stack_list, NUM);
    }
    t2 = clock();
    duration2 = (double) (t2-t1)/CLOCKS_PER_SEC;

    printf("The 'push' - operation took %g ms in stack-array "
           "and %g ms in stack-list.\n", duration1, duration2);

    duration1 = 0;
    duration2 = 0;
    t1 = clock();
    for(int i = 0; i < 100000000; i++) {
        stack_arr.pos_l = pop_l1(&num, stack_arr.data, stack_arr.pos_l, LEFT);
    }
    t2 = clock();
    duration1 = (double) (t2-t1)/CLOCKS_PER_SEC/2;

    t1 = clock();
    for(int i = 0; i < 100000000; i++)  {
        pop(&stack_list);
    }
    t2 = clock();
    duration2 = (double) (t2-t1)/CLOCKS_PER_SEC;

    printf("The 'pop' - operation took %g ms in stack-array "
           "and %g ms in stack-list.\n", duration1, duration2);
}
