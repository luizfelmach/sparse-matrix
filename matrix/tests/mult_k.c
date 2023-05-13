#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(10, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix mult_k = matrix_mult_k(m, 10);

    matrix_show_dense(mult_k);

    matrix_destroy(m);
    matrix_destroy(mult_k);
    return 0;
}
