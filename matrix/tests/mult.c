#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m1 = matrix_gen(3, 10);
    Matrix m2 = matrix_gen(10, 2);

    matrix_show_dense(m1);
    printf("\n");
    matrix_show_dense(m2);
    printf("\n");

    Matrix mult = matrix_mult(m1, m2);

    matrix_show_dense(mult);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(mult);
    return 0;
}
