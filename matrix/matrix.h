#ifndef SPARSE_H
#define SPARSE_H

#include <node.h>
#include <stdio.h>

typedef struct _matrix* Matrix;

/* O(N)
 * O calloc faz com que a complexidade da funcao seja linear
 */
Matrix matrix(int row, int column);

/* O(N)
 * A busca na linha para encontrar o no faz com que a funcao seja linear
 */
void matrix_set(Matrix m, double data, int row, int column);

/* O(N)
 * A busca na linha para encontrar o no faz com que a funcao seja linear
 */
double matrix_get(Matrix m, int row, int column);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e somar com a outra matriz
 */
Matrix matrix_sum(Matrix m1, Matrix m2);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e multiplicar pelo k
 */
Matrix matrix_mult_k(Matrix m, double k);

/* O(N^3)
 * A complexidade N^3 se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e depois percorrer mais uma vez a linha e coluna juntas para
 * multiplicar e somar
 */
Matrix matrix_mult(Matrix m1, Matrix m2);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e mutiplicar ponto a ponto pela outra matriz
 */
Matrix matrix_mult_point(Matrix m1, Matrix m2);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e adicionar na nova matriz
 */
Matrix matrix_swap_row(Matrix m, int r1, int r2);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e adicionar na nova matriz
 */
Matrix matrix_swap_column(Matrix m, int c1, int c2);

/* O((r2 - r1) * (c2 - c1))
 * A complexidade (r2 - r1) * (c2 - c1) se da pelo fato de precisar somente percorrer um
 * intervalo delimitado pela entrada.
 */
Matrix matrix_slice(Matrix m, int r1, int c1, int r2, int c2);

/* O(r * c)
 * A complexidade r * c se da pelo fato de percorrer todas as linhas e para cada linha
 * percorrer todas as colunas e adicionar na nova matriz
 */
Matrix matrix_transposed(Matrix m);

/* O(r * c * k * k)
 * A complexidade r * c * k * k, onde k é o tamanho do kernel, se da pelo fato de
 * percorrer as linhas e colunas da matriz e para fazer o slice do kernel e necessario
 * percorrer o tamanho do kernel. Para kernel pequeno, a funcao tem um comportamento
 * quadrático.
 */
Matrix matrix_convolution(Matrix m, Matrix kernel);

/* Extras
 * Muito dificil analisar a complexidade dessas funcoes. Mas parece ser fatorial.
 */
Matrix matrix_cof(Matrix m);
Matrix matrix_adj(Matrix m);
double matrix_det(Matrix m);
Matrix matrix_inv(Matrix m);
Matrix matrix_solve(Matrix A, Matrix B);

/* O(r * c)
 * As funcoes abaixos apresentam complexidade r * c
 */
void   matrix_show(Matrix m);
void   matrix_show_dense(Matrix m);
void   matrix_save(Matrix m, FILE* file);
Matrix matrix_load(FILE* file);
void   matrix_destroy(Matrix m);

#endif
