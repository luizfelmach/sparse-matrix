#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(10, 10);

    matrix_show_dense(m);
    printf("\n");

    double det = matrix_det(m);

    printf("det: %.1lf\n", det);

    matrix_destroy(m);
    return 0;
}
