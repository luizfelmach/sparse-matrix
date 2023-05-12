#include <node.h>
#include <stdlib.h>

Node node_new(double value, Node next, Node down, int row, int column) {
    Node n = calloc(1, sizeof(struct _node));

    n->row    = row;
    n->column = column;
    n->value  = value;
    n->next   = next;
    n->down   = down;

    return n;
}

void node_destroy(Node n) {
    free(n);
}

void node_save(Node n, FILE *file) {
    fwrite(&n->row, sizeof(int), 1, file);
    fwrite(&n->column, sizeof(int), 1, file);
    fwrite(&n->value, sizeof(double), 1, file);
}

Node node_load(FILE *file) {
    int    row, column;
    double value;
    fread(&row, sizeof(int), 1, file);
    fread(&column, sizeof(int), 1, file);
    fread(&value, sizeof(double), 1, file);
    Node n = node_new(value, NULL, NULL, row, column);
    return n;
}