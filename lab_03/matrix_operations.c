#include "define.h"
#include "print.h"
#include "matrix_operations.h"

void generate(int *pa, int m, int n, int percentage)
{
    int probability;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            probability = rand() % 100;

            if (probability > percentage)
            {
                pa[i * n + j] = 0;
            }
            else
            {
                pa[i * n + j] = rand() % 10 + 1;
            }
        }
    }
}

void input(int *pa, int m, int n)
{
    int i = 0, j = 0, elem = 0;
    fflush(stdin);

    // printf("\n\n\n%d\n\n\n", n);

    do
    {
        if (i >= 0 && j >= 0 && i < m && j < n)
            pa[i * n + j] = elem;
        else
            printf("Wrong index input!\nMust be (i: [0; %d], j: [0, %d])\n", m - 1, n - 1);

        printf("Input (i j elem): ");
        fflush(stdin);
    }
    while (scanf("%d %d %d", &i, &j, &elem) == 3);
}

void count_not_zero(int *pa, int m, int n, int *not_zero_rows, int *not_zero)
{
    *not_zero_rows = 0;
    *not_zero = 0;

    int quantity_rows = 0;

    for (int i = 0; i < m; i++)
    {
        quantity_rows = 0;
        for (int j = 0; j < n; j++)
        {
            if (pa[i * n + j] != 0)
            {
                (*not_zero)++;

                if (!quantity_rows)
                {
                    quantity_rows = 1;
                    (*not_zero_rows)++;
                }
            }
        }
    }
}

void change_matrix(int *pa, int m, int n, int *A, int *JA, struct IA *IA)
{
    int A_curr = 0;
    int An_curr = 0;
    int first_in_row = 1;

    for (int i = 0; i < m; i++)
    {
        first_in_row = 1;
        for (int j = 0; j < n; j++)
        {
            if (pa[i * n + j] != 0)
            {
                A[A_curr] = pa[i * n + j];
                JA[A_curr] = j;

                if (first_in_row)
                {
                    first_in_row = 0;
                    IA->Nk = A_curr;
                    IA->i = i;
                    IA = IA->next;
                }
                A_curr++;
            }
        }
    }
}

void usual_addition(int *pa, int *pb, int *pc, int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            pc[i * n + j] = pa[i * n + j] + pb[i * n + j];
}

void moded_addition(int *A1, int *JA1, struct IA *IA1, int not_zero_pa,
                    int *A2, int *JA2, struct IA *IA2, int not_zero_pb,
                    int *A3, int *JA3, struct IA *IA3, int *not_zero_pc)
{
    struct IA *h_struct_1 = IA1, *h_struct_2 = IA2, *h_struct_3 = IA3;
    *not_zero_pc = 0;

    while (h_struct_1 && h_struct_2)
    {
        if (h_struct_1->i < h_struct_2->i)
        {
            copy_rows(A1, JA1, h_struct_1, not_zero_pa, A3, JA3, h_struct_3, not_zero_pc);
            h_struct_1 = h_struct_1->next;
        }
        else if (h_struct_2->i < h_struct_1->i)
        {
            copy_rows(A2, JA2, h_struct_2, not_zero_pb, A3, JA3, h_struct_3, not_zero_pc);
            h_struct_2 = h_struct_2->next;
        }
        else
        {
            addition_rows(A1, JA1, h_struct_1, not_zero_pa, A2, JA2, h_struct_2, not_zero_pb, A3, JA3, h_struct_3, not_zero_pc);
            h_struct_1 = h_struct_1->next;
            h_struct_2 = h_struct_2->next;
        }
        if (h_struct_3->next)
            h_struct_3 = h_struct_3->next;
    }

    while (h_struct_1)
    {
        copy_rows(A1, JA1, h_struct_1, not_zero_pa, A3, JA3, h_struct_3, not_zero_pc);
        h_struct_1 = h_struct_1->next;

        if (h_struct_3->next)
            h_struct_3 = h_struct_3->next;
    }

    while (h_struct_2)
    {
        copy_rows(A2, JA2, h_struct_2, not_zero_pb, A3, JA3, h_struct_3, not_zero_pc);
        h_struct_2 = h_struct_2->next;

        if (h_struct_3->next)
            h_struct_3 = h_struct_3->next;
    }
}

void copy_rows(int *A1, int *JA1, struct IA *IA1, int max_iel,
               int *A3, int *JA3, struct IA *IA3, int *not_zero_pc)
{
    int i_from = IA1->Nk;
    int i_to;

    if (IA1->next)
    {
        i_to = (IA1->next)->Nk;
    }
    else
    {
        i_to = max_iel;
    }

    if (IA3->i != -1)
    {
        IA3->next = malloc(sizeof(struct IA));
        IA3 = IA3->next;
        IA3->next = NULL;
    }

    IA3->i = IA1->i;
    IA3->Nk = *not_zero_pc;

    for (int i = i_from; i < i_to; i++)
    {
        A3[*not_zero_pc] = A1[i];
        JA3[*not_zero_pc] = JA1[i];
        (*not_zero_pc)++;
    }
}

void addition_rows(int *A1, int *JA1, struct IA *IA1, int max_i1el,
                  int *A2, int *JA2, struct IA *IA2, int max_i2el,
                  int *A3, int *JA3, struct IA *IA3, int *not_zero_pc)
{
    if (IA3->i != -1)
    {
        IA3->next = malloc(sizeof(struct IA));
        IA3 = IA3->next;
        IA3->next = NULL;
    }

    IA3->i = IA1->i;
    IA3->Nk = *not_zero_pc;
    int i1_from = IA1->Nk;
    int i1_to, i1 = i1_from;

    if (IA1->next)
        i1_to = (IA1->next)->Nk;
    else
        i1_to = max_i1el;

    int i2_from = IA2->Nk;
    int i2_to, i2 = i2_from;

    if (IA2->next)
        i2_to = (IA2->next)->Nk;
    else
        i2_to = max_i2el;

    while ((i1 < i1_to) && (i2 < i2_to))
    {
        if (JA1[i1] < JA2[i2])
        {
            JA3[*not_zero_pc] = JA1[i1];
            A3[*not_zero_pc] = A1[i1++];
        }
        else if (JA2[i2] < JA1[i1])
        {
            JA3[*not_zero_pc] = JA2[i2];
            A3[*not_zero_pc] = A2[i2++];
        }
        else
        {
            JA3[*not_zero_pc] = JA1[i1];
            A3[*not_zero_pc] = A1[i1++] + A2[i2++];
        }
        (*not_zero_pc)++;
    }

    while (i1 < i1_to)
    {
        JA3[*not_zero_pc] = JA1[i1];
        A3[*not_zero_pc] = A1[i1++];
        (*not_zero_pc)++;
    }

    while (i2 < i2_to)
    {
        JA3[*not_zero_pc] = JA2[i2];
        A3[*not_zero_pc] = A2[i2++];
        (*not_zero_pc)++;
    }
}
