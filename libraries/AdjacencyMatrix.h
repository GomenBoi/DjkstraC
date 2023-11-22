#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SIZE 4
#define MAX_SIZE 20

typedef struct AdjacencyMatrix {
    int ** grid;
    int num_nodes;
} AdjacencyMatrix;

/*Constructor*/
AdjacencyMatrix * initialise_matrix(int);
/*Methods*/
void set_edge(AdjacencyMatrix *, int, int, int);
void free_matrix(AdjacencyMatrix *);
void print_matrix(AdjacencyMatrix *);

/*Helper functions*/
int check_lims(int, int, int);

/*Functions*/
AdjacencyMatrix * initialise_matrix(int size) {
    AdjacencyMatrix * matrix;
    int i, j;

    if (!check_lims(size, 0, MAX_SIZE)) {
        fprintf(stderr, "Size must be in the range [0, 20] inclusive for natural numbers.\n");
        exit(2);
    }

    matrix = (AdjacencyMatrix *) malloc(sizeof(AdjacencyMatrix));
    matrix->grid = (int**) malloc(size * sizeof(int*));
    matrix->num_nodes = size;

    for (i = 0; i < size; i++) {
        matrix->grid[i] = (int *) malloc(size * sizeof(int));
        for (j = 0; j < size; j++) {
            matrix->grid[i][j] = 0;
        }
    }

    return matrix;
}

int check_lims(int value, int low, int high) {
    if (value >= low && value <= high) {
        return 1;
    }
    return 0;
}

/*Procedures*/
void set_edge(AdjacencyMatrix * matrix, int node_one, int node_two, int weight) {

    if (!check_lims(node_one, 0, matrix->num_nodes) || !check_lims(node_two, 0, matrix->num_nodes)) {
        fprintf(stderr, "Node was not in the bounds of the adjacency matrix.\n");
        exit(2);
    }

    matrix->grid[node_one][node_two] = weight;
}

void print_matrix(AdjacencyMatrix * matrix) {
    int i, j;
    int row_count = 0;
    int col_count = 0;

    if (!matrix) {
        fprintf(stderr, "Matrix pointer does not exist.\n");
        exit(1);
    }

    printf("  ");
    for (i = 0; i < matrix->num_nodes - 1; i++) {
        printf("%d ", col_count);
        col_count++;
    }
    printf("%d", col_count);
    printf("\n");

    for (i = 0; i < matrix->num_nodes; i++) {
        printf("%d|", row_count++);
        for (j = 0; j < matrix->num_nodes - 1; j++) {
            printf("%d ", matrix->grid[i][j]);
        }
        printf("%d\n", matrix->grid[i][j]);
    }
}

void free_matrix(AdjacencyMatrix * matrix) {
    int i;

    if (!matrix) {
        fprintf(stderr, "Matrix pointer does not exist.\n");
        exit(1);
    }

    for (i = 0; i < matrix->num_nodes; i++) {
        free(matrix->grid[i]);
    }

    free(matrix->grid);
    free(matrix);
}
#endif