#include "solutions.h"

ProblemInstance* pinstance_init(int dim)
{
	ProblemInstance *pinst = malloc(sizeof(ProblemInstance));
    pinst->graph = graph_init(dim);
    pinst->demand = array_init(dim);
    pinst->draft = array_init(dim);
    return pinst;
}

void free_pinstance(ProblemInstance *pinst)
{
	free_graph(pinst->graph);
    free(pinst->demand);
    free(pinst->draft);
    free(pinst);
}

Solution *new_solution(ProblemInstance *pinst)
{
    Solution *sol = malloc(sizeof(Solution));
    sol->dim = pinst->graph->N;
    sol->route = calloc(sol->dim, sizeof(int));
    sol->pinst = pinst;
    sol->distance = 0;
    return sol;
}

void free_solution(Solution *s)
{
    free(s->route);
    free(s);
}

bool solution_is_valid(Solution *s)
{
    int weight = s->dim - 1;
    int *draft = s->pinst->draft;
    int *demand = array_duplicate(s->pinst->demand, s->dim);

    for (int i = 0; i < s->dim - 1; i++)
    {
    	int port = s->route[i];
        // verifica o indice dos portos
        if (port < 0)
            return false;
        // verifica se o porto de origem está sendo visitado antes da hora
        if (port == 0)
            return false;
        // verifica a condição do calado
        if (draft[port] < weight)
            return false;
        // verifica se a demanda já foi atendida
        if (!demand[port])
            return false;
        // senão, atende à demanda e diminui o peso
        demand[port] = 0;
        weight--;
    }
    // verifica se o navio retorna ao porto de origem
    return (s->route[s->dim - 1] == 0);
}

bool solution_compare(Solution* sA, Solution* sB)
{
    return array_compare(sA->route, sB->route, sA->dim);
}

bool solution_is_in(Solution* s, int port)
{
    for (int i = 0; i < s->dim; i++)
        if (s->route[i] == port)
            return true;
    return false;
}

int solution_atleast(Solution **sArr, int cost)
{
	int population_size = 2 * sArr[0]->dim;
    for (int i = 0; i < population_size; i++)
        if (sArr[i]->distance <= cost)
            return i;
    return -1;
}

void solution_copy(Solution *sSource, Solution *sTarget)
{
    /*
        Função utilizada para efetuar a cópia do conteúdo
        dos ponteiros de Solution
    */
    for (int i = 0; i < sSource->dim; i++)
        sTarget->route[i] = sSource->route[i];
    sTarget->distance = sSource->distance;
    sTarget->pinst = sSource->pinst;
    sTarget->dim = sSource->dim;
}

Solution* solution_duplicate(Solution *sSource)
{
	Solution *sTarget = new_solution(sSource->pinst);
	solution_copy(sSource, sTarget);
	return sTarget;
}

void solution_print(Solution *s)
{
    array_print(s->route, s->dim);
    printf("%d\n", s->distance);
}

SolutionChangeTrack* new_changetrack(Solution *s, int n_changes)
{
	SolutionChangeTrack* sct = malloc(sizeof(SolutionChangeTrack));
	sct->change = malloc(sizeof(int) * n_changes);
	for(int i=0; i < n_changes; i++)
		sct->change[i] = -1;
	sct->n = n_changes;
	sct->s = s;
	return sct;
}

void free_changetrack(SolutionChangeTrack *sct, bool keep_solution)
{
	if(!keep_solution)
		free_solution(sct->s);
	free(sct->change);
	free(sct);
}

void changetrack_copy(SolutionChangeTrack *sctSource, SolutionChangeTrack *sctTarget)
{
	solution_copy(sctSource->s, sctTarget->s);
	array_copy(sctSource->change, sctTarget->change, sctSource->n);
}

SolutionChangeTrack* changetrack_duplicate(SolutionChangeTrack *sctSource)
{
	SolutionChangeTrack* sctTarget = new_changetrack(sctSource->s, sctSource->n);
	sctTarget->s = solution_duplicate(sctSource->s);
	array_copy(sctSource->change, sctTarget->change, sctSource->n);
	return sctTarget;
}

bool changetrack_update(SolutionChangeTrack *sctCurr, SolutionChangeTrack *sctNew)
{
        if (sctNew->s->distance < sctCurr->s->distance)
        {
            changetrack_copy(sctNew, sctCurr);
            return true;
        }
        return false;
}
