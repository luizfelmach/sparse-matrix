#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(3, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix cof = matrix_cof(m);

    matrix_show_dense(cof);

    matrix_destroy(m);
    matrix_destroy(cof);
    return 0;
}
