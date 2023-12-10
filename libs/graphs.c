
#include "graphs.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

int** New_matrix_dynamic(int row, int columns){
    int val;
    int **m = malloc(sizeof(int*) * row);
    for(Type i = 0; i < row; i++)
        m[i] = malloc(sizeof(int) * columns);
    // for(Type i = 0; i < row; i++)
    //     for(Type j = 0; j < columns; j++){
    //         scanf("%d", &val);
    //         m[i][j] = val;
    //     }
    return m;
}

Graph* New_Graph(int V){
    Graph *G = malloc(sizeof(Graph));
    G->V = V;
    G->A = 0;
    G->adj = New_matrix(V, V);
    return G;
}

Graph* New_Graph_dynamic(int V){
    Graph *G = malloc(sizeof(Graph));
    G->V = V;
    G->A = 0;
    G->adj = New_matrix_dynamic(V, V);
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
    printf("%d", G->adj[28][28]);
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