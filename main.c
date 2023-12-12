#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include "lib/meta_index_tabu.h"
#include "lib/local_search.h"

Graph *G;
size_t CONT_GER;
int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;
int *DEMAND, *DRAFT;

int main()
{
    //clock_t tempo;
    srand(time(NULL));

    // Arrays and Matrices initialization
    scanf("%d", &DIM);
    G = new_graph(DIM);
    DEMAND = array_init(DIM);
    DRAFT = array_init(DIM);
    scanf("%d", &OPT_VAL);

    // Stopping criteria
    MAX_ITER = 100;

    //int best = 0;
    //tempo = clock();
    // metaheuristica
    // Graph_print(G);    
    // print_arr(DEMAND);
    // print_arr(DRAFT);

    Solution* s = new_solution();
    lsearch_greedy(s);
    solution_print(s);
    /*Solution* ns = tabu_search(s, G, 30, 10, 3);
    print_solution(ns);

    //tempo = clock() - tempo;

    //printf("%d,%f", best, (double)tempo / CLOCKS_PER_SEC);*/
    free_solution(s);
    //free_solution(ns);
    free_graph(G);
    free(DEMAND);
    free(DRAFT);

    return 0;
}
