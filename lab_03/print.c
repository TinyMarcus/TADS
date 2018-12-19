#include <stdio.h>
#include "print.h"
#include "matrix_operations.h"

void print_matrix(const int *pa, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", pa[i * n + j]);
        }
        printf("\n");
    }
}

void print_array(const int *array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

void print_list(struct IA *IA)
{
    struct IA *struct_h = IA;

    // printf("\nANi: ");
    // if (struct_h)
    //     for (; struct_h != NULL; struct_h = struct_h->next)
    //         printf("%d ", struct_h->i, &struct_h);


    struct_h = IA;
    printf("\nIA: ");
    if (struct_h)
        for (; struct_h != NULL; struct_h = struct_h->next)
            printf("%d ", struct_h->Nk, &struct_h);
}

void print_moded(const int *A, const int *JA, struct IA *IA, const int not_zero)
{
    printf("\nA: ");
    print_array(A, not_zero);

    printf("\nJA: ");
    print_array(JA, not_zero);

    print_list(IA);
    printf(" ");
}
