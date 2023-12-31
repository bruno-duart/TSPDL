#include "solution_pointer.h"

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

Solution *new_solution()
{
    Solution *sol = malloc(sizeof(Solution));
    sol->port = malloc(sizeof(int) * DIM);
    sol->distance = 0;

    for (int i = 0; i < DIM; i++)
        sol->port[i] = 0;
    return sol;
}

void free_solution(Solution *S)
{
    free(S->port);
    free(S);
}

bool is_Solution(int *port)
{
    int weight = G->V - 1;
    int demand[DIM];

    // copia a demanda
    for (int i = 0; i < G->V; i++)
        demand[i] = DEMAND[i];

    for (int i = 0; i < G->V - 1; i++)
    {
        // verifica o indice dos portos
        if (port[i] < 0)
            return false;
        // verifica se o porto de origem está sendo visitado antes da hora
        if (port[i] == 0)
            return false;
        // verifica a condição do calado
        if (DRAFT[port[i]] < weight)
            return false;
        // verifica se a demanda já foi atendida
        if (!demand[port[i]])
            return false;
        // senão, atende à demanda e diminui o peso
        demand[port[i]] = 0;
        weight--;
    }
    // verifica se o navio retorna ao porto de origem
    return (port[DIM - 1] == 0);
}

bool is_same_solution(Solution* sA, Solution* sB)
{
    for (int i = 0; i < G->V; i++)
    {
        if (sA->port[i] != sB->port[i])
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

int indexOf(Solution **Arr, int value)
{
    for (int i = 0; i < 2 * G->V; i++)
        if (Arr[i]->distance == value)
            return i;
    return -1;
}

Solution* random_solution(){
    Solution *s = new_solution();
    s->port[G->V-1] = 0;
    
    do{
        for(int i=0; i<G->V-1; i++)
        {
            s->port[i] = rand() % G->V;
            for(int j=0; j<i; j++)
                if(s->port[j] == s->port[i])
                {
                    i--;
                    break;
                }
        }
    }while(!is_Solution(s->port));

    s->distance = fitness(s->port);
    
    return s;
}

Solution* random_solution_guided(){ 
    Solution *s = new_solution(); 
    int* visited = (int*) calloc(G->V, sizeof(int)); 
    int count_visited = 0, weight = G->V-1; 
     
    s->port[G->V-1] = 0; 
 
    for(int i=0; i<G->V-1; i++){ 
        s->port[i] = (rand() % (G->V-1)) + 1; 
        if ((weight > DRAFT[s->port[i]]) || (visited[s->port[i]]) || (weight < DEMAND[s->port[i]])) { 
            i--; 
            continue; 
        } 
        visited[s->port[i]] = 1; 
        weight--; 
        count_visited++; 
    } 
 
    s->distance = fitness(s->port); 
    free(visited);
    return s; 
}

Solution *greedy_method()
{
    Solution *newSolution = new_solution();
    int weight = G->V - 1, smaller, position, k = 0;
    int *demand = malloc(sizeof(int) * G->V);
    

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
            newSolution->port[i] = k;
            weight--;
            newSolution->distance += smaller;
            demand[k] = 0;
        }
    }
    newSolution->distance += G->adj[k][0];

    free(demand);
    return newSolution;
}

Solution *build_solution_pseudo_greedy()
{
    /*
        Constrói uma solução viável para o conjunto de soluções relativo à
        população inicial do algoritmo genético. A construção é realizada
    com o método guloso com características aleatórias, através do qual
        dois portos são sorteados aleatoriamente para comporem o início da solução,
        e em seguida, aplica-se o método guloso para obter uma solução viável.
    */
    Solution *newSolution = new_solution();
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
    newSolution->port[0] = port1;
    newSolution->port[1] = port2;
    newSolution->distance = G->adj[0][port1] + G->adj[port1][port2];
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
            newSolution->port[i] = k;
            weight--;
            newSolution->distance += smaller;
            demand[k] = 0;
        }
    }
    newSolution->distance += G->adj[k][0];

    free(demand);
    return newSolution;
}

void copy_solution(Solution *S_target, Solution *S_origin)
{
    /*
        Função utilizada para efetuar a cópia do conteúdo
        dos ponteiros de Solution
    */
    for (int i = 0; i < G->V; i++)
        S_target->port[i] = S_origin->port[i];
    S_target->distance = S_origin->distance;
}

ResultLocalSearch* random_swap(ResultLocalSearch *res0)
{
    ResultLocalSearch* res = new_resultlocalsearch();
    int index_1, index_2, aux;
    Solution *copy = new_solution();
    //Solution *s_new = new_solution();
    copy_solution(res->s, res0->s);
    res->index_i = res0->index_i;
    res->index_j = res0->index_j;

    for (int i = 0; i < 100; i++)
    {
        for (int k = 0; k < G->V; k++)
            copy->port[k] = res0->s->port[k];
        do
        {
            index_1 = rand() % (G->V - 1);
            do
            {
                index_2 = rand() % (G->V - 1);
            } while (index_1 == index_2);

            aux = copy->port[index_2];
            copy->port[index_2] = copy->port[index_1];
            copy->port[index_1] = aux;
        } while (!is_Solution(copy->port));

        copy->distance = fitness(copy->port);
        // print_arr(copy);
        // printf("%d\n", distance_i);
        if (copy->distance < res->s->distance)
        {
            copy_solution(res->s, copy);
            
            res->index_i = index_1;
            res->index_j = index_2;
        }
    }
    free_solution(copy);

    return res;
}

void random_swap_pointer (Solution* s0, int* index){
    int copy[DIM], distance;
    int index_i=index[0], index_j=index[1], aux;
    for(int i=0; i<DIM; i++)
        copy[i] = s0->port[i];
        
    for (int i=0; i < 100; i++){
        
        do
        {
            index_i = rand() % (G->V - 1);
            do
            {
                index_j = rand() % (G->V - 1);
            } while (index_i == index_j);

            aux = copy[index_i];
            copy[index_i] = copy[index_j];
            copy[index_j] = aux;
        } while (!is_Solution(copy));

       distance = fitness(copy);

       if(distance < s0->distance) {
            for(int i=0; i<DIM; i++)
                s0->port[i] = copy[i];
            s0->distance = distance;
            index[0] = index_i;
            index[1] = index_j;
        }

        aux = copy[index_j];
        copy[index_j] = copy[index_i];
        copy[index_i] = aux;
    }
}

void lsearch_random_swap(Solution* s0, int* index, int max_swaps){
    Solution* sAux = new_solution();
    copy_solution(sAux, s0);
    int aux, i, j;
    
    while(max_swaps--){
        i = randint(0, G->V-1);
        j = randintavoid(0, G->V-1, i);
        aux = sAux->port[i]; 
        sAux->port[i] = sAux->port[j];
        sAux->port[j] = aux;

        if(is_Solution(sAux->port)){
            sAux->distance = fitness(sAux->port);
            if (sAux->distance < s0->distance) {
                copy_solution(s0, sAux);
                index[0] = i;
                index[1] = j;
            }
        } else {
            aux = sAux->port[i]; 
            sAux->port[i] = sAux->port[j];
            sAux->port[j] = aux;
        }
    }
    free_solution(sAux);
}

ResultLocalSearch* random_swap_first(Solution *s0)
{
    ResultLocalSearch* res = new_resultlocalsearch();
    int index_1, index_2, aux;
    Solution *copy = new_solution();
    //Solution *s_new = new_solution();
    copy_solution(res->s, s0);
    res->index_i = 0;
    res->index_j =0;

    for (int i = 0; i < 100; i++)
    {
        for (int k = 0; k < G->V; k++)
            copy->port[k] = s0->port[k];
        do
        {
            index_1 = rand() % (G->V - 1);
            do
            {
                index_2 = rand() % (G->V - 1);
            } while (index_1 == index_2);

            aux = copy->port[index_2];
            copy->port[index_2] = copy->port[index_1];
            copy->port[index_1] = aux;
        } while (!is_Solution(copy->port));

        copy->distance = fitness(copy->port);
        // print_arr(copy);
        // printf("%d\n", distance_i);
        if (copy->distance < res->s->distance)
        {
            copy_solution(res->s, copy);
            
            res->index_i = index_1;
            res->index_j = index_2;
        }
    }
    free_solution(copy);

    return res;
}

ResultLocalSearch* fixed_swap(ResultLocalSearch *res0)
{
    ResultLocalSearch* res = new_resultlocalsearch();
    int aux;
    Solution* copy = new_solution();

    copy_solution(res->s, res0->s);
    res->index_i = res0->index_i;
    res->index_j = res0->index_j;
    // copies entry solution
    for (int k = 0; k < G->V; k++)
        copy->port[k] = res0->s->port[k];

    // Makes swaps between positions of the solution
    for (int i = 0; i < DIM - 1; i++)
    {
        for (int j = i + 1; j < DIM; j++)
        {
            // Swaping generates a "new" solution
            aux = copy->port[j];
            copy->port[j] = copy->port[i];
            copy->port[i] = aux;

            if (is_Solution(copy->port) && fitness(copy->port) < res->s->distance){
                copy_solution(res->s, copy);
                res->index_i = i;
                res->index_j = j;
            }                

            // Undo movement, to allow next iteration
            aux = copy->port[j];
            copy->port[j] = copy->port[i];
            copy->port[i] = aux;
        }
    }
    free_solution(copy);
    return res;
}

void fixed_swap_pointer(Solution *s0, int* index)
{
   int copy[DIM], distance, aux;
   int index_i=index[0], index_j = index[1];

    // copies entry solution
    for (int k = 0; k < G->V; k++)
        copy[k] = s0->port[k];

    // Makes swaps between positions of the solution
    for (int i = 0; i < DIM - 1; i++)
    {
        for (int j = i + 1; j < DIM; j++)
        {
            // Swaping generates a "new" solution
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;

            distance = fitness(copy);
            if (is_Solution(copy) && distance < s0->distance){
                for (int k = 0; k < G->V; k++)
                    s0->port[k] = copy[k];
                s0->distance = distance;
                index[0] = i;
                index[1] = j;
            }                

            // Undo movement, to allow next iteration
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;
        }
    }
}

void Swap_2opt(Solution *s)
{
    /*Realiza a troca de posições seguindo o critério 2-opt.*/
    Solution *best_route = new_solution();
    Solution *route = new_solution();

    copy_solution(best_route, s);
    best_route->distance = fitness(best_route->port);

    // number of nodes eligible to be swapped: DIM-1 (penúltimo do array)
    for (int i = 0; i < DIM - 3; i++)
    {
        for (int k = i + 2; k < DIM / 4; k++)
        {
            //  1. take s[0] to s[i-1] and add them in order to route
            for (int j = 0; j < i; j++)
                route->port[j] = s->port[j];

            // 2. take s[i] to s[k] and add them in reverse order to route
            for (int j = 0; j < (k - i); j++)
                route->port[i + j] = s->port[k - j];

            // 3. take [k+1] to end and add them in order to route
            for (int j = k; j < DIM - 1; j++)
                route->port[j] = s->port[j];

            if (is_Solution(route->port))
            { // Verifica se a solução gerada é viável
                route->distance = fitness(route->port);
                if (route->distance < best_route->distance)
                { // Verifica se a solução é melhor que a corrente
                    copy_solution(best_route, route);
                    best_route->distance = route->distance;
                    // return;
                }
            }
        }
    }

    // Atualiza a melhor solução
    copy_solution(s, best_route);
}

ResultLocalSearch* swap_2opt(ResultLocalSearch *res0)
{
    ResultLocalSearch* res = new_resultlocalsearch();
    Solution *route = new_solution();

    copy_solution(res->s, res0->s);
    res->index_i = res0->index_i;
    res->index_j = res0->index_j;

    // number of nodes eligible to be swapped: DIM-1 (penúltimo do array)
    for (int i = 0; i < DIM - 3; i++)
    {
        for (int k = i + 2; k < DIM / 4; k++)
        {
            //  1. take s[0] to s[i-1] and add them in order to route
            for (int j = 0; j < i; j++)
                route->port[j] = res0->s->port[j];

            // 2. take s[i] to s[k] and add them in reverse order to route
            for (int j = 0; j < (k - i); j++)
                route->port[i + j] = res0->s->port[k - j];

            // 3. take [k+1] to end and add them in order to route
            for (int j = k; j < DIM - 1; j++)
                route->port[j] = res0->s->port[j];

            if (is_Solution(route->port))
            { // Verifies if generated solution is valid
                route->distance = fitness(route->port);
                if (route->distance < res->s->distance)
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

// int reverse_segment_if_better(Solution *s, int i, int j, int k)
// {
//     int A = s->port[i - 1], B = s->port[i], C = s->port[j - 1];
//     int D = s->port[j], E = s->port[k - 1], F = s->port[k % DIM];

//     int d0, d1, d2, d3, d4;
//     d0 = G->adj[A][B] + G->adj[C][D] + G->adj[E][F];
//     d1 = G->adj[A][C] + G->adj[B][D] + G->adj[E][F];
//     d2 = G->adj[A][B] + G->adj[C][E] + G->adj[D][F];
//     d3 = G->adj[A][D] + G->adj[E][B] + G->adj[C][F];
//     d4 = G->adj[F][B] + G->adj[C][D] + G->adj[E][A];

//     if (d0 > d1)
//     {
//         int arr[j - i], m = 0;
//         for (int l = i; l < j; l++)
//             arr[m++] = s->port[l];
//         m -= 1;
//         for (int l = i; l < j; l++)
//             s->port[l] = arr[m--];
//         return -d0 + d1;
//     }
//     else if (d0 > d2)
//     {
//         int arr[k - j], m = 0;
//         for (int l = j; l < k; l++)
//             arr[m++] = s->port[l];
//         m -= 1;
//         for (int l = j; l < k; l++)
//             s->port[l] = arr[m--];
//         return -d0 + d2;
//     }
//     else if (d0 > d4)
//     {
//         int arr[k - i], m = 0;
//         for (int l = i; l < k; l++)
//             arr[m++] = s->port[l];
//         m -= 1;
//         for (int l = i; l < k; l++)
//             s->port[l] = arr[m--];
//         return -d0 + d4;
//     }
//     else if (d0 > d3)
//     {
//         int arr[k - i], m = 0;
//         for (int l = j; l < k; l++)
//             arr[m++] = s->port[l];
//         for (int l = i; l < j; l++)
//             arr[m++] = s->port[l];
//         return -d0 + d3;
//     }
//     return 0;
// }

// void Swap_3opt(Solution *s)
// {
//     int delta;
//     // while(1){
//     delta = 0;
//     for (int i = 0; i < DIM + 4; i++)
//     {
//         for (int j = i + 2; j < DIM + 2; j++)
//         {
//             for (int k = j + 2; k < DIM + (i > 0); k++)
//             {
//                 delta += reverse_segment_if_better(s, i, j, k);
//             }
//         }
//     }
//     /*if(delta >= 0)
//         break;*/
//     // printf("Entrei\n");
//     //}
//     s->distance = fitness(s->port);
// }

// Solution *swap_3opt(Solution *s)
// {
//     int delta = 0;
//     Solution *s_new = new_solution();
//     copy_solution(s_new, s->port);

//     for (int i = 0; i < DIM + 4; i++)
//     {
//         for (int j = i + 2; j < DIM + 2; j++)
//         {
//             for (int k = j + 2; k < DIM + (i > 0); k++)
//             {
//                 delta += reverse_segment_if_better(s, i, j, k);
//             }
//         }
//     }

//     s->distance = fitness(s->port);

//     return s_new;
// }

void shuffle(Solution **Arr, int nChanges)
{
    Solution *aux;
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

void print_solution(Solution *s)
{
    print_arr(s->port);
    printf("%d\n", s->distance);
}

ResultLocalSearch* new_resultlocalsearch(){
    ResultLocalSearch* res = malloc(sizeof(ResultLocalSearch));
    res->s = new_solution();

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