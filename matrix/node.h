#ifndef SPARSE_NODE_H
#define SPARSE_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int           row, column;
    double        value;
    struct _node *next;
    struct _node *down;
} *Node;

Node node_new(double value, Node next, Node down, int row, int column);
void node_destroy(Node n);
void node_save(Node n, FILE *file);
Node node_load(FILE *file);

#endif