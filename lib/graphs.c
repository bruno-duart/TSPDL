#include "graphs.h"

EdgeType** matrix_init(int row, int columns){
    EdgeType val;
    EdgeType **m = malloc(sizeof(EdgeType*) * row);
    for(int i = 0; i < row; i++)
    {
        m[i] = malloc(sizeof(EdgeType) * columns);
        for(int j = 0; j < columns; j++)
       	{
            scanf("%d", &val);
            m[i][j] = val;
        }
    }
    return m;
}

Graph* graph_init(int N){
    Graph *G = malloc(sizeof(Graph));
    G->N = N;
    G->M = 0;
    G->adj = matrix_init(N, N);
    return G;
}

void free_graph(Graph *G){
    for(int i=0; i < G->N; i++)
        free(G->adj[i]);
    free(G->adj);
    free(G);
}

void graph_insert_arc(Graph *G, int i, int j, EdgeType value){
    if (G->adj[i][j] == 0){
        G->adj[i][j] = value;
        G->M++;
    }
}

void graph_remove_arc(Graph *G, int i, int j){
    if(G->adj[i][j] != 0){
        G->adj[i][j] = 0;
        G->M--;
    }
}

void graph_print(Graph *G){
    for(int i=0; i < G->N; i++){
        for(int j=0; j < G->N; j++)
            printf("%4d ", G->adj[i][j]);
        printf("\n");
    }
}
