#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write_file.h"
#include "actions.h"
#include "define.h"
#include "structure.h"

char* read_word(FILE *file)
{
    char *str = malloc(MAX_LEN_STR * sizeof(char));
    char temp;
    int n = 0;
    // Считываем строку до нужного символа
    while (fscanf(file, "%c", &temp) == 1)
    {
        if (temp == '|' || temp == '\n')
        {
            if (n != 0)
                break;
        }
        else
            *(str + n++) = temp;
    }
    
    if (n == 0)
        return NULL;
    
    *(str + n) = '\0';
    str = realloc(str, (n+1) * sizeof(char));
    
    return str;
}

int read_file(const char *const argv, struct table_inf **p, int *const n)
{
    FILE *file;
    char temp;
    struct table_inf *arr;
    // Открываем и считываем весь файл
    file = fopen(argv, "r");
    
    /*if (file = NULL)
        return WRONG_FILE;*/
    
    while (fscanf(file, "%c", &temp) == 1)
        if (temp == '\n')
            (*n)++;
        
    if (feof(file) == 0)
    {
        fclose(file);
        return WRONG_INPUT;
    }
    
    if (*n == 0)
    {
        fclose(file);
        return EMPTY_ARRAY;
    }
    
    rewind(file);
    
    arr = malloc(*n * sizeof(struct table_inf));
    *p = arr;
    
    if (arr == NULL)
    {
    	fclose(file);
        return WRONG_ALLOCATION;
	}
    // Записываем данные в массив согласно нашей структуре
    for (int i = 0; i < *n; i++)
	{
	    if ((arr[i].surname = read_word(file)) == NULL ||
		    (arr[i].book_name = read_word(file)) == NULL ||
			(arr[i].publishing_house = read_word(file)) == NULL ||
			(fscanf(file, "%d", &(arr[i].pages))) != 1 ||
            (arr[i].pages < 0) ||
			(arr[i].literature_type = read_word(file)) == NULL)
		{
            fclose(file);
			free(arr);
			return WRONG_INPUT;
		}
		
		if (strcmp(arr[i].literature_type, "technical") == 0)
		{
			if ((arr[i].industry_type = read_word(file)) == NULL || 
                (arr[i].country = read_word(file)) == NULL ||
                (fscanf(file, "%d", &(arr[i].published_year)) != 1) ||
                arr[i].published_year > 2018)
			{
                fclose(file);
				free(arr);
				return WRONG_INPUT;
            }

            /*if (arr[i].published_year > 2018)
            {
                fclose(file);
                free(arr);
                return WRONG_INPUT;
            }*/
		}

		else if (strcmp(arr[i].literature_type, "artistic") == 0)
		{
			if ((arr[i].artistic_genre = read_word(file)) == NULL)
			{
                fclose(file);
				free(arr);
				return WRONG_INPUT;
            }				
		}

        else if (strcmp(arr[i].literature_type, "children") == 0)
		{
			if ((arr[i].children_genre = read_word(file)) == NULL)
			{
				fclose(file);
				free(arr);
                return WRONG_INPUT;	
			}
        }		
        
        else
		{
			fclose(file);
			free(arr);
            return WRONG_INPUT;
		}

        if (strcmp(arr[i].literature_type, "technical") == 0 &&
            strcmp(arr[i].country, "domestic") != 0 &&
            strcmp(arr[i].country, "foreign") != 0 &&
            strcmp(arr[i].industry_type, "engeneering") != 0 &&
            strcmp(arr[i].industry_type, "metallurgy") != 0 &&
            strcmp(arr[i].industry_type, "biology") != 0 &&
            strcmp(arr[i].industry_type, "geography") != 0 &&
            strcmp(arr[i].industry_type, "aviation") != 0 &&
            strcmp(arr[i].industry_type, "physics") != 0)
		{
			fclose(file);
			free(arr);
            return WRONG_INPUT;
		}
			
        else if (strcmp(arr[i].literature_type, "artistic") == 0 &&
            strcmp(arr[i].artistic_genre, "novel") != 0 &&	
            strcmp(arr[i].artistic_genre, "play") != 0 &&
            strcmp(arr[i].artistic_genre, "poems") != 0)
		{
			fclose(file);
			free(arr);
            return WRONG_INPUT;
        }

        else if (strcmp(arr[i].literature_type, "children") == 0 &&
            strcmp(arr[i].children_genre, "fairy tales") != 0 &&	
            strcmp(arr[i].children_genre, "poems") != 0)
		{
			fclose(file);
			free(arr);
            return WRONG_INPUT;
        }	
	}
	
	while (fscanf(file, "%c", &temp) == 1)
	    if (!(temp == '\n' || temp == '|'))
		{
			fclose(file);
			free(arr);
		    return WRONG_INPUT;
		}
	
	if (feof(file) == 0)
	{
		fclose(file);
		free(arr);
        return WRONG_INPUT;
	}
	
	fclose(file);
	return SUCCESS;
}
 
int write_file(const char *const argv, const struct table_inf *const arr, const int n)
{
	FILE *file;
    // Записываем нашу таблицу в файл
	file = fopen(argv, "w");
    if (file == NULL) 
        return WRONG_FILE;

    write(file, arr, n);
	
	fclose(file);
	return SUCCESS;
} 