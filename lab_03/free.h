#ifndef FREE_H
#define FREE_H
#include "matrix_operations.h"

void free_list(struct IA *head);

void free_matrix_and_array(int *matr, int *A, int *JA, struct IA *IA);

#endif
