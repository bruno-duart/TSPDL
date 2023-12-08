#include "headers.h"

int *ini_array()
{
    int *arr = malloc(sizeof(int) * DIM);
    int value;
    for (int i = 0; i < DIM; i++)
        scanf("%d", &arr[i]);
    return arr;
}

void print_arr(int *arr)
{
    for (int i = 0; i < DIM; i++)
        printf(" %d ", arr[i]); // erro com valor não inicializado, por conta do 'i'
    printf("\n");
}

int* new_solution(int n)
{
    int* new_s = (int*)malloc(sizeof(int) * n);
    return new_s;
}

void free_solution(int* s)
{
    free(s);
}

bool is_Solution(int *s)
{
    int weight = G->V - 1;
    int demand[DIM];

    // copia a demanda
    for (int i = 0; i < G->V; i++)
        demand[i] = DEMAND[i];

    for (int i = 0; i < G->V - 1; i++)
    {
        // verifica o indice dos portos
        if (s[i] < 0)
            return false;
        // verifica se o porto de origem está sendo visitado antes da hora
        if (s[i] == 0)
            return false;
        // verifica a condição do calado
        if (DRAFT[s[i]] < weight)
            return false;
        // verifica se a demanda já foi atendida
        if (!demand[s[i]])
            return false;
        // senão, atende à demanda e diminui o peso
        demand[s[i]] = 0;
        weight--;
    }
    // verifica se o navio retorna ao porto de origem
    return (s[DIM - 1] == 0);
}

bool is_same_solution(int* sA, int* sB)
{
    for (int i = 0; i < G->V; i++)
    {
        if (sA[i] != sB[i])
        {
            return false;
        }
    }
    return true;
}

int fitness(int *port)
{
    int distance = G->adj[0][port[0]];
    
    for (int i = 1; i < G->V; i++)
    {
        distance += G->adj[port[i - 1]][port[i]];
    }
    return distance;
}

int isIn(int port, int *route)
{
    for (int i = 0; i < G->V; i++)
        if (route[i] == port)
            return 1;
    return 0;
}

int indexOf(int **Arr, int value)
{
    for (int i = 0; i < 2 * G->V; i++)
        if (fitness(Arr[i]) == value)
            return i;
    return -1;
}

int* random_solution(int n){
    int *s = new_solution(n);
    s[G->V-1] = 0;
    
    do{
        for(int i=0; i<G->V-1; i++)
        {
            s[i] = rand() % G->V;
            for(int j=0; j<i; j++)
                if(s[j] == s[i])
                {
                    i--;
                    break;
                }
        }
    }while(!is_Solution(s));
    
    return s;
}

int* greedy_method(int n)
{
    int* new_s = new_solution(n);
    int weight = G->V - 1, smaller, position, k = 0;
    int *demand = (int*) malloc(sizeof(int) * G->V);
    

    for (int i = 0; i < G->V; i++)
        demand[i] = DEMAND[i];
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
            new_s[i] = k;
            weight--;
            demand[k] = 0;
        }
    }

    free(demand);
    return new_s;
}

int* build_solution_pseudo_greedy(int n)
{
    /*
        Constrói uma solução viável para o conjunto de soluções relativo à
        população inicial do algoritmo genético. A construção é realizada
    com o método guloso com características aleatórias, através do qual
        dois portos são sorteados aleatoriamente para comporem o início da solução,
        e em seguida, aplica-se o método guloso para obter uma solução viável.
    */
    int* new_s = new_solution(n);
    int port1, port2, weight = G->V - 1, smaller, position, k;
    int *demand = malloc(sizeof(int) * G->V);

    // Cópia do array de demandas, permitindo que seja possível alterá-lo sem preocupações
    for (int i = 0; i < G->V; i++)
        demand[i] = DEMAND[i];

    // Seleção dos dois portos iniciais. Port1 e port2 devem ser diferentes entre si
    // e devem ser viáveis.
    do
        port1 = rand() % (G->V - 1) + 1;
    while (DRAFT[port1] < (weight));
    weight--;

    do
        port2 = rand() % (G->V - 1) + 1;
    while (DRAFT[port2] < weight || port2 == port1);
    weight--;

    // Inicialização da solução, atualização da distância percorrida
    new_s[0] = port1;
    new_s[1] = port2;
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
            new_s[i] = k;
            weight--;
            demand[k] = 0;
        }
    }

    free(demand);
    return new_s;
}

void copy_solution(int* S_target, int* ports)
{
    /*
        Função utilizada para efetuar a cópia do conteúdo
        dos ponteiros de Solution
    */
    for (int i = 0; i < G->V; i++)
        S_target[i] = ports[i];
}

ResultLocalSearch* random_swap(int* s0, int index_i, int index_j, int n)
{
    ResultLocalSearch* res = new_resultlocalsearch(n);
    int index_1, index_2, aux, distance_i;
    int *copy = malloc(sizeof(int) * (G->V));
    //Solution *s_new = new_solution();
    copy_solution(res->s, s0);
    res->index_i = index_i;
    res->index_j = index_j;

    for (int i = 0; i < 100; i++)
    {
        for (int k = 0; k < G->V; k++)
            copy[k] = s0[k];
        do
        {
            index_1 = rand() % (G->V - 1);
            do
            {
                index_2 = rand() % (G->V - 1);
            } while (index_1 == index_2);

            aux = copy[index_2];
            copy[index_2] = copy[index_1];
            copy[index_1] = aux;
        } while (!is_Solution(copy));

        distance_i = fitness(copy);
        // print_arr(copy);
        // printf("%d\n", distance_i);
        if (distance_i < fitness(res->s))
        {
            copy_solution(res->s, copy);
            
            res->index_i = index_1;
            res->index_j = index_2;
        }
    }
    free(copy);

    return res;
}


ResultLocalSearch* random_swap_first(int* s0, int n)
{
    ResultLocalSearch* res = new_resultlocalsearch(n);
    int index_1, index_2, aux, distance_i;
    int *copy = malloc(sizeof(int) * (G->V));
    //Solution *s_new = new_solution();
    copy_solution(res->s, s0);
    res->index_i = 0;
    res->index_j =0;

    for (int i = 0; i < 100; i++)
    {
        for (int k = 0; k < G->V; k++)
            copy[k] = s0[k];
        do
        {
            index_1 = rand() % (G->V - 1);
            do
            {
                index_2 = rand() % (G->V - 1);
            } while (index_1 == index_2);

            aux = copy[index_2];
            copy[index_2] = copy[index_1];
            copy[index_1] = aux;
        } while (!is_Solution(copy));

        distance_i = fitness(copy);
        // print_arr(copy);
        // printf("%d\n", distance_i);
        if (distance_i < fitness(res->s))
        {
            copy_solution(res->s, copy);
            
            res->index_i = index_1;
            res->index_j = index_2;
        }
    }
    free(copy);

    return res;
}

ResultLocalSearch* fixed_swap(int* s0, int index_i, int index_j, int n)
{
    ResultLocalSearch* res = new_resultlocalsearch(n);
    int aux, copy[DIM];

    copy_solution(res->s, s0);
    res->index_i = index_i;
    res->index_j = index_j;
    // copies entry solution
    for (int k = 0; k < G->V; k++)
        copy[k] = s0[k];

    // Makes swaps between positions of the solution
    for (int i = 0; i < DIM - 1; i++)
    {
        for (int j = i + 1; j < DIM; j++)
        {
            // Swaping generates a "new" solution
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;

            if (is_Solution(copy) && fitness(copy) < fitness(res->s)){
                copy_solution(res->s, copy);
                res->index_i = i;
                res->index_j = j;
            }                

            // Undo movement, to allow next iteration
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;
        }
    }

    return res;
}

void Swap_2opt(int* s, int n)
{
    /*Realiza a troca de posições seguindo o critério 2-opt.*/
    int* best_route = new_solution(n);
    int route[DIM], route_distance;

    copy_solution(best_route, s);
    
    // number of nodes eligible to be swapped: DIM-1 (penúltimo do array)
    for (int i = 0; i < DIM - 3; i++)
    {
        for (int k = i + 2; k < DIM / 4; k++)
        {
            //  1. take s[0] to s[i-1] and add them in order to route
            for (int j = 0; j < i; j++)
                route[j] = s[j];

            // 2. take s[i] to s[k] and add them in reverse order to route
            for (int j = 0; j < (k - i); j++)
                route[i + j] = s[k - j];

            // 3. take [k+1] to end and add them in order to route
            for (int j = k; j < DIM - 1; j++)
                route[j] = s[j];

            if (is_Solution(route))
            { // Verifica se a solução gerada é viável
                route_distance = fitness(route);
                if (route_distance < fitness(best_route))
                { // Verifica se a solução é melhor que a corrente
                    copy_solution(best_route, route);
                    // return;
                }
            }
        }
    }

    // Atualiza a melhor solução
    copy_solution(s, best_route);
}

ResultLocalSearch* swap_2opt(int* s0, int index_i, int index_j, int n)
{
    ResultLocalSearch* res = new_resultlocalsearch(n);
    int route[DIM], route_distance;

    copy_solution(res->s, s0);
    res->index_i = index_i;
    res->index_j = index_j;

    // number of nodes eligible to be swapped: DIM-1 (penúltimo do array)
    for (int i = 0; i < DIM - 3; i++)
    {
        for (int k = i + 2; k < DIM / 4; k++)
        {
            //  1. take s[0] to s[i-1] and add them in order to route
            for (int j = 0; j < i; j++)
                route[j] =  s0[j];

            // 2. take s[i] to s[k] and add them in reverse order to route
            for (int j = 0; j < (k - i); j++)
                route[i + j] = s0[k - j];

            // 3. take [k+1] to end and add them in order to route
            for (int j = k; j < DIM - 1; j++)
                route[j] = s0[j];

            if (is_Solution(route))
            { // Verifies if generated solution is valid
                route_distance = fitness(route);
                if (route_distance < fitness(res->s))
                { // Verifies if solution is better than the current one
                    copy_solution(res->s, route);
                    res->index_i = i;
                    res->index_j = k;
                }
            }
        }
    }

    return res;
}

int reverse_segment_if_better(int* s, int i, int j, int k)
{
    int A = s[i - 1], B = s[i], C = s[j - 1];
    int D = s[j], E = s[k - 1], F = s[k % DIM];

    int d0, d1, d2, d3, d4;
    d0 = G->adj[A][B] + G->adj[C][D] + G->adj[E][F];
    d1 = G->adj[A][C] + G->adj[B][D] + G->adj[E][F];
    d2 = G->adj[A][B] + G->adj[C][E] + G->adj[D][F];
    d3 = G->adj[A][D] + G->adj[E][B] + G->adj[C][F];
    d4 = G->adj[F][B] + G->adj[C][D] + G->adj[E][A];

    if (d0 > d1)
    {
        int arr[j - i], m = 0;
        for (int l = i; l < j; l++)
            arr[m++] = s[l];
        m -= 1;
        for (int l = i; l < j; l++)
            s[l] = arr[m--];
        return -d0 + d1;
    }
    else if (d0 > d2)
    {
        int arr[k - j], m = 0;
        for (int l = j; l < k; l++)
            arr[m++] = s[l];
        m -= 1;
        for (int l = j; l < k; l++)
            s[l] = arr[m--];
        return -d0 + d2;
    }
    else if (d0 > d4)
    {
        int arr[k - i], m = 0;
        for (int l = i; l < k; l++)
            arr[m++] = s[l];
        m -= 1;
        for (int l = i; l < k; l++)
            s[l] = arr[m--];
        return -d0 + d4;
    }
    else if (d0 > d3)
    {
        int arr[k - i], m = 0;
        for (int l = j; l < k; l++)
            arr[m++] = s[l];
        for (int l = i; l < j; l++)
            arr[m++] = s[l];
        return -d0 + d3;
    }
    return 0;
}

void Swap_3opt(int* s)
{
    int delta;
    // while(1){
    delta = 0;
    for (int i = 0; i < DIM + 4; i++)
    {
        for (int j = i + 2; j < DIM + 2; j++)
        {
            for (int k = j + 2; k < DIM + (i > 0); k++)
            {
                delta += reverse_segment_if_better(s, i, j, k);
            }
        }
    }
    /*if(delta >= 0)
        break;*/
    // printf("Entrei\n");
    //}
}

int* swap_3opt(int* s, int n)
{
    int delta = 0;
    int* s_new = new_solution(n);
    copy_solution(s_new, s);

    for (int i = 0; i < DIM + 4; i++)
    {
        for (int j = i + 2; j < DIM + 2; j++)
        {
            for (int k = j + 2; k < DIM + (i > 0); k++)
            {
                delta += reverse_segment_if_better(s, i, j, k);
            }
        }
    }

    return s_new;
}

void shuffle(int** Arr, int nChanges)
{
    int* aux;
    int idx1, idx2;

    for (int i = 0; i < nChanges; i++)
    {
        idx1 = rand() % (2 * G->V - 1);
        do
        {
            idx2 = rand() % (2 * G->V - 1);
        } while (idx1 == idx2);
        aux = Arr[idx1];
        Arr[idx1] = Arr[idx2];
        Arr[idx2] = aux;
    }
}

void print_solution(int* s)
{
    print_arr(s);
    printf("%d\n", fitness(s));
}

ResultLocalSearch* new_resultlocalsearch(int n){
    ResultLocalSearch* res = malloc(sizeof(ResultLocalSearch));
    res->s = new_solution(n);

    return res;
}

void free_resultlocalsearch(ResultLocalSearch* res){
    free_solution(res->s);
    free(res);
}

void print_resultlocalsearch(ResultLocalSearch* res){
    printf("(%d,%d) ", res->index_i, res->index_j);
    print_solution(res->s);

}