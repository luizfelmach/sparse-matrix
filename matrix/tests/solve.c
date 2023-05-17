#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix A = matrix_gen(3, 3);
    Matrix B = matrix_gen(3, 1);

    matrix_show_dense(A);
    printf("\n");
    matrix_show_dense(B);
    printf("\n"); 

    Matrix solve = matrix_solve(A, B);

    matrix_show_dense(solve);
    printf("\n"); 

    matrix_destroy(A);
    matrix_destroy(B);
    matrix_destroy(solve);
    return 0;
}
