#ifndef SORT_TABLE_H
#define SORT_TABLE_H

#include "structure.h"

int table_sort(struct table_inf* pa, int n, int *const table_bubble, int *const table_qsort, int *time_avg_bubble, int *time_avg_qsort);

int key_sort(struct table_inf* pa, int n, int **p, int *const bubble_t, int *const qsort_t, int *time_avg_bubble_key, int *time_avg_qsort_key);
    
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));

void swap(void *i, void *j, int size);

unsigned long long tick(void);

int compare_char(const void *a, const void *b);

int compare_key(const void *a, const void *b);

#endif