#include <sparse_matrix.h>
#include <stdio.h>
#include <stdlib.h>

struct _sparse {
    int    r, c, total_nodes;
    void **rows;
    void **columns;
};

Sparse sparse(int row, int column) {
    Sparse sm = calloc(1, sizeof(struct _sparse));

    sm->rows        = calloc(row, sizeof(void *));
    sm->columns     = calloc(column, sizeof(void *));
    sm->r           = row;
    sm->c           = column;
    sm->total_nodes = 0;

    return sm;
}

SparseNode sparse_find_index(Sparse sm, int row, int column) {
    if (!sm->rows[row]) {
        return NULL;
    }

    if (!sm->columns[column]) {
        return NULL;
    }

    SparseNode sn = sm->rows[row];

    while (sn) {
        if (sn->row == row && sn->column == column) {
            return sn;
        }
        sn = sn->next;
    }

    return NULL;
}

void sparse_push_row(Sparse sm, SparseNode sn, int row) {
    SparseNode node = sm->rows[row];
    SparseNode prev = NULL;

    if (!node) {
        sm->rows[row] = sn;
        sn->next      = NULL;
        return;
    }

    while (node) {
        if (node->row > row) {
            if (!prev) {
                sn->next = node;
                break;
            } else {
                prev->next = sn;
                sn->next   = node;
                break;
            }
        }

        if (!node->next) {
            node->next = sn;
            break;
        }

        prev = node;
        node = node->next;
    }
}

void sparse_push_column(Sparse sm, SparseNode sn, int column) {
    SparseNode node = sm->columns[column];
    SparseNode prev = NULL;

    if (!node) {
        sm->columns[column] = sn;
        sn->down            = NULL;
        return;
    }

    while (node) {
        if (node->column > column) {
            if (!prev) {
                sn->down = node;
                break;
            } else {
                prev->down = sn;
                sn->down   = node;
                break;
            }
        }

        if (!node->down) {
            node->down = sn;
            break;
        }

        prev = node;
        node = node->down;
    }
}

void *sparse_create_node(Sparse sm, double data, int row, int column) {
    SparseNode new_node = sparse_node_new(data, NULL, NULL, row, column);
    sparse_push_row(sm, new_node, row);
    sparse_push_column(sm, new_node, column);
    sm->total_nodes += 1;
    return new_node;
}

void sparse_set(Sparse sm, double data, int row, int column) {
    if (data == 0) {
        return;
    }

    SparseNode exists = sparse_find_index(sm, row, column);

    if (!exists) {
        exists = sparse_create_node(sm, data, row, column);
    }

    exists->value = data;
}

double sparse_get(Sparse sm, int row, int column) {
    SparseNode exists = sparse_find_index(sm, row, column);
    if (!exists) {
        return 0.0;
    }
    return exists->value;
}

Sparse sparse_sum(Sparse sm1, Sparse sm2) {
    if (sm1->r != sm2->r || sm1->c != sm2->c) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Sparse new = sparse(sm1->r, sm1->c);

    int i;
    for (i = 0; i < sm1->r; i++) {
        SparseNode node1 = sm1->rows[i];
        SparseNode node2 = sm2->rows[i];
        while (node1 && node2) {
            if (node1->column > node2->column) {
                node2 = node2->next;
            } else if (node2->column > node1->column) {
                node1 = node1->next;
            } else {
                sparse_set(new, node1->value + node2->value, node1->row, node2->column);
                node1 = node1->next;
                node2 = node2->next;
            }
        }
    }

    return new;
}

Sparse sparse_mult_k(Sparse sm, double k) {
    Sparse new = sparse(sm->r, sm->r);

    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            sparse_set(new, k * node->value, node->row, node->column);
            node = node->next;
        }
    }

    return new;
}

Sparse sparse_mult(Sparse sm1, Sparse sm2) {
    if (sm1->c != sm2->r) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Sparse new = sparse(sm1->r, sm2->c);

    int i, j;
    for (i = 0; i < sm1->r; i++) {
        SparseNode node1 = sm1->rows[i];
        for (j = 0; j < sm2->c; j++) {
            SparseNode node2 = sm2->columns[j];
            double     res   = 0;

            while (node1 && node2) {
                if (node1->column == node2->row) {
                    res += node1->value * node2->value;
                    node1 = node1->next;
                    node2 = node2->down;
                } else if (node1->column > node2->row) {
                    node2 = node2->down;
                } else {
                    node1 = node1->next;
                }
            }

            sparse_set(new, res, i, j);
            node1 = sm1->rows[i];
        }
    }

    return new;
}

Sparse sparse_mult_point(Sparse sm1, Sparse sm2) {
    if (sm1->r != sm2->r || sm1->c != sm2->c) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Sparse new = sparse(sm1->r, sm1->c);

    int i;
    for (i = 0; i < sm1->r; i++) {
        SparseNode node = sm1->rows[i];
        while (node) {
            double res = node->value * sparse_get(sm2, i, node->column);
            sparse_set(new, res, i, node->column);
            node = node->next;
        }
    }

    return new;
}

Sparse sparse_swap_row(Sparse sm, int r1, int r2) {
    Sparse new = sparse(sm->r, sm->c);

    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            if (i == r1) {
                sparse_set(new, node->value, r2, node->column);
            } else if (i == r2) {
                sparse_set(new, node->value, r1, node->column);
            } else {
                sparse_set(new, node->value, i, node->column);
            }
            node = node->next;
        }
    }

    return new;
}

Sparse sparse_swap_column(Sparse sm, int c1, int c2) {
    Sparse new = sparse(sm->r, sm->c);

    int i;
    for (i = 0; i < sm->c; i++) {
        SparseNode node = sm->columns[i];
        while (node) {
            if (i == c1) {
                sparse_set(new, node->value, node->row, c2);
            } else if (i == c2) {
                sparse_set(new, node->value, node->row, c1);
            } else {
                sparse_set(new, node->value, node->row, i);
            }
            node = node->down;
        }
    }

    return new;
}

Sparse sparse_slice(Sparse sm, int r1, int c1, int r2, int c2) {
    Sparse new = sparse(r2 - r1 + 1, c2 - c1 + 1);

    int i;
    for (i = r1; i <= r2; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            if (node->column >= c1 && node->column <= c2) {
                sparse_set(new, node->value, node->row - r1, node->column - c1);
            }
            node = node->next;
        }
    }

    return new;
}

Sparse sparse_transposed(Sparse sm) {
    Sparse new = sparse(sm->c, sm->r);

    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            sparse_set(new, node->value, node->column, node->row);
            node = node->next;
        }
    }

    return new;
}

void sparse_show(Sparse sm) {
    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            printf("%.1f\t", node->value);
            node = node->next;
        }
        printf("\n");
    }
}

void sparse_show_dense(Sparse sm) {
    int i, j;
    for (i = 0; i < sm->r; i++) {
        for (j = 0; j < sm->c; j++) {
            printf("%.0lf ", sparse_get(sm, i, j));
        }
        printf("\n");
    }
}

void sparse_save(Sparse sm, FILE *file) {
    fwrite(&sm->r, sizeof(int), 1, file);
    fwrite(&sm->c, sizeof(int), 1, file);
    fwrite(&sm->total_nodes, sizeof(int), 1, file);

    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            sparse_node_save(node, file);
            node = node->next;
        }
    }
}

Sparse sparse_load(FILE *file) {
    int row, column, total_nodes;
    fread(&row, sizeof(int), 1, file);
    fread(&column, sizeof(int), 1, file);
    fread(&total_nodes, sizeof(int), 1, file);

    Sparse sm = sparse(row, column);

    int i;
    for (i = 0; i < total_nodes; i++) {
        SparseNode node = sparse_node_load(file);
        sparse_push_row(sm, node, node->row);
        sparse_push_column(sm, node, node->column);
        sm->total_nodes += 1;
    }

    return sm;
}

void sparse_destroy(Sparse sm) {
    int i;
    for (i = 0; i < sm->r; i++) {
        SparseNode node = sm->rows[i];
        while (node) {
            SparseNode aux = node->next;
            sparse_node_destroy(node);
            node = aux;
        }
    }
    free(sm->columns);
    free(sm->rows);
    free(sm);
}