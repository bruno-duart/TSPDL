/*
 *	make all && ./run.sh burma14_10_1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include "lib/meta_index_tabu.h"
#include "lib/local_search.h"

typedef struct time_diff_t {
	clock_t ti;
	clock_t tf;
} TimeDiff;

void tick(TimeDiff *tdiff){
	tdiff->ti = clock();
};

double tack(TimeDiff *tdiff){
	tdiff->tf = clock();
	return (double)(tdiff->tf - tdiff->ti) / CLOCKS_PER_SEC;
};

size_t CONT_GER;
int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;

int main()
{
    TimeDiff tdiff;
    srand(time(NULL));

    // Arrays and Matrices initialization
    scanf("%d", &DIM);
    ProblemInstance *pinst = pinstance_init(DIM);
    scanf("%d", &OPT_VAL);

    // Stopping criteria
    MAX_ITER = 100;

    //int best = 0;
    //tempo = clock();
    // metaheuristica
    // Graph_print(G);    
    // print_arr(DEMAND);
    // print_arr(DRAFT);

    Solution* s = new_solution(pinst);
    SolutionChangeTrack* sct = new_changetrack(s, 2);
    
    tick(&tdiff);
    constructor_random(sct->s);
	printf("\n>>> Random constructor (%.2fms)\n", 1000*tack(&tdiff));
    solution_print(sct->s);
    
    tick(&tdiff);
    constructor_random_guided(sct->s);
	printf("\n>>> Random guided constructor (%.2fms)\n", 1000*tack(&tdiff));
    solution_print(sct->s);
    
    tick(&tdiff);
    lsearch_random_swap(sct, 1000);
	printf("\n>>> Random swap (%.2fms | 1k)\n", 1000*tack(&tdiff));
    solution_print(sct->s);
    
    tick(&tdiff);
    lsearch_fixed_swap(sct);
	printf("\n>>> Fixed swap (%.2fms)\n", 1000*tack(&tdiff));
    solution_print(sct->s);
    
    tick(&tdiff);
    constructor_greedy(sct->s);
	printf("\n>>> Greedy constructor (%.2fms)\n", 1000*tack(&tdiff));
    solution_print(sct->s);
    
    
    /*Solution* ns = tabu_search(s, G, 30, 10, 3);
    print_solution(ns);

    //tempo = clock() - tempo;

    //printf("%d,%f", best, (double)tempo / CLOCKS_PER_SEC);*/
    free_solution(s);
    free_pinstance(pinst);
    //free_solution(ns);
    
    return 0;
}
