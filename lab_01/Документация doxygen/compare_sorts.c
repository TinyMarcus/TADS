#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_LEN 10
#define MAX_LEN 10000000
#define SUCCESS 0

unsigned long long tick();
void create_array(int *pa, int *pb, int length);
void swap(void *a, void *b, size_t size);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int compare(const void *p, const void *q);

int main()
{
    int *pa;
    int *pb;
    int length = MIN_LEN;
    int step = 10;
    unsigned long long tb, te;

    while (length <= MAX_LEN)
    {
        pa = malloc(length * sizeof(int));
        pb = malloc(length * sizeof(int));
        create_array(pa, pb, length);

        printf("\nLength of array: %d\n", length);
        tb = tick();
        mysort((void*)pa, length, sizeof(int), compare);
        te = tick();
        printf("mysort (modified bubble sort 3): %I64d\n", (te - tb));

        tb = tick();
        qsort((void*)pb, length, sizeof(int), compare);
        te = tick();
        printf("qsort: %I64d\n=======================", (te - tb));
        length *= step;
        free(pa);
        free(pb);
        scanf("%d", &length);
    }

    return SUCCESS;
}

unsigned long long tick()
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));

    return d;
}

void create_array(int *pa, int *pb, int length)
{
    srand(time(NULL));

    for (int i = 0; i < length; i++)
    {
        pa[i] = rand();
        pb[i] = pa[i];
    }
}

void swap(void *a, void *b, size_t size)
{
    int *a_help, *b_help, help_var;
    a_help = a; b_help = b;

    while (size-- > 0)
    {
        help_var = *a_help;
        *a_help = *b_help;
        *b_help = help_var;

        a_help += 1;
        b_help += 1;
    }
}

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *pb_dst = base;
    char *pe_dst = pb_dst + (nmemb - 1) * size;
    char *pa = base;
    char *p_ind;

    while (pb_dst != pe_dst)
    {
        for (p_ind = pb_dst; p_ind < pe_dst; p_ind += size)
        {
            if (compar(p_ind, p_ind + size) > 0)
            {
                swap(p_ind, p_ind + size, size);
                pa = p_ind;
            }
        }

        pe_dst = pa;

        for (p_ind = pe_dst - size; p_ind >= pb_dst; p_ind -= size)
        {
            if (compar(p_ind, p_ind + size) > 0)
            {
                swap(p_ind, p_ind + size, size);
                pa = p_ind + size;
            }
        }

        pb_dst = pa;
    }
}

int compare(const void *p, const void *q)
{
    return *(int*)p - *(int*)q;
}
