// /**
 // * \file prog.c
 // * \brief Multiplication of two long numbers that do not fit into the computer's bitmap.
 // * \author Ilyasov Idris IU7-33B
 // * \date September 2018
 // */

 
// #include <stdio.h>
// #include <ctype.h>

// #define SUCCESS 0
// #define INPUT_ERROR -1
// #define OVERFLOW_ERROR -2
// #define EXPON_ERROR -3


// /**
 // * \fn int input(char *const sign_result, int *const num, int *const dad,
                 // int *const dbd, int *const expon)
 // * \brief Inputing number in uneccessary format.
 // * \param [in] sign_result sign of number pointer(+/-).
 // * \param [in] num pointer at digit char array of number .
 // * \param [in] dad pointer at count of digit of number before dot.
 // * \param [in] dbd pointer at count of digit of number after dot.
 // * \param [in] expon pointer at exponent of number.
 // * \return SUCCESS if result is OK, INPUT_ERROR if not.
 // */
// int input(char *const sign_result, short int *const num, short int *const dad,
          // short int *const dbd, int *const expon)
// {
    // // Этапы ввода числа:
    // // (0) - знак,
    // // (1) - до точки,
    // // (2) - после точки
    // int stage = 0;
    // char buffer;
    // //int cnt_exp = 0;
    // *dad = *dbd = 0;
    // *sign_result = '+';
    // *expon = 0;

    // scanf("%c", &buffer);

    // // Цикл считывания символов
    // while (buffer != '\n')
    // {
        // // Изменение этапа ввода при вводе знака и проверка
        // if (buffer == '+' || buffer == '-')
        // {
            // if (stage == 0)
            // {
                // stage = 1;
                // *sign_result = buffer;
            // }
            // else
                // return INPUT_ERROR;
        // }

        // // Проверка на вводимые цифры
        // else if (isdigit(buffer))
        // {
            // // Ввод цифры до запятой
            // if (stage < 2 && (*dad + *dbd < 30))
            // {
                // stage = 1;
                // num[(*dad)++] = (int) buffer - 48;
            // }

            // // Ввод цифры после запятой
            // else if ((*dad + *dbd) < 30)
                // num[*dad + (*dbd)++] = (int) buffer - 48;

            // else
                // return INPUT_ERROR;
        // }

        // // Проверка на ввод точки или запятой
        // else if (buffer == '.' || buffer == ',')
            // if (stage == 2)
                // return INPUT_ERROR;
            // else
                // stage = 2;

        // // Проверка на ввод пробела для ввода порядка
        // else if (buffer == ' ')
        // {
            // if (stage == 3)
                // return INPUT_ERROR;
            // else
                // stage = 3;


            // if (scanf("E %d", expon) != 1 || *expon > 99999 || *expon < -99999)
            // {
                // return INPUT_ERROR;
            // }
        // }

        // // Если введен некорректный символ
        // else
            // return INPUT_ERROR;

        // scanf("%c", &buffer);
    // }

    // // Проверка на ввод как таковой
    // if (*dad || *dbd || *expon)
        // return SUCCESS;
    // else
        // return INPUT_ERROR;
// }

// /**
 // * \fn int mult(const int *num_1, const int *num_2, const int l_num_1,
                // const int l_num_2, int *const res)
 // * \brief multiplication of two long numbers that do not fit into the computer's bitmap.
 // * \param [in] num_1 pointer at number #1.
 // * \param [in] num_2 pointer at number #2.
 // * \param [in] l_num_1 length of number #1.
 // * \param [in] l_num_2 length of number #2.
 // * \param [in] res pointer at result.
 // * \return SUCCESS if result is OK, INPUT_ERROR if not.
 // */
// int mult(const short int *num_1, const short int *num_2, const short int l_num_1,
         // const short int l_num_2, short int *const res)
// {
    // // "Буфер", где будет храниться промежуточная сумма умножения
    // int buffer[60]; 
    
    // // Обнуление переменной с результатом
    // for (int i = 0; i < 60; i++)
        // res[i] = 0;
    
    // // Сама операция умножения
    // for (int i = 0; i < l_num_2; i++)
    // {
        // // Обнуление буфера
        // for (int k = 0; k < 60; k++)
            // buffer[k] = 0;
        
        // // Перемножение разрядов чисел
        // // sur - остаток, перенос на следующий разряд
        // for (int sur = 0, j = 0; j < l_num_1; j++) 
        // {
            // sur += (*(num_2 + l_num_2 - 1 - i))*(*(num_1 + l_num_1 - 1 - j));
            // buffer[59 - i - j] = sur % 10; 
            // sur /= 10;
            
            // if (j == l_num_1 - 1)
                // buffer[58 - i - j] = sur;
        // }
        
        // // Сложение промежуточной суммы и результата
        // for (int sur = 0, k = 59; k >= 0; k--)
        // {
            // sur = sur + res[k]+ buffer[k];
            // res[k] = sur % 10;
            // sur /= 10;
        // }
    // }
    
    // return SUCCESS;
// }


// /**
 // * \fn int output(const char sign_result, int *res, int expon)
 // * \brief output result number in uneccessary format.
 // * \param [in] sign_result sign of result (+/-).
 // * \param [in] res pointer at array of digit of result.
 // * \param [in] expon exponent of number.
 // * \return SUCCESS if all is OK, OVERFLOW_ERROR if overflow.
 // */
// int output(const char sign_result, short int *res, int expon)
// {
    // // Количество цифр в результате
    // short int len_res; 
    // int i = 0;
    
    // // Избавление от незначащих нулей слева
    // while (i < 60 && res[i] == 0)
    // {
        // i++;
    // }
    
    // len_res = 60 - i;
    // res += i;
    
    // // Вычисление и проверка на переполнение порядка
    // expon += len_res;
    
    // if (expon > 99999 || expon < -99999)
    // {
        // printf("Error, wrong input of number!\nProgram was finished (Press ENTER)!");
        // return OVERFLOW_ERROR;
    // }
    
    // // Округление числа до 30 значащих цифр
    // if (len_res > 30)
    // {
        // len_res = 30;
        
        // if (res[30] >= 5)
        // {
            // res[29] += 1;
            
            // for (int i = 29; res[i] == 10; i--)
            // {
                // res[i] = 0;
                // res[i-1] += 1;
            // }
        // }
    // }
    
    // // Избавление от незначащих нулей справа
    // for (int i = len_res - 1; i >= 0; i--)
        // if (res[i] == 0)
            // len_res--;
        // else
            // break;
    
    // // В случае нулевого результата вывод сообщение об этом
    // if (len_res == 0)
        // printf("\nResult is 0.0 E 0\nProgram was finished (Press ENTER)!");
    // // В других случаях обычный вывод
    // else
    // {
        // printf("\nResult is %c0.", sign_result);
        
        // for (int i = 0; i < len_res; i++)
            // printf("%d", res[i]);
        
        // if (expon != 0)
            // printf(" E %d\nProgram was finished (Press ENTER)!", expon);
    // }
    
    // return SUCCESS;
// }

// /**
 // * \fn int main(void)
 // * \brief main function
 // * \return SUCCESS if all is OK, OVERFLOW_ERROR if overflow, INPUT_ERROR if incorrect input.
 // */
// int main(void)
// {   
    // char sign_result, sign_num_1, sign_num_2;  // Знак результата, первого числа, второго числа
    // short int num_1[30], dad_1, dbd_1;         // Цифры первого числа, кол-во знаков до и после точки
    // short int num_2[30], dad_2, dbd_2;         // Цифры второго числа, кол-во знаков до и после точки
    // int expon_1, expon_2;                      // Порядок первого и второго числа
    // short int res[60] = {0};                   // Массив, где будет храниться результат
    // // Вывод вводной информации
    // printf("Lab_01");
    // printf("\n=====================\nILYASOV IDRIS IU7-33B\n=====================\n");
    // printf("Multiplication\n");
    // printf("Input nums in next format: \n(+/-)M.N E (+/-)K\nWhere (M + N) is less than ");
    // printf("31 digits\n             K is less than 6 digits\n=================================");
    // printf("\nFor example: -125.641 E -23\n");
    // printf("\nFirst one:\n______________________________ E _____|\n");

    // // Ввод первого числа
    // if (input(&sign_num_1, num_1, &dad_1, &dbd_1, &expon_1) != SUCCESS)
    // {
        // printf("Error, wrong input number #1!\nProgram was finished (Press ENTER)!");
        // scanf("%c", &sign_num_1);
        // return INPUT_ERROR;
    // }
    
    // // Ввод второго числа
    // printf("\nSecond one:\n______________________________ E _____|\n");
    // if (input(&sign_num_2, num_2, &dad_2, &dbd_2, &expon_2) != SUCCESS)
    // {
        // printf("Error, wrong input number #2!\nProgram was finished (Press ENTER)!");
        // scanf("%c", &sign_num_1);
        // return INPUT_ERROR;
    // }
    
    // // Уменьшение порядка и изменения вида числа, чтобы не было точки
    // expon_1 -= dbd_1;
    // expon_2 -= dbd_2;
    
    // // Выбор нужного знака результата
    // if (sign_num_1 == sign_num_2)
        // sign_result = '+';
    // else 
        // sign_result = '-';
    
    // // Перемножение двух введенных чисел
    // mult(num_1, num_2, dad_1 + dbd_1, dad_2 + dbd_2, res);
    
    // // Вывод реузльтата на экран
    // if (output(sign_result, res, expon_1 + expon_2) != SUCCESS)
    // {
        // printf("Overflow!\nProgram was finished (Press ENTER)!");
        // scanf("%c", &sign_num_1);
        // return OVERFLOW_ERROR;
    // }
       
    // //scanf("%c", &sign_num_1);
    // return SUCCESS;
// }


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
