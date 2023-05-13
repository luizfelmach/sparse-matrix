#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(10, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix transposed = matrix_transposed(m);

    matrix_show_dense(transposed);

    matrix_destroy(m);
    matrix_destroy(transposed);
    return 0;
}
