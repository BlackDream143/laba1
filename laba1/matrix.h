#pragma once
#ifndef LAB_MATRIX_H
#define LAB_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <string.h>

typedef struct
{
    void* data;
    int n;
    int m;
    size_t size;
} matrix_t;

int input_size(int* n, int* m);
matrix_t* allocate_matrix(int n, int m, size_t size);
int fill_matrix(matrix_t* matrix);
void sum_matrix(matrix_t matrix_a, matrix_t matrix_b, matrix_t* matrix_res);
void free_matrix(matrix_t* matrix);
void multiply_matrix(matrix_t matrix_a, matrix_t matrix_b, matrix_t* matrix_res);
int input_type();
void transponse_matrix(matrix_t matrix_a, matrix_t* matrix_res);

#endif

