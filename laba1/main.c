#include <stdio.h>
#include "matrix.h"

#define CMD "Введите команду:\n"
#define INCORRECT_CMD "неверная команда\n"
#define MENU "1. сложение двух матриц\n"   \
             "2. умножение двух матриц\n"  \
             "3. транспонирование матрицы\n"                          \
             "при работе с комплексными числами числа вводятся парой,\n"\
             "то есть ввод 3 5 = 3+5i (1 число - действительная часть, 2 число - мнимая часть)\n"           \
             "4. выход\n"

matrix_t* create_matrix(int n, int m, int size)
{
    matrix_t* matrix_a = allocate_matrix(n, m, size);
    if (fill_matrix(matrix_a))
        return NULL;
    return matrix_a;
}

int get_cmd() {
    char tmp[10];
    printf(CMD);
    int cmd;

    do {
        if (scanf("%s", tmp) == EOF) return EOF;
        printf(INCORRECT_CMD);
    } while (sscanf(tmp, "%d", &cmd) != 1 || cmd < 1 || cmd > 4);

    return cmd;
}

int main()
{
    setbuf(stdout, NULL);
    printf(MENU);
    int cmd;

    matrix_t* matrix_a, * matrix_b, * matrix_res;
    int n, m, type, tmp_size;
    while ((cmd = get_cmd()) != EOF && cmd != 4)
    {
        switch (cmd)
        {
        case 1:
            type = input_type();
            if (type == 0) {
                cmd = 4;
                break;
            }
            tmp_size = type == 1 ? sizeof(double) : sizeof(double complex);
            if (input_size(&n, &m))
                return -1;
            printf("Работа с 1 матрицей\n");

            matrix_a = create_matrix(n, m, tmp_size);
            if (matrix_a == NULL)
                return -2;
            printf("Работа с 2 матрицей\n");
            matrix_b = create_matrix(n, m, tmp_size);
            if (matrix_b == NULL)
                return -2;
            matrix_res = allocate_matrix(n, m, tmp_size);
            sum_matrix(*matrix_a, *matrix_b, matrix_res);
            free_matrix(matrix_a);
            free_matrix(matrix_b);
            free_matrix(matrix_res);
            break;
        case 2:
            type = input_type();
            if (type == 0) {
                cmd = 4;
                break;
            }
            tmp_size = type == 1 ? sizeof(double) : sizeof(double complex);
            printf("Работа с 1 матрицей\n");
            if (input_size(&n, &m))
                return -1;

            matrix_a = create_matrix(n, m, tmp_size);
            if (matrix_a == NULL)
                return -2;
            printf("Работа с 2 матрицей\n");
            if (input_size(&n, &m)) {
                free_matrix(matrix_a);
                return -1;
            }
            matrix_b = create_matrix(n, m, tmp_size);
            if (matrix_b == NULL) {
                free_matrix(matrix_a);
                return -2;
            }
            if (matrix_a->m != matrix_b->n) {
                free_matrix(matrix_a);
                free_matrix(matrix_b);
                return -3;
            }
            matrix_res = allocate_matrix(matrix_a->n, matrix_b->m, tmp_size);
            multiply_matrix(*matrix_a, *matrix_b, matrix_res);
            free_matrix(matrix_a);
            free_matrix(matrix_b);
            free_matrix(matrix_res);
            break;
        case 3:
            type = input_type();
            if (type == 0) {
                cmd = 4;
                break;
            }
            tmp_size = type == 1 ? sizeof(double) : sizeof(double complex);
            if (input_size(&n, &m))
                return -1;
            printf("Работа с 1 матрицей\n");

            matrix_a = create_matrix(n, m, tmp_size);
            if (matrix_a == NULL)
                return -2;

            matrix_res = allocate_matrix(matrix_a->m, matrix_a->n, tmp_size);
            transponse_matrix(*matrix_a, matrix_res);
            free_matrix(matrix_a);
            free_matrix(matrix_res);
            break;
        default:
            break;
        }

    }
    return 0;
}
