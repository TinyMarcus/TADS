#ifndef ACTIONS_H
#define ACTIONS_H

#include "structure.h"

int add_record(struct table_inf** inform, int* const n);

int delete_record(struct table_inf** inform, const char* const deleted_book, int* const n);

int find_book(struct table_inf* arr, const int n, char *industry_type);

void write(FILE *f, const struct table_inf* const array, const int n);

void print(const struct table_inf* const array, const int n);

#endif