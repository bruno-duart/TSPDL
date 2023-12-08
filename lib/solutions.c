#include "solutions.h"

int *array_init()
{
    int *arr = malloc(sizeof(int) * DIM);
    for (int i = 0; i < DIM; i++)
        scanf("%d", &arr[i]);
    return arr;
}

void array_print(int *arr)
{
    for (int i = 0; i < DIM; i++)
        printf(" %d ", arr[i]); // erro com valor não inicializado, por conta do 'i'
    printf("\n");
}

int fitness(int *route)
{
	int pA, pB = 0, distance = 0;

    for (int i = 0; i < G->V; i++)
    {
    	pA = pB;
    	pB = route[i];
        distance += G->adj[pA][pB];
    }
    return distance;
}

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
    int demand[DIM];

    // copia a demanda
    for (int i = 0; i < G->V; i++)
        demand[i] = DEMAND[i];

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

void solution_print(Solution *s)
{
    array_print(s->route);
    printf("%d\n", s->distance);
}
