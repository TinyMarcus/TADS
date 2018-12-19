#ifndef GRAPH_H
#define GRAPH_H

int **allocate_matrix(int n, int m);

int **fill_matrix(FILE *file_in, int **matrix, int cnt);

void print_matrix(int **matrix, int cnt, int flag);

void get_graph(int **matrix, int cnt);

void get_graph_prim(int cnt, int **matrix, int *vector);

int *dijkstra(int cnt, int **matrix, int v0, int *min_len);

int minimum(int a, int b);

int **floyd_warshall(int n, int **matrix, int **short_matrix);

int connected_graph(int **short_matrix, int **matrix, int cnt);

int first_zero(int *arr, int n);

int *prim(int **matrix, int *res, int cnt, int v0);

#endif
