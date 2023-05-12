#include <rocketc.h>
#include <stdio.h>

int main() {
    Sparse sm1 = sparse(3, 3);
    Sparse sm2 = sparse(3, 3);

    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            int a;
            scanf("%d", &a);
            sparse_set(sm1, a, i, j);
        }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            int a;
            scanf("%d", &a);
            sparse_set(sm2, a, i, j);
        }

    sparse_show_dense(sm1);
    printf("\n\n");
    sparse_show_dense(sm2);
    printf("\n\n");
    sparse_show_dense(sparse_swap_column(sm1, 0, 1));

    return 0;
}
