#include "interface.h"
#include "arrstack.h"
#include "liststack.h"

void info(int size_l, int size_a)
{
    printf("======== INFORMATION ========\n"
           "Stack-list need %ld bytes.\n"
           "Stack-array need %ld bytes.\n",
    	   size_l*sizeof(StackNode), size_a*sizeof(struct stack));
}

void menu()
{
    printf("\n\n========= MAIN MENU =========\n"
           "Stack-array\n"
           "-> [1] - push number on the left stack\n"
           "-> [2] - push number on the right stack\n"
           "-> [3] - pop number out of the left stack\n"
           "-> [4] - pop number out of the right stack\n"
           "\n"
           "Stack-list\n"
           "-> [5] - push number\n"
           "-> [6] - pop number\n"
           "\n"
           "-> [0] - exit\n"
           ""
           "Your choice: ");
}
