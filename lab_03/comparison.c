#include "define.h"
#include "matrix_operations.h"
#include "create.h"

unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}

void comparison(int m, int n, int percentage)
{
    unsigned long long time_b, time_e;

    int *pa, *pb, *pc;
    int not_zero_pa, not_zero_pb, not_zero_pc;
    int not_zero_rows_pa, not_zero_rows_pb, not_zero_rows_pc;

    int *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = NULL, *struct_h;

    printf("-------------------------------------------------------------------------------------------------\n");
    printf("%20d |%22d |", m * n, percentage);

    matrix_allocation(&pa, &pb, &pc, m*n);
    generate(pa, m, n, percentage);
    generate(pb, m, n, percentage);

    time_b = tick();
    for (int i = 0; i < ITER; i++)
        usual_addition(pa, pb, pc, m, n);
    time_e = tick();
    printf("%13d %9db |", (time_e - time_b)/ITER, sizeof(int)*m*n*3);

    count_not_zero(pa, m, n, &not_zero_rows_pa, &not_zero_pa);
    array_allocation(&A1, &JA1, not_zero_pa);

    if (not_zero_rows_pa)
    {
        IA1 = malloc(sizeof(struct IA));
        struct_h = IA1;
        for (int i = 0; i < not_zero_rows_pa - 1; i++) {
            struct_h->next = malloc(sizeof(struct IA));
            struct_h = struct_h->next;
        }
        struct_h->next = NULL;
    }

    change_matrix(pa, m, n, A1, JA1, IA1);

    count_not_zero(pb, m, n, &not_zero_rows_pb, &not_zero_pb);
    array_allocation(&A2, &JA2, not_zero_pb);

    if (not_zero_rows_pb)
    {
        IA2 = malloc(sizeof(struct IA));
        struct_h = IA2;
        for (int i = 0; i < not_zero_rows_pb - 1; i++) {
            struct_h->next = malloc(sizeof(struct IA));
            struct_h = struct_h->next;
        }
        struct_h->next = NULL;
    }
    change_matrix(pb, m, n, A2, JA2, IA2);
    array_allocation(&A3, &JA3, not_zero_pa + not_zero_pb);

    IA3 = malloc(sizeof(struct IA));
    IA3->Nk = -1;
    IA3->i = -1;
    IA3->next = NULL;

    time_b = tick();
    for (int i = 0; i < ITER; i++)
        moded_addition(A1, JA1, IA1, not_zero_pa, A2, JA2, IA2, not_zero_pb, A3, JA3, IA3, &not_zero_pc);
    time_e = tick();

    count_not_zero(pc, n, m, &not_zero_rows_pc, &not_zero_pc);

    int size1 = sizeof(int)*not_zero_pa*2 + sizeof(struct IA)*not_zero_rows_pa;
    int size2 = sizeof(int)*not_zero_pb*2 + sizeof(struct IA)*not_zero_rows_pb;
    int size3 = sizeof(int)*not_zero_pc*2 + sizeof(struct IA)*not_zero_rows_pc;

    printf("%13d %9db\n", (time_e - time_b)/ITER, size1 + size2 + size3);
}
