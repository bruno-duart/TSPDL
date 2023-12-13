#ifndef HEADER_GRAPHS
#define HEADER_GRAPHS

#include "presets.h"

#ifndef EdgeType
#define EdgeType int
#endif

typedef struct {
    int N;
    int M;
    EdgeType **adj;
}Graph;


int** matrix_init(int row, int columns);

Graph* graph_init(int N);

void free_graph(Graph *G);

void graph_insert_arc(Graph *G, int i, int j, EdgeType value);

void graph_remove_arc(Graph *G, int i, int j);

void graph_print(Graph *G);

#endif
