#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "libs/meta_index_tabu.h"
#include <string.h>
#include <ctype.h>

Graph *G;
size_t CONT_GER;
int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;
int *DEMAND, *DRAFT;

int main()
{
    clock_t tempo;
    srand(time(NULL));

    // Arrays and Matrices initialization
    char* string = ReadFile("/mnt/c/Users/fabio/Desktop/meta/TSPDL/instances/bayg29_25_1.txt");
    char *token = strtok(string, "\n");
    sscanf(token, "%d", &DIM);
    // printf("%d\n", DIM);
    
    DEMAND = ini_array_dynamic(DIM);
    DRAFT = ini_array_dynamic(DIM);
    // int **matrix = New_matrix_dynamic(DIM, DIM);
    
    // int **matrix = malloc(sizeof(int*) * DIM);
    // for(int i = 0; i < DIM; i++)
    //     matrix[i] = malloc(sizeof(int) * DIM);
    G = New_Graph_dynamic(DIM);

    token = strtok(NULL, " ");
    
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            sscanf(token, "%d", &G->adj[i][j]);
            token = strtok(NULL, " ");
        }
    }

    for (int j = 0; j < DIM; ++j) {
        sscanf(token, "%d", &DEMAND[j]);
        token = strtok(NULL, " ");
    }
    
    for (int j = 0; j < DIM; ++j) {
        sscanf(token, "%d", &DRAFT[j]);
        token = strtok(NULL, " ");
    }

    sscanf(token, "%d", &OPT_VAL);

    // printf("%d\n", OPT_VAL);

    
    
    // for (int i = 0; i < DIM; ++i) {
    //     for (int j = 0; j < DIM; ++j) 
    //         printf("%i ", matrix[i][j]);
    //     printf("\n");
    // }

    // for (int j = 0; j < DIM; ++j) 
    //     printf("%i ", DEMAND[j]); 
    // for (int j = 0; j < DIM; ++j) 
    //     printf("%i ", DRAFT[j]);
    
    // scanf("%d", &DIM);
    // G = New_Graph(DIM);
    // DEMAND = ini_array(DIM);
    // DRAFT = ini_array(DIM);
    // scanf("%d", &OPT_VAL);

    // Stopping criteria
    MAX_ITER = 100;

    int best = 0;
    //tempo = clock();
    // metaheuristica
    // Graph_print(G);    
    // print_arr(DEMAND);
    // print_arr(DRAFT);
    
    
    Solution* s = greedy_method();
    // print_solution(s);
    Solution* ns = tabu_search(s, G, 30, 10, 3);
    // print_solution(ns);

    //tempo = clock() - tempo;

    //printf("%d,%f", best, (double)tempo / CLOCKS_PER_SEC);
    free_solution(s);
    free_solution(ns);
    free_Graph(G);
    free(DEMAND);
    free(DRAFT);
    free(string);

    return 0;
}