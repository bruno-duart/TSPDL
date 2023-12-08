#include <stdio.h>
#include <stdlib.h>

#define Type int

typedef struct {
    int V;
    int A;
    int **adj;
}Graph;

int** new_matrix(int row, int columns);

Graph* new_graph(int V);

void free_graph(Graph *G);

void graph_insert_arc(Graph *G, Type i, Type j, Type value);

void graph_remove_arc(Graph *G, Type i, Type j);

void graph_print(Graph *G);
