#include <stdio.h>
#include "define.h"
#include "input.h"
#include "mult.h"
#include "output.h"

int main(void)
{   
    char sign_result, sign_num_1, sign_num_2;  // Знак результата, первого числа, второго числа
    short int num_1[30], dad_1, dbd_1;         // Цифры первого числа, кол-во знаков до и после точки
    short int num_2[30], dad_2, dbd_2;         // Цифры второго числа, кол-во знаков до и после точки
    int expon_1, expon_2;                      // Порядок первого и второго числа
    short int res[60] = {0};                   // Массив, где будет храниться результат
    
    // Вывод вводной информации
    printf("Multiplication\n");
    printf("Input nums in next format: \n(+/-)M.N E (+/-)K\nWhere (M + N) is less than ");
    printf("31 digits\n       K is less than 6 digits\n=================================");
    printf("\nFor example: -125.641 E -23\n");
    printf("First one:\n______________________________ E _____|\n");
    
    // Ввод первого числа
    if (input(&sign_num_1, num_1, &dad_1, &dbd_1, &expon_1) != SUCCESS)
    {
        //printf("Error, wrong input number #1!\nProgram was finished (Press any key)!");   
        scanf("%c%c", &sign_num_1, &sign_num_2);
        return INPUT_ERROR;
    }
    
    // Ввод второго числа
    printf("Second one:\n______________________________ E _____|\n");
    if (input(&sign_num_2, num_2, &dad_2, &dbd_2, &expon_2) != SUCCESS)
    {
        //printf("Error, wrong input number #2!\nProgram was finished (Press any key)!");  
        scanf("%c%c", &sign_num_1, &sign_num_2);
        return INPUT_ERROR;
    }
    
    // Уменьшение порядка и изменения вида числа, чтобы не было точки
    expon_1 -= dbd_1;
    expon_2 -= dbd_2;
    
    // Выбор нужного знака результата
    if (sign_num_1 == sign_num_2)
        sign_result = '+';
    else 
        sign_result = '-';
    
    // Перемножение двух введенных чисел
    mult(num_1, num_2, dad_1 + dbd_1, dad_2 + dbd_2, res);
    
    // Вывод реузльтата на экран
    if (output(sign_result, res, expon_1 + expon_2) != SUCCESS)
    {
        printf("Overflow!\nProgram was finished (Press any key)!"); 
        scanf("%c", &sign_num_1);
        return OVERFLOW_ERROR;
    }       
    scanf("%c", &sign_num_1);
    return SUCCESS;
}