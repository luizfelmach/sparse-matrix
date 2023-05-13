#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m1 = matrix_gen(4, 4);
    Matrix m2 = matrix_gen(4, 4);

    matrix_show_dense(m1);
    printf("\n");
    matrix_show_dense(m2);
    printf("\n");

    Matrix mult_point = matrix_mult_point(m1, m2);

    matrix_show_dense(mult_point);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(mult_point);
    return 0;
}
