#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "libs/globals.h"
#include "libs/graphs.h"
#include "libs/solution.h"

int main() {
    clock_t tempo;
    srand(time(NULL));

    //Arrays and Matrices initialization
    scanf("%d", &DIM);
    G = New_Graph(DIM);
    DEMAND = ini_array(DIM);
    DRAFT = ini_array(DIM);
    scanf("%d", &OPT_VAL);

    //Stopping criteria
    MAX_ITER = 100;

    long int best;
    tempo = clock();
    //metaheuristica
    tempo = clock() - tempo1;

    printf("%d,%f",best, (double)tempo/CLOCKS_PER_SEC);
    free_Graph(G);
    free(DEMAND);
    free(DRAFT);

    return 0;
}