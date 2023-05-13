#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(10, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix slice = matrix_slice(m, 0, 0, 2, 2);

    matrix_show_dense(slice);

    matrix_destroy(m);
    matrix_destroy(slice);
    return 0;
}
