#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

struct IA
{
    int i;
    int Nk;

    struct IA *next;
};

void generate(int *pa, int m, int n, int percentage);

void input(int *pa, int m, int n);

void count_not_zero(int *pa, int m, int n, int *not_zero_rows, int *not_zero);

void change_matrix(int *pa, int m, int n, int *A, int *JA, struct IA *IA);

void usual_addition(int *pa, int *pb, int *pc, int m, int n);

void moded_addition(int *A1, int *JA1, struct IA *IA1, int not_zero_pa,
                    int *A2, int *JA2, struct IA *IA2, int not_zero_pb,
                    int *A3, int *JA3, struct IA *IA3, int *not_zero_pc);

void copy_rows(int *A1, int *JA1, struct IA *IA1, int max_iel,
               int *A3, int *JA3, struct IA *IA3, int *not_zero_pc);

void addition_rows(int *A1, int *JA1, struct IA *IA1, int max_i1el,
                   int *A2, int *JA2, struct IA *IA2, int max_i2el,
                   int *A3, int *JA3, struct IA *IA3, int *not_zero_pc);

#endif
