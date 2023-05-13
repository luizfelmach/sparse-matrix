#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(3, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix inv = matrix_inv(m);

    matrix_show_dense(inv);

    matrix_destroy(m);
    matrix_destroy(inv);
    return 0;
}
