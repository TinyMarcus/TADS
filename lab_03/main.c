#include "define.h"
#include "read.h"
#include "free.h"
#include "create.h"
#include "matrix_operations.h"
#include "print.h"
#include "comparison.h"

int main()
{
    srand(time(NULL));

    int result, key = 0, percentage = 100, *pa, *pb, *pc, m, n;
    int not_zero_pa, not_zero_pb, not_zero_pc;
    int not_zero_rows_pa, not_zero_rows_pb;
    int *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = NULL, *h_struct;

    // printf("\n=======================================================================\n");
    printf("This program calculates addition of two int matrixes "\
    "(using usual way and advanced way)!\nIf you want to test time, input 'n' or 'N'");
    // printf("\n=======================================================================\n");
    result = read_key("\nAdd two matrixes?\nYour answer ");
    // printf("\n=======================================================================\n");

    if (result)
    {
        result = read_key("\nInput two matrix by yourself (or generate matrix)?\nYour answer ");
        // printf("\n=======================================================================\n");
        read_size("Input num of rows and cols of matrixes (M N): ", &m, &n);
        // printf("\n=======================================================================\n");

        key = matrix_allocation(&pa, &pb, &pc, m * n);
        if (key)
        {
            printf("\nWrong allocation!\n");
            return key;
        }

        if (result)
        {
            printf("\n=======================================================================\n");
            printf("Now you can input matrixes. If you want to quit from inputing \
mode, input any char that is not digit!");
            // printf("\n=======================================================================\n");
            printf("Input first matrix:\n");
            input(pa, m, n);
            printf("\nInput second matrix:\n");
            input(pb, m, n);
        }
        else
        {
            generate(pa, m, n, percentage);
            generate(pb, m, n, percentage);
        }

        count_not_zero(pa, m, n, &not_zero_rows_pa, &not_zero_pa);
        array_allocation(&A1, &JA1, not_zero_pa);

        if (not_zero_rows_pa)
        {
            IA1 = malloc(sizeof(struct IA));
            h_struct = IA1;

            for (int i = 0; i < not_zero_rows_pa - 1; i++)
            {
                h_struct->next = malloc(sizeof(struct IA));
                h_struct = h_struct->next;
            }
            h_struct->next = NULL;
        }
        change_matrix(pa, m, n, A1, JA1, IA1);

        count_not_zero(pb, m, n, &not_zero_rows_pb, &not_zero_pb);
        array_allocation(&A2, &JA2, not_zero_pb);

        if (not_zero_rows_pb)
        {
            IA2 = malloc(sizeof(struct IA));
            h_struct = IA2;

            for (int i = 0; i < not_zero_rows_pb - 1; i++)
            {
                h_struct->next = malloc(sizeof(struct IA));
                h_struct = h_struct->next;
            }
            h_struct->next = NULL;
        }

        change_matrix(pb, m, n, A2, JA2, IA2);

        array_allocation(&A3, &JA3, not_zero_pa + not_zero_pb);
        IA3 = malloc(sizeof(struct IA));
        IA3->Nk = -1;
        IA3->i = -1;
        IA3->next = NULL;

        usual_addition(pa, pb, pc, m, n);
        moded_addition(A1, JA1, IA1, not_zero_pa, A2, JA2, IA2, not_zero_pb, A3, JA3, IA3, &not_zero_pc);

        result = read_key("\nPrint matrix? ");

        if (result)
        {
            printf("\nFirst matrix:\n");
            print_matrix(pa, m, n);
            print_moded(A1, JA1, IA1, not_zero_pa);

            printf("\n\nSecond matrix:\n");
            print_matrix(pb, m, n);
            print_moded(A2, JA2, IA2, not_zero_pb);

            printf("\n\nResult matrix:\n");
            print_matrix(pc, m, n);
            print_moded(A3, JA3, IA3, not_zero_pc);
        }

        free_matrix_and_array(pa, A1, JA1, IA1);
        free_matrix_and_array(pb, A2, JA2, IA2);
        free_matrix_and_array(pc, A3, JA3, IA3);
    }

    fflush(stdin);
    printf("\n=======================================================================\n");
    result = read_key("\nTime comparison ");

    if (result)
    {
        printf("Time comparison:\n");
        printf("Quantity of elements | percentage of filling | Usual:  time     memory | Moded:  time     memory\n");
        comparison(5, 5, 5);
        comparison(5, 5, 20);
        comparison(5, 5, 50);
        comparison(50, 50, 7);
        comparison(50, 50, 20);
        comparison(50, 50, 50);
        comparison(100, 100, 5);
        comparison(100, 100, 17);
        comparison(100, 100, 50);
        comparison(200, 200, 5);
        comparison(200, 200, 19);
        comparison(200, 200, 50);
        comparison(300, 300, 5);
        comparison(300, 300, 20);
        comparison(300, 300, 50);
        comparison(400, 400, 5);
        comparison(400, 400, 20);
        comparison(400, 400, 50);
        comparison(500, 500, 5);
        comparison(500, 500, 17);
        comparison(500, 500, 50);
    }

    return SUCCESS;
}
