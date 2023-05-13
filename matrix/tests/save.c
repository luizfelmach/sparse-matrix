#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix sm = matrix_gen(10, 10);

    FILE *f = fopen("matrix.bin", "wb");

    matrix_save(sm, f);
    matrix_show_dense(sm);

    matrix_destroy(sm);
    fclose(f);
    return 0;
}
