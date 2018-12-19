#include "define.h"
#include "matrix_operations.h"

void free_list(struct IA *head)
{
    struct IA *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

void free_matrix_and_array(int *matr, int *A, int *JA, struct IA *IA)
{
    free(matr);
    free(A);
    free(JA);
    free_list(IA);
}
