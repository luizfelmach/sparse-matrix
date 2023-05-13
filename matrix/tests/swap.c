#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(3, 3);

    matrix_show_dense(m);
    printf("\n");

    Matrix swap_row    = matrix_swap_row(m, 0, 2);
    Matrix swap_column = matrix_swap_column(m, 0, 2);

    matrix_show_dense(swap_row);
    printf("\n");
    matrix_show_dense(swap_column);

    matrix_destroy(m);
    matrix_destroy(swap_row);
    matrix_destroy(swap_column);
    return 0;
}
