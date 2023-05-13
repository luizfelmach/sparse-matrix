#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m1 = matrix_gen(5, 3);
    Matrix m2 = matrix_gen(5, 3);

    matrix_show_dense(m1);
    printf("\n");
    matrix_show_dense(m2);
    printf("\n");

    Matrix sum = matrix_sum(m1, m2);

    matrix_show_dense(sum);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(sum);
    return 0;
}
