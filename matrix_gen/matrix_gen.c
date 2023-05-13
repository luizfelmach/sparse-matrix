#include <matrix.h>
#include <matrix_gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

Matrix matrix_gen(int row, int column) {
    Matrix m = matrix(row, column);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand48(tv.tv_usec);

    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (((unsigned int)(drand48() * 10)) < 3) {
                matrix_set(m, (double)(drand48() * 10), i, j);
            }
        }
    }

    return m;
}
