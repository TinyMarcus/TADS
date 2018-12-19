#include "define.h"
#include "comparison.h"
#include "queue_arr.h"
#include "queue_list.h"

int main()
{
    srand(time(NULL));
    int choice = -1;
	int count;
    int result;

    do
    {
        idle = 0;
        model = 0;
        n = 0;
        count_in = 0;
        count_work = 0;
        twait = 0;
        t1 = 0, t2 = 5, t3 = 0, t4 = 4;

        printf("\n%sМЕНЮ:\n", CYAN);
        printf("[1] - очередь в виде массива\n");
        printf("[2] - очередь в виде списка\n");
        printf("[3] - проверка фрагментации при работе со списком\n");
        printf("[4] - сравнение времени работы и используемой памяти\n");
        printf("[0] - выход%s\n", RESET);
        printf("\nВаш выбор: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                array();
                break;
            case 2:
                list();
                break;
            case 3:
                result = fragmentation();
                if (result == WRONG_INPUT)
                {
                    return WRONG_INPUT;
                }
                break;
            case 4:
				printf("\nВведите размер очереди: ");
				scanf("%d", &count);
                compare(count);
                break;
            case 0:
                break;
            default:
                printf("%sОшибка! Такого пункта меню не существует!%s\n", RED, RESET);
                return WRONG_INPUT;
        }
    } while (choice != 0);

    return SUCCESS;
}
