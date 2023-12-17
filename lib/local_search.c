#include "local_search.h"

void constructor_random(Solution *s){
	int dim = s->dim;
    s->route[dim-1] = 0;
    do{
        for(int i=0; i< dim-1; i++)
        {
            s->route[i] = randint(1, dim-1);
            for(int j=0; j<i; j++)
                if(s->route[j] == s->route[i])
                {
                    i--;
                    break;
                }
        }
    }while(!solution_is_valid(s));
    update_fitness(s);
}

void constructor_random_guided(Solution *s)
{
	int port, weight = s->dim - 1;
    bool* visited = calloc(s->dim, sizeof(bool));
    int *demand = s->pinst->demand;
    int *draft = s->pinst->draft;
    
    s->route[s->dim - 1] = 0; 
 
    for(int i=0; i < s->dim - 1; i++){ 
        port = randint(1, s->dim - 1); 
        if (visited[port] || weight > draft[port] || weight < demand[port]) { 
            i--;
            continue;
        }
        s->route[i] = port;
        visited[port] = true;
        weight--;
    }
	update_fitness(s);
}

void constructor_greedy(Solution *s)
{
	int dim = s->dim;
    int weight = dim-1, smaller, position, k = 0;
    int *demand = array_duplicate(s->pinst->demand, dim);
    int *draft = s->pinst->draft;
    int **edge = s->pinst->graph->adj;
    
    s->distance = 0;

    for (int i = 0; i < dim; i++)
    {
        smaller = __INT16_MAX__;
        for (int j = 0; j < dim; j++)
            if (edge[k][j] < smaller && demand[j] == 1 && weight <= draft[j])
            {
                position = j;
                smaller = edge[k][j];
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
    s->distance += edge[k][0];
    free(demand);
}

void constructor_pseudo_greedy(Solution *s)
{
    /*
        Constrói uma solução viável para o conjunto de soluções relativo à
        população inicial do algoritmo genético. A construção é realizada
    com o método guloso com características aleatórias, através do qual
        dois portos são sorteados aleatoriamente para comporem o início da solução,
        e em seguida, aplica-se o método guloso para obter uma solução viável.
    */
	int dim = s->dim;
    int port1, port2, weight = dim - 1, smaller, position, k;
    int *demand = array_duplicate(s->pinst->demand, dim);
    int *draft = s->pinst->draft;
    int **edge = s->pinst->graph->adj;

    // Seleção dos dois portos iniciais. Port1 e port2 devem ser diferentes entre si
    // e devem ser viáveis.
    do
        port1 = randint(1, dim);
    while (draft[port1] < weight);
    weight--;

    do
        port2 = randint(1, dim);
    while (draft[port2] < weight || port2 == port1);
    weight--;

    // Inicialização da solução, atualização da distância percorrida
    s->route[0] = port1;
    s->route[1] = port2;
    s->distance = edge[0][port1] + edge[port1][port2];
    demand[port1] = demand[port2] = 0;
    k = port2;

    // Etapa gulosa da construção.
    for (int i = 2; i < dim; i++)
    {
        smaller = __INT16_MAX__;
        for (int j = 0; j < dim; j++)
            if (edge[k][j] < smaller && demand[j] == 1 && weight <= draft[j])
            {
                position = j;
                smaller = edge[k][j];
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
    s->distance += edge[k][0];
    free(demand);
}

bool lsearch_try_port_swap(Solution *s, int i, int j)
{
	array_swap(s->route, i, j);
	if(solution_is_valid(s))
	{
		update_fitness(s);
		return true;
	}
	else
	{
		array_swap(s->route, i, j);
		return false;
	}
}

void lsearch_random_swap(SolutionChangeTrack *sctCurr, int max_swaps)
{
	SolutionChangeTrack *sctAux = changetrack_duplicate(sctCurr);
    int valid_ports = sctCurr->s->dim - 1;

    while(max_swaps--)
    {
        sctAux->change[0] = randint(0, valid_ports);
        sctAux->change[1] = randintavoid(0, valid_ports, sctAux->change[0]);
        if(lsearch_try_port_swap(sctAux->s, sctAux->change[0], sctAux->change[1]))
			changetrack_update(sctCurr, sctAux);
    }
    free_changetrack(sctAux, false);
}

void lsearch_fixed_swap(SolutionChangeTrack *sctCurr)
{
	SolutionChangeTrack *sctAux = changetrack_duplicate(sctCurr);
    int dim = sctCurr->s->dim;

    for (int i = 0; i < dim - 1; i++)
    {
		for (int j = i+1; j < dim; j++)
		{
			if(lsearch_try_port_swap(sctAux->s, i, j))
			{
				sctAux->change[0] = i;
				sctAux->change[1] = j;
				changetrack_update(sctCurr, sctAux);
			}
		}
	}
    free_changetrack(sctAux, false);
}
