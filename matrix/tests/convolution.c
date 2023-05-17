#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(3, 3);
    Matrix kernel = matrix_gen(3, 3);

    matrix_show_dense(m);
    printf("\n");
    matrix_show_dense(kernel);
    printf("\n");

    Matrix conv = matrix_convolution(m, kernel);

    matrix_show_dense(conv);

    matrix_destroy(m);
    matrix_destroy(kernel);
    matrix_destroy(conv);
    return 0;
}
