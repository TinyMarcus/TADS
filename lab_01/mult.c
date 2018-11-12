#include "define.h"
#include "mult.h"


int mult(const short int *num_1, const short int *num_2, const short int l_num_1,
         const short int l_num_2, short int *const res)
{
    // "Буфер", где будет храниться промежуточная сумма умножения
    int buffer[60]; 
    
    // Обнуление переменной с результатом
    for (int i = 0; i < 60; i++)
        res[i] = 0;
    
    // Сама операция умножения
    for (int i = 0; i < l_num_2; i++)
    {
        // Обнуление буфера
        for (int k = 0; k < 60; k++)
            buffer[k] = 0;
        
        // Перемножение разрядов чисел
        // sur - остаток, перенос на следующий разряд
        for (int sur = 0, j = 0; j < l_num_1; j++) 
        {
            sur += (*(num_2 + l_num_2 - 1 - i))*(*(num_1 + l_num_1 - 1 - j));
            buffer[59 - i - j] = sur % 10; 
            sur /= 10;
            
            if (j == l_num_1 - 1)
                buffer[58 - i - j] = sur;
        }
        
        // Сложение промежуточной суммы и результата
        for (int sur = 0, k = 59; k >= 0; k--)
        {
            sur = sur + res[k]+ buffer[k];
            res[k] = sur % 10;
            sur /= 10;
        }
    }
    
    return SUCCESS;
}