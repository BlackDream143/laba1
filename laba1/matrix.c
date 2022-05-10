#include "matrix.h"

int input_size(int* n, int* m)
{
    printf("Введите кол-во строк и столбцов:\n");

    if (scanf("%d %d", n, m) != 2)
        return EXIT_FAILURE;


    if (n <= 0 || m <= 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

matrix_t* allocate_matrix(int n, int m, size_t size)
{

    matrix_t* tmp = malloc(sizeof(matrix_t));
    if (tmp == NULL)
        return NULL;

    tmp->n = n;
    tmp->m = m;
    tmp->size = size;

    tmp->data = malloc(size * n * m + size);
    if (tmp->data == NULL)
        return NULL;

    return tmp;
}

int fill_matrix(matrix_t* matrix)
{
    printf("Вводите элементы матрицы:\n");
    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = 0; j < matrix->m; j++)
        {
            if (matrix->size == sizeof(double))
            {
                double tmp;
                if (scanf("%lf", &tmp) != 1)
                    return EXIT_FAILURE;

                memcpy(matrix->data + (matrix->m * i + j) * matrix->size, &tmp, matrix->size);
            }
            else
            {
                double a, b;
                double complex res;
                if (scanf("%lf%lf", &a, &b) != 2)
                    return EXIT_FAILURE;
                res = a + b * I;
                memcpy(matrix->data + (matrix->m * i + j) * matrix->size, &res, matrix->size);
            }

        }
    }
    return EXIT_SUCCESS;
}

void show_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)

        {
            if (matrix.size == sizeof(double))
                printf("%lf ", *(double*)(matrix.data + (matrix.m * i + j) * matrix.size));
            else
                printf("%f + %fi ", creal(*(double complex*) (matrix.data + (matrix.m * i + j) * matrix.size)),
                    cimag(*(double complex*) (matrix.data + (matrix.m * i + j) * matrix.size)));
        }

        printf("\n");
    }
}

void sum_matrix(matrix_t matrix_a, matrix_t matrix_b, matrix_t* matrix_res)
{
    for (int i = 0; i < matrix_res->n; i++)
        for (int j = 0; j < matrix_res->m; j++)
        {


            if (matrix_res->size == sizeof(double))
            {
                double a, b, s;
                a = *(double*)(matrix_a.data + (matrix_a.m * i + j) * matrix_a.size);
                b = *(double*)(matrix_b.data + (matrix_b.m * i + j) * matrix_b.size);
                s = a + b;
                memcpy(matrix_res->data + (matrix_res->m * i + j) * matrix_res->size, &s, matrix_res->size);
            }
            else
            {
                double complex a, b, s;
                a = *(double complex*) (matrix_a.data + (matrix_a.m * i + j) * matrix_a.size);
                b = *(double complex*) (matrix_b.data + (matrix_b.m * i + j) * matrix_b.size);
                s = a + b;
                memcpy(matrix_res->data + (matrix_res->m * i + j) * matrix_res->size, &s, matrix_res->size);
            }

        }

    show_matrix(*matrix_res);
}

void free_matrix(matrix_t* matrix)
{

    free(matrix->data);
    free(matrix);
}

void multiply_matrix(matrix_t matrix_a, matrix_t matrix_b, matrix_t* matrix_res)
{

    for (int i = 0; i < matrix_res->n; i++)
        for (int j = 0; j < matrix_res->m; j++)
        {
            double s = 0;
            double complex sc = 0;
            for (int k = 0; k < matrix_a.m; k++)
            {
                if (matrix_res->size == sizeof(double))
                {
                    double a = *(double*)(matrix_a.data + (matrix_a.m * i + k) * matrix_a.size);
                    double b = *(double*)(matrix_b.data + (matrix_b.m * k + j) * matrix_b.size);
                    s += a * b;
                }
                else
                {
                    double complex a = *(double complex*) (matrix_a.data + (matrix_a.m * i + k) * matrix_a.size);
                    double complex b = *(double complex*) (matrix_b.data + (matrix_b.m * k + j) * matrix_b.size);
                    sc += a * b;
                }
            }
            if (matrix_res->size == sizeof(double))
                memcpy(matrix_res->data + (matrix_res->m * i + j) * matrix_res->size, &s, matrix_res->size);
            else
                memcpy(matrix_res->data + (matrix_res->m * i + j) * matrix_res->size, &sc, matrix_res->size);

        }

    show_matrix(*matrix_res);
}

int input_type()
{
    int cmd = 0;
    printf("1. Вещественные числа\n");
    printf("2. Комплесные числа\n");
    int fl;

    do {
        printf("Выберите тип данных:\n");
        fl = scanf("%d", &cmd);
    } while (fl != EOF && cmd != 1 && cmd != 2);

    return cmd;
}

void transponse_matrix(matrix_t matrix_a, matrix_t* matrix_res)
{
    for (int i = 0; i < matrix_a.n; i++)
        for (int j = 0; j < matrix_a.m; j++)
        {
            if (matrix_res->size == sizeof(double))
            {
                double a = *(double*)(matrix_a.data + (matrix_a.m * i + j) * matrix_a.size);
                memcpy(matrix_res->data + (matrix_res->m * j + i) * matrix_res->size, &a, matrix_res->size);
            }
            else
            {
                double complex a = *(double complex*) (matrix_a.data + (matrix_a.m * i + j) * matrix_a.size);
                memcpy(matrix_res->data + (matrix_res->m * j + i) * matrix_res->size, &a, matrix_res->size);
            }
        }

    show_matrix(*matrix_res);
}
