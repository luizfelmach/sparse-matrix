#ifndef SPARSE_H
#define SPARSE_H

#include <sparse_node.h>
#include <stdio.h>

typedef struct _sparse* Sparse;

Sparse sparse(int row, int column);
void   sparse_set(Sparse sm, double data, int row, int column);
double sparse_get(Sparse sm, int row, int column);

Sparse sparse_sum(Sparse sm1, Sparse sm2);
Sparse sparse_mult_k(Sparse sm, double k);
Sparse sparse_mult(Sparse sm1, Sparse sm2);
Sparse sparse_mult_point(Sparse sm1, Sparse sm2);

Sparse sparse_swap_row(Sparse sm, int r1, int r2);
Sparse sparse_swap_column(Sparse sm, int c1, int c2);
Sparse sparse_slice(Sparse sm, int r1, int c1, int r2, int c2);
Sparse sparse_transposed(Sparse sm);

void   sparse_show(Sparse sm);
void   sparse_show_dense(Sparse sm);
void   sparse_save(Sparse sm, FILE* file);
Sparse sparse_load(FILE* file);
void   sparse_destroy(Sparse sm);

#endif
