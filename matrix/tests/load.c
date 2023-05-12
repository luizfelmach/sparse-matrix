#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    FILE *f = fopen("matrix.bin", "rb");

    Matrix sm = matrix_load(f);

    matrix_show_dense(sm);
    matrix_destroy(sm);
    fclose(f);

    return 0;
}
