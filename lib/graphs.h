#ifndef HEADERS_GRAPHS
#define HEADERS_GRAPHS

#include "presets.h"

#define Type int

typedef struct {
    int V;
    int A;
    int **adj;
}Graph;

int** New_matrix(int row, int columns);

Graph* New_Graph(int V);

void insert_arc(Graph *G, Type i, Type j, Type value);

void remove_arc(Graph *G, Type i, Type j);

void Graph_print(Graph *G);

void free_Graph(Graph *G);

#endif