#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

struct _matrix {
    int    r, c, total_nodes;
    void **rows;
    void **columns;
};

Matrix matrix(int row, int column) {
    Matrix m = calloc(1, sizeof(struct _matrix));

    m->rows        = calloc(row, sizeof(void *));
    m->columns     = calloc(column, sizeof(void *));
    m->r           = row;
    m->c           = column;
    m->total_nodes = 0;

    return m;
}

Node sparse_find_index(Matrix m, int row, int column) {
    if (!m->rows[row]) {
        return NULL;
    }

    if (!m->columns[column]) {
        return NULL;
    }

    Node n = m->rows[row];

    while (n) {
        if (n->row == row && n->column == column) {
            return n;
        }
        n = n->next;
    }

    return NULL;
}

void sparse_push_row(Matrix m, Node n, int row) {
    Node node = m->rows[row];
    Node prev = NULL;

    if (!node) {
        m->rows[row] = n;
        n->next      = NULL;
        return;
    }

    while (node) {
        if (node->row > row) {
            if (!prev) {
                n->next = node;
                break;
            } else {
                prev->next = n;
                n->next    = node;
                break;
            }
        }

        if (!node->next) {
            node->next = n;
            break;
        }

        prev = node;
        node = node->next;
    }
}

void sparse_push_column(Matrix m, Node n, int column) {
    Node node = m->columns[column];
    Node prev = NULL;

    if (!node) {
        m->columns[column] = n;
        n->down            = NULL;
        return;
    }

    while (node) {
        if (node->column > column) {
            if (!prev) {
                n->down = node;
                break;
            } else {
                prev->down = n;
                n->down    = node;
                break;
            }
        }

        if (!node->down) {
            node->down = n;
            break;
        }

        prev = node;
        node = node->down;
    }
}

void *sparse_create_node(Matrix m, double data, int row, int column) {
    Node new = node_new(data, NULL, NULL, row, column);
    sparse_push_row(m, new, row);
    sparse_push_column(m, new, column);
    m->total_nodes += 1;
    return new;
}

void matrix_set(Matrix m, double data, int row, int column) {
    if (data == 0) {
        return;
    }

    Node exists = sparse_find_index(m, row, column);

    if (!exists) {
        exists = sparse_create_node(m, data, row, column);
    }

    exists->value = data;
}

double matrix_get(Matrix m, int row, int column) {
    Node exists = sparse_find_index(m, row, column);
    if (!exists) {
        return 0.0;
    }
    return exists->value;
}

Matrix matrix_sum(Matrix m1, Matrix m2) {
    if (m1->r != m2->r || m1->c != m2->c) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Matrix new = matrix(m1->r, m1->c);

    int i;
    for (i = 0; i < m1->r; i++) {
        Node node1 = m1->rows[i];
        Node node2 = m2->rows[i];
        while (node1 || node2) {
            if (node1 && node2) {
                if (node1->column > node2->column) {
                    matrix_set(new, node2->value, node2->row, node2->column);
                    node2 = node2->next;
                } else if (node2->column > node1->column) {
                    matrix_set(new, node1->value, node1->row, node1->column);
                    node1 = node1->next;
                } else {
                    matrix_set(new, node1->value + node2->value, node1->row,
                               node2->column);
                    node1 = node1->next;
                    node2 = node2->next;
                }
            } else if (node1 != NULL) {
                matrix_set(new, node1->value, node1->row, node1->column);
                node1 = node1->next;
            } else if (node2 != NULL) {
                matrix_set(new, node2->value, node2->row, node2->column);
                node2 = node2->next;
            }
        }
    }

    return new;
}

Matrix matrix_mult_k(Matrix m, double k) {
    Matrix new = matrix(m->r, m->c);

    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            matrix_set(new, k * node->value, node->row, node->column);
            node = node->next;
        }
    }

    return new;
}

Matrix matrix_mult(Matrix m1, Matrix m2) {
    if (m1->c != m2->r) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Matrix new = matrix(m1->r, m2->c);

    int i, j;
    for (i = 0; i < m1->r; i++) {
        Node node1 = m1->rows[i];
        for (j = 0; j < m2->c; j++) {
            Node   node2 = m2->columns[j];
            double res   = 0;

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

            matrix_set(new, res, i, j);
            node1 = m1->rows[i];
        }
    }

    return new;
}

Matrix matrix_mult_point(Matrix m1, Matrix m2) {
    if (m1->r != m2->r || m1->c != m2->c) {
        printf("error: matrix incompatible.\n");
        exit(1);
    }

    Matrix new = matrix(m1->r, m1->c);

    int i;
    for (i = 0; i < m1->r; i++) {
        Node node = m1->rows[i];
        while (node) {
            double res = node->value * matrix_get(m2, i, node->column);
            matrix_set(new, res, i, node->column);
            node = node->next;
        }
    }

    return new;
}

Matrix matrix_swap_row(Matrix m, int r1, int r2) {
    if (r1 < 0 || r2 < 0 || r1 >= m->r || r2 >= m->r) {
        printf("error: incorrect index.\n");
        exit(1);
    }

    Matrix new = matrix(m->r, m->c);

    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            if (i == r1) {
                matrix_set(new, node->value, r2, node->column);
            } else if (i == r2) {
                matrix_set(new, node->value, r1, node->column);
            } else {
                matrix_set(new, node->value, i, node->column);
            }
            node = node->next;
        }
    }

    return new;
}

Matrix matrix_swap_column(Matrix m, int c1, int c2) {
    if (c1 < 0 || c2 < 0 || c1 >= m->r || c2 >= m->r) {
        printf("error: incorrect index.\n");
        exit(1);
    }
    Matrix new = matrix(m->r, m->c);

    int i;
    for (i = 0; i < m->c; i++) {
        Node node = m->columns[i];
        while (node) {
            if (i == c1) {
                matrix_set(new, node->value, node->row, c2);
            } else if (i == c2) {
                matrix_set(new, node->value, node->row, c1);
            } else {
                matrix_set(new, node->value, node->row, i);
            }
            node = node->down;
        }
    }

    return new;
}

Matrix matrix_slice(Matrix m, int r1, int c1, int r2, int c2) {
    if (r1 < 0 || r2 < 0 || r1 >= m->r || r2 >= m->r) {
        printf("error: incorrect index.\n");
        exit(1);
    }
    if (c1 < 0 || c2 < 0 || c1 >= m->r || c2 >= m->r) {
        printf("error: incorrect index.\n");
        exit(1);
    }
    if (r1 > r2 || c1 > c2) {
        printf("error: incorrect index.\n");
        exit(1);
    }
    Matrix new = matrix(r2 - r1 + 1, c2 - c1 + 1);

    int i;
    for (i = r1; i <= r2; i++) {
        Node node = m->rows[i];
        while (node) {
            if (node->column >= c1 && node->column <= c2) {
                matrix_set(new, node->value, node->row - r1, node->column - c1);
            }
            node = node->next;
        }
    }

    return new;
}

Matrix matrix_transposed(Matrix m) {
    Matrix new = matrix(m->c, m->r);

    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            matrix_set(new, node->value, node->column, node->row);
            node = node->next;
        }
    }

    return new;
}

void matrix_show(Matrix m) {
    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            printf("%.1f\t", node->value);
            node = node->next;
        }
        printf("\n");
    }
}

void matrix_show_dense(Matrix m) {
    int i, j;
    for (i = 0; i < m->r; i++) {
        for (j = 0; j < m->c; j++) {
            printf("%3.0lf ", matrix_get(m, i, j));
        }
        printf("\n");
    }
}

void matrix_save(Matrix m, FILE *file) {
    fwrite(&m->r, sizeof(int), 1, file);
    fwrite(&m->c, sizeof(int), 1, file);
    fwrite(&m->total_nodes, sizeof(int), 1, file);

    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            node_save(node, file);
            node = node->next;
        }
    }
}

Matrix matrix_load(FILE *file) {
    int row, column, total_nodes;
    fread(&row, sizeof(int), 1, file);
    fread(&column, sizeof(int), 1, file);
    fread(&total_nodes, sizeof(int), 1, file);

    Matrix m = matrix(row, column);

    int i;
    for (i = 0; i < total_nodes; i++) {
        Node node = node_load(file);
        sparse_push_row(m, node, node->row);
        sparse_push_column(m, node, node->column);
        m->total_nodes += 1;
    }

    return m;
}

void matrix_destroy(Matrix m) {
    int i;
    for (i = 0; i < m->r; i++) {
        Node node = m->rows[i];
        while (node) {
            Node aux = node->next;
            node_destroy(node);
            node = aux;
        }
    }
    free(m->columns);
    free(m->rows);
    free(m);
}