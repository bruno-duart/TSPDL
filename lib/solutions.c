#include "solutions.h"

Solution *new_solution()
{
    Solution *sol = malloc(sizeof(Solution));
    sol->route = calloc(DIM, sizeof(int));
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
    int weight = G->V - 1;
    int *demand = array_duplicate(DEMAND, DIM);

    for (int i = 0; i < G->V - 1; i++)
    {
    	int port = s->route[i];
        // verifica o indice dos portos
        if (port < 0)
            return false;
        // verifica se o porto de origem está sendo visitado antes da hora
        if (port == 0)
            return false;
        // verifica a condição do calado
        if (DRAFT[port] < weight)
            return false;
        // verifica se a demanda já foi atendida
        if (!demand[port])
            return false;
        // senão, atende à demanda e diminui o peso
        demand[port] = 0;
        weight--;
    }
    // verifica se o navio retorna ao porto de origem
    return (s->route[DIM - 1] == 0);
}

bool solution_compare(Solution* sA, Solution* sB)
{
    for (int i = 0; i < G->V; i++)
    {
        if (sA->route[i] != sB->route[i])
            return false;
    }
    return true;
}

bool solution_isin(Solution* s, int port)
{
    for (int i = 0; i < G->V; i++)
        if (s->route[i] == port)
            return true;
    return false;
}

int solution_atleast(Solution **sArr, int cost)
{
    for (int i = 0; i < 2 * G->V; i++)
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
    for (int i = 0; i < G->V; i++)
        sTarget->route[i] = sSource->route[i];
    sTarget->distance = sSource->distance;
}

Solution* solution_duplicate(Solution *sSource)
{
	Solution *sTarget = new_solution();
	solution_copy(sSource, sTarget);
	return sTarget;
}

void solution_print(Solution *s)
{
    array_print(s->route, DIM);
    printf("%d\n", s->distance);
}

SolutionChangeTrack* new_changetrack(Solution *s, int n)
{
	SolutionChangeTrack* sct = malloc(sizeof(SolutionChangeTrack));
	sct->change = malloc(sizeof(int) * n);
	for(int i=0; i < n; i++)
		sct->change[i] = -1;
	sct->s = s;
	sct->n = n;
	return sct;
}

void free_changetrack(SolutionChangeTrack *sct, bool keep_solution)
{
	if(!keep_solution)
		free_solution(sct->s);
	free(sct->change);
	free(sct);
}

SolutionChangeTrack* changetrack_duplicate(SolutionChangeTrack *sctSource)
{
	SolutionChangeTrack* sctTarget = new_changetrack(sctSource->s, sctSource->n);
	sctTarget->s = solution_duplicate(sctSource->s);
	for(int i=0; i < sctSource->n; i++)
		sctTarget->change[i] = sctSource->change[i];
	return sctTarget;
}
