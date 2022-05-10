#include "check_matrix.h"
#include <stdio.h>

int main()
{
    Suite* s;
    SRunner* r;
    int errors;

    s = matrix_suite();
    r = srunner_create(s);
    srunner_run_all(r, CK_VERBOSE);
    errors = srunner_ntests_failed(r);
    errors ? printf("Matrix module FAILED\n") : printf("Matrix module PASSED\n");
    srunner_free(r);

    return 0;
}
