#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include "define.h"
#include "structure.h"

// Сортируем таблицу и замеряем количество тактов на qsort и mysort (пузырек)
int table_sort(struct table_inf* pa, int n, int *const table_bubble,
    int *const table_qsort, int *time_avg_bubble, int *time_avg_qsort)
{
    int *pc = malloc(n * sizeof(pa[0]));
	int *pb = malloc(n * sizeof(pa[0]));
    
    
	if (pb == NULL)
		return WRONG_ALLOCATION;
    
    if (pc == NULL)
		return WRONG_ALLOCATION;
	
    for (int i = 0; i < 100; i++)
    {
        memcpy(pb, pa, n * sizeof(pa[0]));
        memcpy(pc, pa, n * sizeof(pa[0]));
	
        *table_bubble = tick();
        mysort(pb, n, sizeof(pa[0]), compare_char);
        *table_bubble = tick() - *table_bubble;
        *time_avg_bubble += *table_bubble;
        
        *table_qsort = tick();
        qsort(pc, n, sizeof(pa[0]), compare_char);
        *table_qsort = tick() - *table_qsort;
        *time_avg_qsort += *table_qsort;
        //printf("\n%d\n", *time_avg_bubble);
	}
    
    mysort(pa, n, sizeof(pa[0]), compare_char);
    
    *time_avg_bubble = *time_avg_bubble / 100;
    *time_avg_qsort = *time_avg_qsort / 100;
    
    
    printf("\n%d\n", *time_avg_bubble);
    free(pc);
	free(pb);
	return SUCCESS;
}

// Сортируем массив ключей
int key_sort(struct table_inf* pa, int n, int **p,
    int *const bubble_t, int *const qsort_t, int *time_avg_bubble_key, int *time_avg_qsort_key)
{
	int *pb = malloc(n * sizeof(p[0]));
    int *pc = malloc(n * sizeof(p[0]));
	
	if (!*bubble_t)
		*p = realloc(*p, n * sizeof((*p)[0]));
	
	for (int i = 0; i < n; i++)
		(*p)[i] = i;
	
    for (int i = 0; i < 100; i++)
    {
        memcpy(pb, *p, n * sizeof((*p)[0]));
        memcpy(pc, *p, n * sizeof((*p)[0]));
	
        *bubble_t = tick();
        mysort(*p, n, sizeof((*p)[0]), compare_key);
        *bubble_t = tick() - *bubble_t;
        *time_avg_bubble_key += *bubble_t;
	
        *qsort_t = tick();
        qsort(*p, n, sizeof((*p)[0]), compare_key);
        *qsort_t = tick() - *qsort_t;
        *time_avg_qsort_key += *qsort_t;
        printf("\n%d\n", *time_avg_bubble_key);
    }
    
    *time_avg_bubble_key = *time_avg_bubble_key / 100;
    *time_avg_qsort_key = *time_avg_qsort_key / 100;
	free(pc);
	free(pb);
	return SUCCESS;
}

// Сортируем пузырьком
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    char *p_beg = base;
    char *p_end = p_beg + (num - 1) * size; //< Правый флаг
    char *pa = p_beg;
    
    while (p_beg != p_end)
    {
        for (char *p_ind = p_beg; p_ind < p_end; p_ind += size)
        {
            if (compare(p_ind, p_ind + size) > 0)
            {                
                swap(p_ind, p_ind + size, size);
                pa = p_ind;
            }
        }
        
        p_end = pa;
        
        for (char *p_ind = p_end - size; p_ind >= p_beg; p_ind -= size)
        {
            if (compare(p_ind, p_ind + size) > 0)
            {
                swap(p_ind, p_ind + size, size); 
                pa = p_ind + size;
            }
        }
        p_beg = pa;     
    }
}

// Свапаем два ближайших элемента массива
void swap(void *i, void *j, int size)
{
    int *help_var = malloc(size);
    
    memmove(help_var, i, size);
	memmove(i, j, size);
    memmove(j, help_var, size);
	
	free(help_var);
}

// Функция для замера времени
unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
	
    return d;
}

// Сравниваем строки
int compare_char(const void *a, const void *b)
{
    return strcmp(((struct table_inf*)a)->surname, ((struct table_inf*)b)->surname);	
}

// Сравниваем ключи
int compare_key(const void *a, const void *b)
{
	extern struct table_inf *arr;
	
    return strcmp(arr[*((int*)a)].surname, arr[*((int*)b)].surname);	
}