#include <sparse_matrix.h>
#include <stdio.h>

Matrix matrix_read() {
    int row, column;
    scanf("%d %d%*c", &row, &column);

    Matrix m = matrix(row, column);

    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            int a;
            scanf("%d%*c", &a);
            matrix_set(m, a, i, j);
        }
    }

    return m;
}

int main() {
    Matrix m = matrix_read();

    matrix_destroy(m);
    return 0;
}
