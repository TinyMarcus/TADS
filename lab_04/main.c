#include "arrstack.h"
#include "liststack.h"
#include "interface.h"
#include "analisis.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int choice = 0, fc;
    float num;
    struct stack StLst;
    StLst.pos_l = -1;
    StLst.pos_r = STACKSIZE;
    StackNode *mystack = CreateStack();

    info(STACKSIZE, STACKSIZE);

    while(1)
    {
        menu();
        fflush(stdin);
        fc = scanf("%d", &choice);

        if(fc == 0)
            choice = -1;
        printf("\n------------RESULTS--------------\n");

		switch (choice)
		{
        case 1:
            printf("\nEnter float number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("Wrong input!\n");
            else
                StLst.pos_l = push_l(num, StLst.data, StLst.pos_l, LEFT);
            break;
        case 2:
            printf("\nEnter float number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("Wrong input!\n");
            else
                StLst.pos_r = push_l(num, StLst.data, StLst.pos_r, RIGHT);
            break;
        case 3:
            StLst.pos_l = pop_l(&num, StLst.data, StLst.pos_l, LEFT);
            if(StLst.pos_l != 0)
                printf("\n The pop element is %.4f\n", num);
            break;
        case 4:
            StLst.pos_r = pop_l(&num, StLst.data, StLst.pos_r, RIGHT);
            if(StLst.pos_r != 0)
                printf("\n The pop element is %.4f\n", num);
            break;
        case 5:
            printf("\nEnter number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("Wrong input!\n");
            else
                push(&mystack, num);
            break;
        case 6:
            num = pop(&mystack);
            if(num != STACK_FAILURE)
                printf("\nThe pop element is %.4f\n", num);
            break;
        case 7:
            analise();
            break;
        case 0:
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Wrong choice!\n");
			exit(0);
            break;
        }

        num = 0;
        printf("\n---------------------\n");
        print_stack(mystack);
        printf("\n---------------------\n");
        choice = 0;
        printf("Double stack-array:\n");
        for(int i = 0; i < STACKSIZE; i++)
        {
            if(i <= StLst.pos_l || i >= StLst.pos_r)
                printf("%.4f ", StLst.data[i]);
            else
                printf("| ");
        }

        printf("\n---------------------------------\n");

    }
    return 0;
}
