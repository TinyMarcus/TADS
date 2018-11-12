#include <stdio.h>
#include "define.h"
#include "output.h"

int output(const char sign_result, short int *res, int expon)
{
    // Количество цифр в результате
    short int len_res; 
    int i = 0;
    
    // Избавление от незначащих нулей слева
    while (i < 60 && res[i] == 0)
    {
        i++;
    }
    
    len_res = 60 - i;
    res += i;
    
    // Вычисление и проверка на переполнение порядка
    expon += len_res;
    
    if (expon > 99999 || expon < -99999)
    {
        printf("Error, wrong input of number!\nProgram was finished (Press any key)!");
        return OVERFLOW_ERROR;
    }
    
    // Округление числа до 30 значащих цифр
    if (len_res > 30)
    {
        len_res = 30;
        
        if (res[30] >= 5)
        {
            res[29] += 1;
            
            for (int i = 29; res[i] == 10; i--)
            {
                res[i] = 0;
                res[i-1] += 1;
            }
        }
    }
    
    // Избавление от незначащих нулей справа
    for (int i = len_res - 1; i >= 0; i--)
        if (res[i] == 0)
            len_res--;
        else
            break;
    
    // В случае нулевого результата вывод сообщение об этом
    if (len_res == 0)
        printf("\nResult is 0.0 E 0\nProgram was finished (Press any key)!");
    // В других случаях обычный вывод
    else
    {
        printf("\nResult is %c0.", sign_result);
        
        for (int i = 0; i < len_res; i++)
            printf("%d", res[i]);
        
        if (expon != 0)
            printf(" E %d\nProgram was finished (Press any key)!", expon);
    }
    
    return SUCCESS;
}