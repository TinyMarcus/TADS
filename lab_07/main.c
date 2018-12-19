#include "define.h"
#include "graph.h"

int main(void)
{
	int choice = -1;
	int **matrix = NULL;
	int **short_matrix = NULL;
	int cnt;
    FILE *in;

	do
	{
        printf("\n\n%sУсловие\n", GREEN);
        printf("Задана система двусторонних дорог. Для каждой пары городов\n");
        printf("найти длину кратчайшего пути между ними.%s\n", RESET);
		printf("\n%sМеню:\n", CYAN);
		printf("[1] - загрузить граф из файла\n");
		printf("[2] - задать граф вручную\n");
		printf("[3] - вывести граф в файл .png\n");
		printf("[4] - длина кратчайшего пути между каждой парой городов\n");
		printf("[5] - длина кратчайшего пути из одного города до других\n");
		printf("[6] - вывести на экран матрицы кратчайших расстояний\n");
		printf("[7] - проверить связность графа\n");
		printf("[8] - вывести минимальное остовное дерево в файл .png\n");
		printf("[0] - выйти из программы%s\n",RESET);
		printf("\nВведите пункт меню: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				in = fopen("graph.txt", "r");
				fscanf(in,"%d", &cnt);
				matrix = allocate_matrix(cnt, cnt);
				matrix = fill_matrix(in, matrix, cnt);
				printf("Матрица достижимости:\n");
				print_matrix(matrix, cnt, 2);
				printf("Матрица стоимостей:\n");
				print_matrix(matrix, cnt, 1);
				fclose(in);
				break;
			case 2:
				printf("Количество вершин: ");
				scanf("%d", &cnt);
				matrix = allocate_matrix(cnt, cnt);

				for (int i = 0; i < cnt; i++)
                {
					for (int j = 0; j < cnt; j++)
                    {
						matrix[i][j] = 0;
                    }
                }

				int a, b, len;
				printf("\n%sВвод данных. Для завершения введите отрицательные числа.%s\n", GREEN, RESET);

				do
				{
					printf("Введите через пробел номера двух вершин (<= %d) и расстояние между ними: ", cnt);
					scanf("%d %d %d", &a, &b, &len);

					if (a <= cnt && a > 0 && b <= cnt && b > 0 && len > 0)
					{
						matrix[a - 1][b - 1] = len;
						matrix[b - 1][a - 1] = len;
						//printf("[%d][%d] = %d", a-1,b-1,len);
					}
					else
                    {
						if (a < 0 || b < 0 || len < 0)
                        {
							break;
                        }
						else
                        {
							printf("%sНеверный ввод!%s\n", RED, RESET);
                        }
                    }
				} while (a > -1);

				printf("Матрица достижимости:\n");
				print_matrix(matrix, cnt, 2);
				printf("Матрица стоимостей:\n");
				print_matrix(matrix, cnt,1);
				break;
			case 3:
				if (matrix == NULL)
                {
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
                }
				else
				{
					get_graph(matrix, cnt);
					system("/bin/bash /mnt/c/Users/ilyas/Desktop/ТиСД/ЛР7/file.sh");
				}

				break;
			case 4:
				if (!matrix)
                {
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
                }
				else
				{
					printf("%s| Город 1 | Город 2 | Кратчайшее расстояние |\n", WHITE);

                	for (int i = 0; i < cnt; i++)
					{
						int *min_len = malloc(sizeof(int) * cnt);
						min_len = dijkstra(cnt, matrix, i, min_len);

						for (int j = i+1; j < cnt; j++)
						{
							printf("+—————————+—————————+———————————————————————+\n");
							if (min_len[j] != INFINITY)
								printf("|  %2d     |   %2d    |         %3d           |\n", i + 1, j + 1, min_len[j]);
							else
								printf("|  %2d     |   %2d    |           %s∞%s           | %s\n", i + 1, j + 1, RED, RESET, RESET);
						}
					}
					printf("+—————————+—————————+———————————————————————+\n");
				}

				break;
			case 5:
				if (!matrix)
                {
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
                }
				else
				{
					int v0;
					printf("Введите номер начальной вершины(город): ");
					scanf("%d", &v0);
					v0 -= 1;
					int *min_len = malloc(sizeof(int)*cnt);
					min_len = dijkstra(cnt, matrix, v0, min_len);

					for (int i = 0; i < cnt; i++)
                    {
						if (v0 != i)
						{
							if (min_len[i] == INFINITY)
								printf("%s  Из города %d нельзя попасть в город %d               \n%s", RED, v0+1, i+1, RESET);
							else
								printf("%s  Кратчайшее расстояние между городами %d и %d - %3d  \n%s", GREEN, v0+1, i+1, min_len[i], RESET);
						}
                    }
					free(min_len);
				}

				break;
			case 6:
				printf("%sМатрица достижимости (Алгоритм Флойда — Уоршелла): %s\n", GREEN, RESET);
				short_matrix = allocate_matrix(cnt, cnt);
				short_matrix = floyd_warshall(cnt, matrix, short_matrix);

				for (int i = 0; i < cnt; i++)
                {
					for (int j = 0; j < cnt; j++)
                    {
						if (short_matrix[i][j] == INFINITY)
                        {
							short_matrix[i][j] = 0;
                        }
                    }
                }
				print_matrix(short_matrix, cnt, 1);
				free(short_matrix);

				break;
			case 7:
				switch(connected_graph(short_matrix, matrix, cnt))
				{
					case 0:
						printf("%s   Граф несвязный%s\n", RED, RESET);
						break;
					case 1:
						printf("%s   Граф связный%s\n", GREEN, RESET);
						break;
				}
				free(short_matrix);

                break;
			case 8:
				if (matrix == NULL)
				{
					printf("Ошибка!\n");
					break;
				}

				if (connected_graph(short_matrix, matrix, cnt) == 0)
                {
					printf("%sНе удаётся построить!\n%s",RED, RESET);
                }
				else
				{
					int *res = malloc(cnt*sizeof(int));
					int v0;
					printf("Введите начальную вершину: ");
					scanf("%d", &v0);
					res = prim(matrix, res, cnt, v0-1);
					printf("%sМинимальное остовное дерево: \n%s", GREEN, RESET);
					for (int i = 0; i < cnt; i++)
						if (i != cnt-1)
							printf("%d -> ", res[i] + 1);
						else
							printf("%d\n", res[i] + 1);
					get_graph_prim(cnt, matrix, res);
					system("/bin/bash /mnt/c/Users/ilyas/Desktop/ТиСД/ЛР7/file_prim.sh");
					free(res);
				}

				break;
			case 0:
				free(matrix);
				break;
			default:
				printf("%sПункт меню выбран неверно!%s\n", RED, RESET);
				break;
		}
	} while (choice != 0);
}
