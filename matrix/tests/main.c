#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix sm1 = matrix(3, 3);
    Matrix sm2 = matrix(3, 3);

    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            int a;
            scanf("%d", &a);
            matrix_set(sm1, a, i, j);
        }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            int a;
            scanf("%d", &a);
            matrix_set(sm2, a, i, j);
        }

    matrix_show_dense(sm1);
    printf("\n\n");
    matrix_show_dense(sm2);
    printf("\n\n");
    matrix_show_dense(matrix_swap_column(sm1, 0, 1));

    return 0;
}
