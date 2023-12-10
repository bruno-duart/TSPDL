#include <stdio.h>
#include <stdlib.h>

#define Type int

typedef struct {
    int V;
    int A;
    int **adj;
}Graph;

int** New_matrix(int row, int columns);

Graph* New_Graph(int V);

Graph* New_Graph_dynamic(int V);

char* ReadFile(char *filename);

int** New_matrix_dynamic(int row, int columns);

int *ini_array_dynamic(int size);

void insert_arc(Graph *G, Type i, Type j, Type value);

void remove_arc(Graph *G, Type i, Type j);

void Graph_print(Graph *G);

void free_Graph(Graph *G);