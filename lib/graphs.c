#include "graphs.h"

int** New_matrix(int row, int columns){
    int val;
    int **m = malloc(sizeof(int*) * row);
    for(Type i = 0; i < row; i++)
        m[i] = malloc(sizeof(int) * columns);
    for(Type i = 0; i < row; i++)
        for(Type j = 0; j < columns; j++){
            scanf("%d", &val);
            m[i][j] = val;
        }
    return m;
}

Graph* New_Graph(int V){
    Graph *G = malloc(sizeof(Graph));
    G->V = V;
    G->A = 0;
    G->adj = New_matrix(V, V);
    return G;
}

void insert_arc(Graph *G, Type i, Type j, Type value){
    if (G->adj[i][j] == 0){
        G->adj[i][j] = value;
        G->A++;
    }
}

void remove_arc(Graph *G, Type i, Type j){
    if(G->adj[i][j] != 0){
        G->adj[i][j] = 0;
        G->A--;
    }
}

void Graph_print(Graph *G){
    for(int i=0; i < G->V; i++){
        for(int j=0; j < G->V; j++)
            printf("%4d ", G->adj[i][j]);
        printf("\n");
    }
}

void free_Graph(Graph *G){
    for(int i=0; i < G->V; i++)
        free(G->adj[i]);
    free(G->adj);
    free(G);
}