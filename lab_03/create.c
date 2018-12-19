#include "define.h"

int matrix_allocation(int **pa, int **pb, int **pc, int size)
{
    if (size < 0 || size > MAX_SIZE)
    {
        return WRONG_ALLOCATION;
    }

    *pa = calloc(size, sizeof(int));
    *pb = calloc(size, sizeof(int));
    *pc = calloc(size, sizeof(int));

    if (!*pa || !*pb || !*pc)
    {
        return WRONG_ALLOCATION;
    }

    return SUCCESS;

}

void array_allocation(int **a, int **b, int size)
{
    *a = malloc(size * sizeof(int));
    *b = malloc(size * sizeof(int));
}
