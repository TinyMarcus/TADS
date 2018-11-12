#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "read_write_file.h"
#include "actions.h"
#include "define.h"
#include "sorts.h"
#include "structure.h"

#define TRUE 1
#define FALSE 0

struct table_inf *arr = NULL;

// Главная функция
int main(const int argc, const char **argv)
{
    // Объявляем начальную длину строки, задаем все переменные
    int n = 0, result, choice, *key_arr = NULL;
    int table_bubble = 0, table_qsort = 0, key_bubble = 0, key_qsort = 0;
    char industry_type[25];
    int check = TRUE;
    int time_avg_bubble = 0, time_avg_bubble_key = 0;
    int time_avg_qsort = 0, time_avg_qsort_key = 0;
    
    // Проверка на входные параметры командной строки
    if (argc != 2)
    {
        printf("Wrong parameters of commandline\nMust be: main.exe <input_file>\n");
		return WRONG_PARAMS;
    }

    // Записываем в переменную возвращаемый код функцией read_file
    result = read_file(argv[1], &arr, &n);
    
    // Проверяем, что вернула функция
    if (result == WRONG_FILE)
    {
        printf("Can't open this file: %s\n", strerror(errno));
		return WRONG_FILE;
    }
    else if (result == WRONG_INPUT)
    {
        printf("Wrong input\n");
        return WRONG_INPUT;
    }
    else if (result == EMPTY_ARRAY)
    {
        printf("Array is empty\n");
        return EMPTY_ARRAY;
    }
    else if (result == WRONG_ALLOCATION)
    {
        printf("Wrong allocation\n");
        return WRONG_ALLOCATION;
    }
    
    // Открываем меню
    while (check)
    {
        printf("\n\nMENU:\n"
        "0. Print table on screen.\n"
		"1. Add record to table.\n"
		"2. Delete record from table.\n"
        "3. Find book.\n"
		"4. Sort table.\n"
        "5. Sort and print array of keys (bubble and qsort).\n"
        "6. Print sorted table by array of keys.\n"
        "7. Compare efficiency.\n"
		"8. Save to file.\n"
        "9. Exit.\n\n"
        "> ");
		
		// Проверяем ввод
		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 9)
		{
			free(arr);
			free(key_arr);
			printf("Wrong input\n");
            continue;
			//return WRONG_INPUT;
		}	
        // Выводим таблицу на экран
        else if (choice == 0)
        {
            printf("\n");
            print(arr, n);
        }
        // Добавляем запись в таблицу
        else if (choice == 1)
        {
			//printf("\n-----------------------------------------------\n");
			
			result = add_record(&arr, &n);
			if (result == WRONG_ALLOCATION)
			{
				printf("\nWrong allocation\n");
				free(key_arr);
				return result;
			}
			else if (result == WRONG_INPUT)
				printf("\nWrong input\n");
			
			else
			    printf("Record was added to table");
            table_bubble = 0;
            table_qsort = 0; 
            key_bubble = 0;
            key_qsort = 0;
            time_avg_bubble = 0;
            time_avg_qsort = 0;
            time_avg_qsort_key = 0;
            time_avg_bubble_key = 0;
            
        }
        // Удаляем запись из таблицы
        else if (choice == 2)
        {
            printf("Delete book: ");
			result = delete_record(&arr, read_word(stdin), &n);
			//printf("-----------------------------------------------\n");
			if (result == WRONG_ALLOCATION)
			{
				printf("Wrong allocation\n");
				free(key_arr);
				return result;
			}
			else if (result == NOTHING_DELETED)
				printf("You deleted nothing\n");
			else
				printf("All is done\n");
            table_bubble = 0;
            table_qsort = 0; 
            key_bubble = 0;
            key_qsort = 0;
            time_avg_bubble = 0;
            time_avg_qsort = 0;
            time_avg_qsort_key = 0;
            time_avg_bubble_key = 0;
        }
        // Проводим поиск по нужной отрасли
        else if (choice == 3)
		{
		    printf("Industry type (engeneering/metallurgy/biology/geography/aviation/physics): ");
          
			if (scanf("%s", industry_type) == 1 && (strcmp(industry_type,
     			"engeneering") == 0 || strcmp(industry_type, "metallurgy") ==
				0 || strcmp(industry_type, "biology") == 0 
                || strcmp(industry_type, "geography") == 0 ||
                strcmp(industry_type, "aviation") == 0 || 
                strcmp(industry_type, "physics") == 0))
			{
				if (find_book(arr, n, industry_type))
					printf("There is no books of this type of industry\n");
			}
			else
				printf("Wrong input");
		}
        // Сортируем таблицу
        else if (choice == 4)
        {
            if (table_sort(arr, n, &table_bubble, &table_qsort, &time_avg_bubble, &time_avg_qsort) == WRONG_ALLOCATION)
                printf("Wrong allocation\n");
            
            printf("Sorted\n\nbubble table_sort time (in tacts): %d\nqsort time (in tacts): %d\n\n", time_avg_bubble, time_avg_qsort);
        }
        // Сортируем массив ключей
        else if (choice == 5)
        {
            key_sort(arr, n, &key_arr, &key_bubble, &key_qsort, &time_avg_bubble_key, &time_avg_qsort_key); 
			
			printf("Sorted\nbubble table_sort time (in tacts): %d\nqsort time (in tacts): %d\n", time_avg_bubble_key, time_avg_qsort_key);
			
			for (int i = 0; i < n; i++)
				printf("%2d) %-2d %s\n", i + 1, key_arr[i], arr[key_arr[i]].surname);
		}
        // Выводим таблицу, отсортированную по массиву ключей
        else if (choice == 6)
		{
			if (!key_bubble)
				key_sort(arr, n, &key_arr, &key_bubble,
			        &key_qsort, &time_avg_bubble_key, &time_avg_qsort_key);
			
			for (int i, j = 0; j < n; j++)
	        {
				i = key_arr[j];
				
		        printf("%-30s| %-29s| %-22s| %-6d| %-17s|", arr[i].surname,
		            arr[i].book_name, arr[i].publishing_house, arr[i].pages,
			        arr[i].literature_type);
		
		        if (strcmp(arr[i].literature_type, "technical") == 0)
                    fprintf(stdout, "%-15s| %-10s| %-7d\n", arr[i].industry_type,
                        arr[i].country, arr[i].published_year);

                else if (strcmp(arr[i].literature_type, "artistic") == 0)
                    fprintf(stdout, "%-15s\n", arr[i].artistic_genre);	

                else if (strcmp(arr[i].literature_type, "children") == 0)
                    fprintf(stdout, "%-15s\n", arr[i].children_genre);	
		    }
		}
        // Оцениваем эффективность сортировок (по памяти и по времени)
        else if (choice == 7)
        {
            if (!key_bubble)// || !key_qsort)
                key_sort(arr, n, &key_arr, &key_bubble, &key_qsort, &time_avg_bubble_key, &time_avg_qsort_key);
            
            if (!table_bubble)// || !table_qsort)
                table_sort(arr, n, &table_bubble, &table_qsort, &time_avg_bubble, &time_avg_qsort);
            
            printf("\nEfficiency test time:            Table sort         Key array sort\n"
                   "bubble sort:                       100%%               %f%%         \n"
                   "qsort:                             100%%               %f%%       \n\n",
                   (float)time_avg_bubble_key/time_avg_bubble * 100, (float)time_avg_qsort_key/time_avg_qsort * 100);
            

            printf("----------------------------------------------------------------------"
                   "\nEfficiency test memory:          Table sort         Key array sort\n"
                   "                                   100%%               %f%%       \n\n",
                   (float)sizeof(key_arr[0]) / sizeof(arr[0]) * 100 + 100);
            //printf("\n%f %f\n", (float)(key_bubble/table_bubble * 100), (float)(key_qsort/table_qsort * 100));
        }
         
        // Записываем таблицу в текущий файл
        else if (choice == 8)
        {
            write_file(argv[1], arr, n);
            printf("Information was saved in file");
        }
        // Выходим из программы
        else if (choice == 9)
        {
            check = FALSE;
            break;
        }
	}
    
    return SUCCESS;
}