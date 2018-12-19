#ifndef PRINT_H
#define PRINT_H
#include "matrix_operations.h"

void print_matrix(const int *pa, int m, int n);

void print_array(const int *array, int len);

void print_list(struct IA *IA);

void print_moded(const int *A, const int *JA, struct IA *IA, const int n_z_el);

#endif
