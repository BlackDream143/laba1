#include "check_matrix.h"

#include <stdlib.h>
#include <stdio.h>

matrix_t create_matrix_double(int n, int m, int mode)
{
    matrix_t matrix;
    matrix.m = m;
    matrix.n = n;
    matrix.size = sizeof(double);
    matrix.data = malloc(sizeof(double) * m * n);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
        {
            double a;
            if (mode == 0)
                a = i * j + j;
            else
                a = j + 2 * i;
            memcpy(matrix.data + (matrix.m * i + j) * matrix.size, &a, matrix.size);
        }

    return matrix;
}

matrix_t create_matrix_complex(int n, int m, int mode)
{
    matrix_t matrix;
    matrix.m = m;
    matrix.n = n;
    matrix.size = sizeof(double complex);
    matrix.data = malloc(sizeof(double complex) * m * n);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
        {
            double complex a;
            if (mode == 0)
                a = i * j + j * I;
            else
                a = j + 2 * i * I;
            memcpy(matrix.data + (matrix.m * i + j) * matrix.size, &a, matrix.size);
        }

    return matrix;
}

START_TEST(test_sum_square_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 2, 0);
    matrix_t matrix_b = create_matrix_double(2, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    sum_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[4] = { 0, 2, 2, 5 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_sum_rect_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 3, 0);
    matrix_t matrix_b = create_matrix_double(2, 3, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 3;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    sum_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[6] = { 0, 2, 4, 2, 5, 8 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }
    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_multiply_square_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 2, 0);
    matrix_t matrix_b = create_matrix_double(2, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    multiply_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[4] = { 2, 3, 4, 6 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_multiply_rect_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 3, 0);
    matrix_t matrix_b = create_matrix_double(3, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 3;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    multiply_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[6] = { 10, 13, 4, 20, 26, 8 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_transponse_square_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 2, 0);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    transponse_matrix(matrix_a, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[4] = { 0, 0, 1, 2 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_transponse_rect_matrix_double)
{
    matrix_t matrix_a = create_matrix_double(2, 3, 0);
    matrix_t matrix_res;
    matrix_res.n = 3;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double);
    matrix_res.data = malloc(sizeof(double) * matrix_res.m * matrix_res.n);

    transponse_matrix(matrix_a, &matrix_res);
    int rc = 0;
    int c = 0;
    double res[6] = { 0, 0, 1, 2, 2, 4 };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double val = *(double*)(matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (res[c] != val)
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_sum_square_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 2, 0);
    matrix_t matrix_b = create_matrix_complex(2, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    sum_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[4] = { 0 + 0 * I, 1 + 1 * I, 0 + 2 * I, 2 + 3 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_sum_rect_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 3, 0);
    matrix_t matrix_b = create_matrix_complex(2, 3, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 3;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    sum_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[6] = { 0 + 0 * I, 1 + 1 * I, 2 + 2 * I, 0 + 2 * I, 2 + 3 * I, 4 + 4 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);

            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }
    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_multiply_square_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 2, 0);
    matrix_t matrix_b = create_matrix_complex(2, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    multiply_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[4] = { -2 + 0 * I, -2 + 1 * I, -2 + 2 * I, -1 + 3 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);

            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }
    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_multiply_rect_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 3, 0);
    matrix_t matrix_b = create_matrix_complex(3, 2, 1);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 3;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    multiply_matrix(matrix_a, matrix_b, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[6] = { -10 + 0 * I, -10 + 3 * I, -4 - 0 * I, -10 + 10 * I, -7 + 13 * I, -4 + 4 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }

    free(matrix_res.data);
    free(matrix_a.data);
    free(matrix_b.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_transponse_square_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 2, 0);
    matrix_t matrix_res;
    matrix_res.n = 2;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    transponse_matrix(matrix_a, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[4] = { 0 + 0 * I, 0 + 0 * I, 0 + 1 * I, 1 + 1 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);

            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }
    free(matrix_res.data);
    free(matrix_a.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_transponse_rect_matrix_complex)
{
    matrix_t matrix_a = create_matrix_complex(2, 3, 0);
    matrix_t matrix_res;
    matrix_res.n = 3;
    matrix_res.m = 2;
    matrix_res.size = sizeof(double complex);
    matrix_res.data = malloc(sizeof(double complex) * matrix_res.m * matrix_res.n);

    transponse_matrix(matrix_a, &matrix_res);
    int rc = 0;
    int c = 0;
    double complex res[6] = { 0 + 0 * I, 0 + 0 * I, 0 + 1 * I, 1 + 1 * I, 0 + 2 * I, 2 + 2 * I };
    for (int i = 0; i < matrix_res.n; i++)
        for (int j = 0; j < matrix_res.m; j++)
        {
            double complex val = *(double complex*) (matrix_res.data + (matrix_res.m * i + j) * matrix_res.size);
            if (creal(res[c]) != creal(val) || cimag(res[c]) != cimag(val))
                rc++;
            c++;
        }
    free(matrix_res.data);
    free(matrix_a.data);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite* matrix_suite(void)
{
    Suite* s;
    TCase* tc;

    s = suite_create("matrix");
    tc = tcase_create("all_matrix");
    tcase_add_test(tc, test_sum_square_matrix_double);
    tcase_add_test(tc, test_sum_rect_matrix_double);
    tcase_add_test(tc, test_multiply_square_matrix_double);
    tcase_add_test(tc, test_multiply_rect_matrix_double);
    tcase_add_test(tc, test_transponse_square_matrix_double);
    tcase_add_test(tc, test_transponse_rect_matrix_double);

    tcase_add_test(tc, test_sum_square_matrix_complex);
    tcase_add_test(tc, test_sum_rect_matrix_complex);
    tcase_add_test(tc, test_multiply_square_matrix_complex);
    tcase_add_test(tc, test_multiply_rect_matrix_complex);
    tcase_add_test(tc, test_transponse_square_matrix_complex);
    tcase_add_test(tc, test_transponse_rect_matrix_complex);

    suite_add_tcase(s, tc);

    return s;
}
