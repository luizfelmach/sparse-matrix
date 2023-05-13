#include <sparse_matrix.h>
#include <stdio.h>

int main() {
    Matrix m = matrix_gen(500, 350);

    matrix_destroy(m);
    return 0;
}
