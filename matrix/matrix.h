#ifndef SPARSE_H
#define SPARSE_H

#include <node.h>
#include <stdio.h>

typedef struct _matrix* Matrix;

Matrix matrix(int row, int column);
void   matrix_set(Matrix m, double data, int row, int column);
double matrix_get(Matrix m, int row, int column);

Matrix matrix_sum(Matrix m1, Matrix m2);
Matrix matrix_mult_k(Matrix m, double k);
Matrix matrix_mult(Matrix m1, Matrix m2);
Matrix matrix_mult_point(Matrix m1, Matrix m2);

Matrix matrix_swap_row(Matrix m, int r1, int r2);
Matrix matrix_swap_column(Matrix m, int c1, int c2);
Matrix matrix_slice(Matrix m, int r1, int c1, int r2, int c2);
Matrix matrix_transposed(Matrix m);

Matrix matrix_cof(Matrix m);
Matrix matrix_adj(Matrix m);
double matrix_det(Matrix m);
Matrix matrix_inv(Matrix m);
Matrix matrix_solve(Matrix A, Matrix B);

void   matrix_show(Matrix m);
void   matrix_show_dense(Matrix m);
void   matrix_save(Matrix m, FILE* file);
Matrix matrix_load(FILE* file);
void   matrix_destroy(Matrix m);

#endif
