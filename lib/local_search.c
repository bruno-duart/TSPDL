#include "local_search.h"

void lsearch_random_init(Solution *s){
    s->route[G->V-1] = 0;
    do{
        for(int i=0; i<G->V-1; i++)
        {
            s->route[i] = rand() % (G->V);
            for(int j=0; j<i; j++)
                if(s->route[j] == s->route[i])
                {
                    i--;
                    break;
                }
        }
    }while(!solution_is_valid(s));
    s->distance = fitness(s->route);
}

void lsearch_greedy_init(Solution *s)
{
    int weight = G->V - 1, smaller, position, k = 0;
    int *demand = array_duplicate(DEMAND, G->V);

    for (int i = 0; i < G->V; i++)
    {
        smaller = __INT16_MAX__;
        for (int j = 0; j < G->V; j++)
            if (G->adj[k][j] < smaller && demand[j] == 1 && weight <= DRAFT[j])
            {
                position = j;
                smaller = G->adj[k][j];
            }
        if (smaller != __INT16_MAX__)
        {
            k = position;
            s->route[i] = k;
            weight--;
            s->distance += smaller;
            demand[k] = 0;
        }
    }
    s->distance += G->adj[k][0];
    free(demand);
}

void lsearch_pseudo_greedy(Solution *s)
{
    /*
        Constrói uma solução viável para o conjunto de soluções relativo à
        população inicial do algoritmo genético. A construção é realizada
    com o método guloso com características aleatórias, através do qual
        dois portos são sorteados aleatoriamente para comporem o início da solução,
        e em seguida, aplica-se o método guloso para obter uma solução viável.
    */
    int port1, port2, weight = G->V - 1, smaller, position, k;
    int *demand = array_duplicate(DEMAND, G->V);

    // Seleção dos dois portos iniciais. Port1 e port2 devem ser diferentes entre si
    // e devem ser viáveis.
    do
        port1 = randint(1, G->V);
    while (DRAFT[port1] < weight);
    weight--;

    do
        port2 = randint(1, G->V);
    while (DRAFT[port2] < weight || port2 == port1);
    weight--;

    // Inicialização da solução, atualização da distância percorrida
    s->route[0] = port1;
    s->route[1] = port2;
    s->distance = G->adj[0][port1] + G->adj[port1][port2];
    demand[port1] = demand[port2] = 0;
    k = port2;

    // Etapa gulosa da construção.
    for (int i = 2; i < G->V; i++)
    {
        smaller = __INT16_MAX__;
        for (int j = 0; j < G->V; j++)
            if (G->adj[k][j] < smaller && demand[j] == 1 && weight <= DRAFT[j])
            {
                position = j;
                smaller = G->adj[k][j];
            }
        if (smaller != __INT16_MAX__)
        {
            k = position;
            s->route[i] = k;
            weight--;
            s->distance += smaller;
            demand[k] = 0;
        }
    }
    s->distance += G->adj[k][0];
    free(demand);
}

bool lsearch_try_port_swap(Solution *s, int i, int j)
{
	array_swap(s->route, i, j);
	if(solution_is_valid(s))
	{
		s->distance = fitness(s->route);
		return true;
	}
	else
	{
		//array_swap(s->route, i, j);
		return false;
	}
}

bool lsearch_choose_better(SolutionChangeTrack *sctCurr, Solution *sCandidate, int *index)
{
        if (sCandidate->distance < sctCurr->s->distance)
        {
            solution_copy(sCandidate, sctCurr->s);
            array_copy(index, sctCurr->change, G->V);
            return true;
        }
        return false;
}

void lsearch_random_swap(SolutionChangeTrack *sctCurr, int max_swaps)
{
	Solution *sAux = solution_duplicate(sctCurr->s);
	bool valid_swap;
    int index[2];

    while(max_swaps--)
    {
        index[0] = randint(0, G->V - 1);
        index[1] = randintavoid(0, G->V - 1, index[0]);
        valid_swap = lsearch_try_port_swap(sAux, index[0], index[1]);
        if(valid_swap && lsearch_choose_better(sctCurr, sAux, index))
        {
        	printf("x\n");
        	break;
        }
    }
    free_solution(sAux);
}

void lsearch_fixed_swap(SolutionChangeTrack *sctCurr)
{
	Solution *sAux = solution_duplicate(sctCurr->s);
    int index[2];

    for (int i = 0; i < DIM-1; i++)
    {
		for (int j = i+1; j < DIM; j++)
		{
			if(lsearch_try_port_swap(sAux, i, j))
			{
				index[0] = i;
				index[1] = j;
				lsearch_choose_better(sctCurr, sAux, index);
			}
		}
	}
    free_solution(sAux);
}
