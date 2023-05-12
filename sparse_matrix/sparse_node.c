#include <sparse_node.h>
#include <stdlib.h>

SparseNode sparse_node_new(double value, SparseNode next, SparseNode down, int row,
                           int column) {
    SparseNode sn = calloc(1, sizeof(struct _sparseNode));

    sn->row    = row;
    sn->column = column;
    sn->value  = value;
    sn->next   = next;
    sn->down   = down;

    return sn;
}

void sparse_node_destroy(SparseNode sn) {
    free(sn);
}

void sparse_node_save(SparseNode sn, FILE *file) {
    fwrite(&sn->row, sizeof(int), 1, file);
    fwrite(&sn->column, sizeof(int), 1, file);
    fwrite(&sn->value, sizeof(double), 1, file);
}

SparseNode sparse_node_load(FILE *file) {
    int    row, column;
    double value;
    fread(&row, sizeof(int), 1, file);
    fread(&column, sizeof(int), 1, file);
    fread(&value, sizeof(double), 1, file);
    SparseNode sn = sparse_node_new(value, NULL, NULL, row, column);
    return sn;
}