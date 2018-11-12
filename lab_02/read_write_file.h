#ifndef READ_WRITE_FILE_H
#define READ_WRITE_FILE_H

#include "structure.h"

char* read_word(FILE *file);

int read_file(const char *const argv, struct table_inf **p, int *const n);

int write_file(const char *const argv, const struct table_inf *const arr, const int n);

#endif