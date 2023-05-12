#include <rocketc.h>
#include <stdio.h>

int main() {
    Sparse sm = sparse(3, 5);

    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++) {
            int a;
            scanf("%d", &a);
            sparse_set(sm, a, i, j);
        }

    FILE *f = fopen("matrix.bin", "wb");

    sparse_save(sm, f);
    sparse_show_dense(sm);
    sparse_destroy(sm);
    fclose(f);
    return 0;
}
