#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Numero incorreto de argumento (%d), digite (./prog (linhas) (colunas))\n",
               argc - 1);
        exit(1);
    }

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand48(tv.tv_usec);

    printf("%d %d\n", i, j);

    for (int c = 0; c < i; c++) {
        for (int l = 0; l < j; l++) {
            if (((unsigned int)(drand48() * 10)) < 3) {
                printf("%d ", (unsigned int)(drand48() * 10));
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    return 0;
}