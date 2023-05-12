#include <rocketc.h>
#include <stdio.h>

int main() {
    FILE *f = fopen("matrix.bin", "rb");

    Sparse sm = sparse_load(f);

    sparse_show_dense(sm);
    sparse_destroy(sm);
    fclose(f);

    return 0;
}
