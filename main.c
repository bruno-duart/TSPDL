#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "lib/meta_pointer.h"

Graph *G;
size_t CONT_GER;
int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;
int *DEMAND, *DRAFT;

int main()
{
    clock_t tempo;
    srand(time(NULL));

    // Arrays and Matrices initialization
    scanf("%d", &DIM);
    G = New_Graph(DIM);
    DEMAND = ini_array(DIM);
    DRAFT = ini_array(DIM);
    scanf("%d", &OPT_VAL);

    // Stopping criteria
    MAX_ITER = 200;

    Solution* s = greedy_method();

    tempo = clock();
    Solution* ns = tabu_search(s, G, 10);
    tempo = clock() - tempo;

    printf("%d,%d,%d,%f\n", ns->distance, s->distance, OPT_VAL, (double)tempo / CLOCKS_PER_SEC);
    free_solution(s);
    free_solution(ns);
    free_Graph(G);
    free(DEMAND);
    free(DRAFT);

    return 0;
}

//gcc main.c lib/graphs.c lib/list_pointer.c lib/solution_pointer.c lib/meta_pointer.c -o main
//valgrind --leak-check=full --track-origins=yes ./main < instances/burma14_10_1.txt
//./main < instances/burma14_10_1.txt