#ifndef SPARSE_NODE_H
#define SPARSE_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _sparseNode {
    int                 row, column;
    double              value;
    struct _sparseNode *next;
    struct _sparseNode *down;
} *SparseNode;

SparseNode sparse_node_new(double value, SparseNode next, SparseNode down, int row,
                           int column);
void       sparse_node_destroy(SparseNode sn);
void       sparse_node_save(SparseNode sn, FILE *file);
SparseNode sparse_node_load(FILE *file);

#endif