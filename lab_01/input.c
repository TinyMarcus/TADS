#include <stdio.h>
#include <ctype.h>
#include "define.h"
#include "input.h"

/*
int input(char *const sign_result, short int *const num, short int *const dad,
        short int *const dbd, int *const exponon)
{
    // Этапы ввода числа: 
    // (-1) - знак, 
    // (0) - до точки, 
    // (1) - после точки
    int input_stage = 0; 
    char buffer;
    
    *dad = *dbd = 0;
    *sign_result = '+';
    *exponon = 0;
    
    scanf("%c", &buffer);
    

    // Цикл считывания символов
    while (buffer != '\n')
    {   
        // Изменение этапа ввода при вводе знака и проверка
        if (buffer == '+' || buffer == '-')
        {
            if (input_stage == -1)
            {
                input_stage = 0;
                *sign_result = buffer;
            }
            else
            {
                scanf("%c", &buffer);
                return INPUT_ERROR;
            }
        }
        
        // Проверка на вводимые цифры
        else if (isdigit(buffer))
        {
            // Ввод цифры до запятой
            if (input_stage < 1 && (*dad + *dbd < 30)) 
            {
                input_stage = 0;
                num[(*dad)++] = (int)buffer - 48;
            }
            
            // Ввод цифры после запятой
            else if ((*dad + *dbd) < 30) 
                num[*dad + (*dbd)++] = (int)buffer - 48;
                
            else
            {
                scanf("%c", &buffer);
                printf("Error, wrong input of number!\nProgram was finished (Press any key)!");
                return INPUT_ERROR;
            }
        }
        
        // Проверка на ввод точки или запятой 
        else if (buffer == '.' || buffer == ',')
            if (input_stage == 1)
            {
                printf("Error, wrong input of number!\nProgram was finished (Press any key)!");
                scanf("%c", &buffer);
                return INPUT_ERROR;
            }
            else
                input_stage = 1;  
            
        // В случае ввода пробела вводится порядок с "E"
        else if (buffer == ' ')
        {           
            if (scanf("E %d", exponon) != 1 || *exponon > 99999 || *exponon < -99999)
            {
                printf("Error, wrong input of number!\nProgram was finished (Press any key)!");
                scanf("%c", &buffer);
                return INPUT_ERROR;
            }
        }
            
        // При некорректном вводе выводится ошибка
        else
        {
            printf("Error, wrong input of number!\nProgram was finished (Press any key)!");
            scanf("%c", &buffer);
            return INPUT_ERROR;
        }
        
        scanf("%c", &buffer);
    }
    
    // Проверка на ввод чего-либо вообще
    if (*dad || *dbd || *exponon)
        return SUCCESS;
    else
    {
        return INPUT_ERROR;
        scanf("%c", &buffer);
    }
    
}*/

int input(char *const sign_result, short int *const num, short int *const dad,
        short int *const dbd, int *const expon)
{
    // Этапы ввода числа: 
    // (0) - знак, 
    // (1) - до точки, 
    // (2) - после точки
    int stage = 0;
    char buffer;
    
    *dad = *dbd = 0;
    *sign_result = '+';
    *expon = 0;
    
    scanf("%c", &buffer);
    
    // Цикл считывания символов
    while (buffer != '\n')
    {   
        // Изменение этапа ввода при вводе знака и проверка
        if (buffer == '+' || buffer == '-')
        {
            if (stage == 0)
            {
                stage = 1;
                *sign_result = buffer;
            }
            else
                return INPUT_ERROR;
        }
        
        // Проверка на вводимые цифры
        else if (isdigit(buffer))
        {
            // Ввод цифры до запятой
            if (stage < 2 && (*dad + *dbd < 30)) 
            {
                stage = 1;
                num[(*dad)++] = (int) buffer - 48;
            }
            
            // Ввод цифры после запятой
            else if ((*dad + *dbd) < 30) 
                num[*dad + (*dbd)++] = (int) buffer - 48;
                
            else
                return INPUT_ERROR;
        }
        
        // Проверка на ввод точки или запятой 
        else if (buffer == '.')
            if (stage == 2)
                return INPUT_ERROR;
            else
                stage = 2;  
            
        // Проверка на ввод пробела для ввода порядка 
        else if (buffer == ' ')
        {           
            if (scanf("E %d", expon) != 1 || *expon > 99999 || *expon < -99999)
                return INPUT_ERROR;
        }
            
        // Если введен некорректный символ
        else
            return INPUT_ERROR;
        
        scanf("%c", &buffer);
    }
    
    // Проверка на ввод как таковой
    if (*dad || *dbd || *expon)
        return SUCCESS;
    else
        return INPUT_ERROR;
}
