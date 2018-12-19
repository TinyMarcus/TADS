#include "define.h"
#include "graph.h"

int **allocate_matrix(int n, int m)
{
	int **matrix = malloc(n*sizeof(int*) + n*m*sizeof(int));

	if (!matrix)
	{
		return NULL;
	}

	for (int i = 0; i < n; i++)
	{
		matrix[i] = (int*)((char*)matrix + n*sizeof(int*) + i*m*sizeof(int));
	}

    return matrix;
}

int **fill_matrix(FILE *file, int **matrix, int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt; j++)
		{
			fscanf(file, "%d", &matrix[i][j]);
		}
	}

	return matrix;
}

void print_matrix(int **matrix, int cnt, int flag)
{
	switch(flag)
	{
		case 1:
			for (int i = 0; i < cnt; i++)
			{
				for (int j = 0; j < cnt; j++)
				{
					if (matrix[i][j] == 0)
						printf("   ∞");
					else
						printf("%4d",matrix[i][j]);
				}
				printf("\n");
			}
			break;
		case 2:
			for (int i = 0; i < cnt; i++)
			{
				for (int j = 0; j < cnt; j++)
				{
					if (matrix[i][j] != 0)
						printf("   1");
					else
						printf("%4d", matrix[i][j]);
				}
				printf("\n");
			}
			break;
	}
}

void get_graph(int **matrix, int cnt)
{
	FILE *graph = fopen("graph.gv", "w");
	fprintf(graph, "graph G{\n");

	for (int i = 0; i < cnt; i++)
	{
		fprintf(graph,"%d\n", i + 1);

		for (int j = i; j < cnt; j++)
        {
			if (matrix[i][j] != 0)
            {
				fprintf(graph, "%d -- %d [label=%d, len=2]\n", i + 1, j + 1, matrix[i][j]);
            }
        }
	}

	fprintf(graph, "}");
	fclose(graph);
}

void get_graph_prim(int cnt, int **matrix, int *vector)
{
	FILE *graph = fopen("graph_prim.gv", "w");
	fprintf(graph, "graph G{\n");

    for (int i = 0; i < cnt; i++)
	{
		for (int j = i; j < cnt; j++)
        {
			if (matrix[i][j] != INFINITY)
            {
				fprintf(graph, "%d -- %d [label=%d]\n", i+1, j+1, matrix[i][j]);
            }
        }
	}

	for (int i = 0; i < cnt-1; i++)
	{
		fprintf(graph, "%d -- %d [color=blue]\n", vector[i]+1, vector[i+1]+1);
	}

	fprintf(graph, "}");
	fclose(graph);
}

int *dijkstra(int cnt, int **matrix, int v0, int *min_len)
{
	int already_used[cnt];
	int min_ind, min, tmp;

    for (int i = 0; i < cnt; i++)
	{
		min_len[i] = INFINITY;
		already_used[i] = 1;
	}
	min_len[v0] = 0;

    do
	{
		min_ind = INFINITY;
		min = INFINITY;
		for (int i = 0; i < cnt; i++)
		{
			if (already_used[i] == 1 && min_len[i] < min)
			{
				min = min_len[i];
				min_ind = i;
			}
		}

		if (min_ind != INFINITY)
		{
			for (int i = 0; i < cnt; i++)
			{
				if (matrix[min_ind][i] > 0)
				{
					tmp = min + matrix[min_ind][i];

        			if (tmp < min_len[i])
                    {
						min_len[i] = tmp;
                    }
				}
			}

			already_used[min_ind] = 0;
		}
	} while (min_ind < INFINITY);

	return min_len;
}

int minimum(int a, int b)
{
	return (a < b) ? a : b;
}

int **floyd_warshall(int n, int **matrix, int **short_matrix)
{
	for (int i = 0; i < n; i++)
    {
		for (int j = 0; j < n; j++)
        {
			if (matrix[i][j] != 0)
            {
				short_matrix[i][j] = matrix[i][j];
            }
			else
            {
				short_matrix[i][j] = INFINITY;
            }
        }
    }

	for (int k = 0; k < n; k++)
    {
		for (int i = 0; i < n; i++)
        {
			for (int j = 0; j < n; j++)
            {
				short_matrix[i][j] = minimum(short_matrix[i][j], short_matrix[i][k]+short_matrix[k][j]);
            }
        }
    }

	for (int i = 0; i < n; i++)
	{
		short_matrix[i][i] = 0;
	}

	return short_matrix;
}

int connected_graph(int **short_matrix, int **matrix, int cnt)
{
	short_matrix = allocate_matrix(cnt, cnt);
	short_matrix = floyd_warshall(cnt, matrix, short_matrix);

    for (int i = 0; i < cnt; i++)
    {
		for (int j = 0; j < cnt; j++)
        {
			if (short_matrix[i][j] == INFINITY)
            {
				return 0;
            }
        }
    }

	return 1;
}

int first_zero(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == 0)
		{
			return i;
		}
	}

	return -1;
}

int *prim(int **matrix, int *result, int cnt, int v0)
{
	for (int i = 0; i < cnt; i++)
    {
		for (int j = 0; j < cnt; j++)
        {
			if (matrix[i][j] == 0)
            {
				matrix[i][j] = INFINITY;
            }
        }
    }
	int *already_used = malloc(cnt* sizeof(int));

    for (int i = 0; i < cnt; i++)
    {
		already_used[i] = 0;
    }
	already_used[v0] = 1;
    result[0] = v0;

    for (int i = 1; i < cnt; i++)
	{
		int min = matrix[v0][first_zero(already_used, cnt)];
		result[i] = first_zero(already_used, cnt);

		for (int j = 0; j < cnt; j++)
        {
			if (matrix[v0][j] < min && already_used[j] == 0)
			{
				min = matrix[v0][j];
				result[i] = j;
			}
        }

		v0 = result[i];
		already_used[v0] = 1;
	}

	return result;
}
