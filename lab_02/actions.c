#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "read_write_file.h"
#include "actions.h"
#include "structure.h"

// Считываем данные и добавляет запись в массив структур
int add_record(struct table_inf** table_el, int* const n)
{
	struct table_inf new;
	
    if ((printf("Author's surname: "), (new.surname = read_word(stdin)) == NULL) ||
		(printf("Book's name: "), (new.book_name = read_word(stdin)) == NULL) ||
	    (printf("Publishing house: "), (new.publishing_house = read_word(stdin)) == NULL) ||
		(printf("Pages: "), scanf("%d", &(new.pages)) != 1 && new.pages < 0) ||
		(printf("Literature type (technical/artistic/children): "), 
		(new.literature_type = read_word(stdin)) == NULL))
        /*if (new.pages < 0)
            return WRONG_INPUT;
        else
            return WRONG_INPUT;*/
        return WRONG_INPUT;
        
		if (new.pages < 0)
            return WRONG_INPUT;
        
		if (strcmp(new.literature_type, "technical") == 0)
		{
			if ((printf("Industry type (engeneering/metallurgy/biology/geography/aviation/physics): "), 
			    (new.industry_type = read_word(stdin)) == NULL) ||
		        (printf("Country (domestic/foreign): "), 
				(new.country = read_word(stdin)) == NULL) || 
                (printf("Published year: "),
                scanf("%d", &(new.published_year)) != 1))
                return WRONG_INPUT;
			
            if (new.published_year > 2018)
                return WRONG_INPUT;
            
			if (strcmp(new.industry_type, "engeneering") != 0 &&
                strcmp(new.industry_type, "metallurgy") != 0 &&
                strcmp(new.industry_type, "biology") != 0 &&
                strcmp(new.industry_type, "geography") != 0 &&
                strcmp(new.industry_type, "aviation") != 0 &&
                strcmp(new.industry_type, "physics") != 0)
                return WRONG_INPUT;
        }				

		else if (strcmp(new.literature_type, "artistic") == 0)
		{
			if (((printf("Genre (novel/play/poems): "), 
			    new.artistic_genre = read_word(stdin)) == NULL) ||
                (strcmp(new.artistic_genre, "novel") != 0 &&
                strcmp(new.artistic_genre, "play") != 0 &&
                strcmp(new.artistic_genre, "poems") != 0))
                return WRONG_INPUT;
            
            /*if (strcmp(new.artistic_genre, "novel") != 0 &&
                strcmp(new.artistic_genre, "play") != 0 &&
                strcmp(new.artistic_genre, "poems") != 0)
                return WRONG_INPUT;*/
		}

        else if (strcmp(new.literature_type, "children") == 0)
		{
			if ((printf("Genre (fairy tales/poems): "), 
			    (new.children_genre = read_word(stdin)) == NULL) || 
                (strcmp(new.children_genre, "fairy tales") != 0 &&	
                strcmp(new.children_genre, "poems") != 0))
                return WRONG_INPUT;	
        }		
        
        else
            return WRONG_INPUT;			
	
    *table_el = realloc(*table_el, (*n + 1) * sizeof((*table_el)[0]));
    if (*table_el == NULL)
	   	return WRONG_ALLOCATION;	
	
	(*table_el)[*n] = new;
	*n = *n + 1;
	
	return SUCCESS;
}
// Удаляем данные из таблицы (позже можно будет выбирать по какому ключу удалять)
int delete_record(struct table_inf** table_el,
    const char* const deleted_book, int* const n)
{
	int flag = 0; //  Был ли удален элемент
	int last_checked = 0; // Индекс за последним проверенным элементом
	
	while (last_checked != *n)	
        for (int i = last_checked; i < *n; i++)
		{
		    if (strcmp((*table_el)[i].book_name, deleted_book) == 0)
            {
		        memmove(*table_el + i, *table_el + i + 1,
				    (*n - i - 1) * sizeof((*table_el)[0]));
                *table_el = realloc(*table_el, (*n - 1) * sizeof((*table_el)[0]));	
			    if (*table_el == NULL)
			    	return WRONG_ALLOCATION;
				
			    *n = *n - 1;
				flag = 1;
				
				break;
            }
			
			last_checked = i + 1;
        }

    if (!flag)
        return NOTHING_DELETED;
    
    return SUCCESS;	
}
// Находим нужную техническую книгу по заданной отрасли
int find_book(struct table_inf* arr, const int n, char *industry_type)
{
	int flag = 0;
	
	for (int i = 0; i < n; i++)
		if (strcmp(arr[i].industry_type, industry_type) == 0 && strcmp(arr[i].country, "domestic") == 0)
		{
			if (flag == 0)
			{
				flag = 1;
                printf("\n-----------------------------------------------\
-----------------------------------------------------------------------------------------------"
		        "\nAuthor's surname              | Book name                    | Publishing house\
      | Pages | Literature type | Industry   | Country   | Year"
		        "\n---------------------------------------------------------------------------\
-------------------------------------------------------------------\n");				
			}
			
			printf("%-30s| %-29s| %-22s| %-6d| %-16s| %-11s| %-10s| %-6d\n", arr[i].surname,
		        arr[i].book_name, arr[i].publishing_house, arr[i].pages,
			    arr[i].literature_type, arr[i].industry_type, arr[i].country, arr[i].published_year);
	    }
	
	if (flag == 0)
		return NOTHING_FOUND;
	return SUCCESS;
}
// Выводим результат в файл
void write(FILE *f, const struct table_inf* const arr, const int n)
{
    for (int i = 0; i < n; i++)
	{
		fprintf(f, "%-1s|%-1s|%-1s|%-1d|%-1s|", arr[i].surname,
		    arr[i].book_name, arr[i].publishing_house, arr[i].pages,
			arr[i].literature_type);
		
		if (strcmp(arr[i].literature_type, "technical") == 0)
            fprintf(f, "%-1s|%-1s|%-1d\n", arr[i].industry_type,
		        arr[i].country, arr[i].published_year);

        else if (strcmp(arr[i].literature_type, "artistic") == 0)
            fprintf(f, "%-1s\n", arr[i].artistic_genre);	

        else if (strcmp(arr[i].literature_type, "children") == 0)
            fprintf(f, "%-1s\n", arr[i].children_genre);	
    }		
}
// Выводим результат на экран
void write_screen(FILE *f, const struct table_inf* const arr, const int n)
{
    for (int i = 0; i < n; i++)
	{
		fprintf(f, "%-30s| %-29s| %-22s| %-6d| %-16s|", arr[i].surname,
		    arr[i].book_name, arr[i].publishing_house, arr[i].pages,
			arr[i].literature_type);
		
		if (strcmp(arr[i].literature_type, "technical") == 0)
            fprintf(f, " %-15s| %-10s| %-7d\n", arr[i].industry_type,
		        arr[i].country, arr[i].published_year);

        else if (strcmp(arr[i].literature_type, "artistic") == 0)
            fprintf(f, " %-15s\n", arr[i].artistic_genre);	

        else if (strcmp(arr[i].literature_type, "children") == 0)
            fprintf(f, " %-15s\n", arr[i].children_genre);	
    }		
}

// Выводим таблицу и её заголовок
void print(const struct table_inf* const arr, const int n)
{
	printf("----------------------------------------------------------------------------------\
-----------------------------------------------------------------"
		"\nAuthor's surname              | Book name                    | Publishing house\
      | Pages | Literature type | Other (Genre/Industry/Country/Year)"
		        "\n---------------------------------------------------------------------------\
------------------------------------------------------------------------\n");
	
	write_screen(stdout, arr, n);
}