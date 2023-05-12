#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix sm = matrix(3, 5);

    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++) {
            int a;
            scanf("%d", &a);
            matrix_set(sm, a, i, j);
        }

    FILE *f = fopen("matrix.bin", "wb");

    matrix_save(sm, f);
    matrix_show_dense(sm);
    matrix_destroy(sm);
    fclose(f);
    return 0;
}
