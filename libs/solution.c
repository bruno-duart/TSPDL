#include "solution.h"

int* ini_array(){
    int *arr = malloc(sizeof(int) * DIM);
    int value;
    for(int i=0; i < DIM; i++)
        scanf("%d", &arr[i]);
    return arr;
}

void print_arr(int *arr){
    for(int i=0; i < DIM; i++)
        printf(" %d ",arr[i]); //erro com valor não inicializado, por conta do 'i'
    printf("\n");
}

Solution* new_solution(){
    Solution* sol = malloc(sizeof(Solution));
    sol->port = malloc(sizeof(int) * DIM);
    sol->distance = __INT16_MAX__;

    for(int i=0; i < DIM; i++)
        sol->port[i] = 0;
    return sol;
}

void free_solution(Solution *S){
    free(S->port);
    free(S);
}

bool is_Solution(int *port){
    int weight = G->V-1;
    int demand[DIM];

    //copia a demanda
    for(int i=0; i < G->V; i++)
        demand[i] = DEMAND[i];
    
    for(int i=0; i < G->V - 1; i++){
        //verifica o indice dos portos
        if(port[i] < 0)
            return false;
        //verifica se o porto de origem está sendo visitado antes da hora
        if(port[i] == 0)
            return false;
        //verifica a condição do calado
        if(DRAFT[port[i]] < weight)
            return false;
        //verifica se a demanda já foi atendida
        if(!demand[port[i]])
            return false;
        //senão, atende à demanda e diminui o peso
        demand[port[i]] = 0;
        weight--;
    }
    //verifica se o navio retorna ao porto de origem
    return (port[DIM-1] == 0);
}

int fitness(int *port){
    int distance = G->adj[0][ port[0] ];

    for(int i = 1; i < G->V; i++){
        distance += G->adj[ port[i-1] ][ port[i] ];
    }
    return distance;
}

int isIn(int port, int *route){
    for(int i = 0; i < G->V; i++)
        if(route[i] == port)
            return 1;
    return 0;
}

int indexOf(Solution **Arr, int value){
    for(int i = 0; i < 2 * G->V; i++)
        if(Arr[i]->distance == value)
            return i;
    return -1;
}


Solution* build_solution(){
    /*
    	Constrói uma solução viável para o conjunto de soluções relativo à 
    	população inicial do algoritmo genético. A construção é realizada
   	com o método guloso com características aleatórias, através do qual
    	dois portos são sorteados aleatoriamente para comporem o início da solução, 
    	e em seguida, aplica-se o método guloso para obter uma solução viável.
    */
    Solution *newSolution = new_solution(G->V);
    int port1, port2, weight = G->V-1, smaller, position, k;
    int *demand = malloc(sizeof(int) * G->V);
    
    //Cópia do array de demandas, permitindo que seja possível alterá-lo sem preocupações
    for(int i=0; i<G->V; i++)
        demand[i] = DEMAND[i];
    
    //Seleção dos dois portos iniciais. Port1 e port2 devem ser diferentes entre si
    //e devem ser viáveis.
    do
        port1 = rand() % (G->V-1) + 1;
    while(DRAFT[port1] < (weight));
    weight--;

    do
        port2 = rand() % (G->V-1) + 1;
    while(DRAFT[port2] < weight || port2 == port1);
    weight--;

    //Inicialização da solução, atualização da distância percorrida
    newSolution->port[0] = port1;
    newSolution->port[1] = port2;
    newSolution->distance = G->adj[0][port1] + G->adj[port1][port2];
    demand[port1] = demand[port2] = 0;
    k = port2;

    //Etapa gulosa da construção.
    for(int i = 2; i < G->V; i++){
        smaller = __INT16_MAX__;
        for(int j = 0; j < G->V; j++)
            if(G->adj[k][j] < smaller && demand[j] == 1 && weight <= DRAFT[j]){
                position = j;
                smaller = G->adj[k][j];
            }    
        if(smaller != __INT16_MAX__){
            //printf("K = %d\n", position);
            k = position;
            newSolution->port[i] = k;
            weight--;
            newSolution->distance += smaller;
            demand[k] = 0;
        }
       // print_arr(G->V, newSolution->port);
    }
    newSolution->distance += G->adj[k][0];
    //print_arr(G->V, newSolution->port);
    //printf("Weight: %d\n",weight);
    //exit(1);

    free(demand);
    return newSolution;    
}


void copiar(Solution *S, int *solucao){
    /*
    	Função utilizada para efetuar a cópia do conteúdo 
    	dos ponteiros de Solution
    */
    for(int i = 0; i < G->V; i++)
        S->port[i] = solucao[i];
    S->distance = fitness(solucao);
}




void fixed_swap(Solution* s){
    /* 
        Realiza a busca local utilizando o critério de troca
        fixa. Todas as posições são trocadas uma com as outras.
        
    */
    int aux, copy[DIM];
    
   //gera uma cópia da solução de entrada
   for(int k=0; k < G->V; k++)
       copy[k] = s->port[k];
    
    for(int i=0; i < DIM-1; i++)
        for(int j=i+1; j < DIM; j++){
            //gera uma solução
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;

            if(is_Solution(copy) && fitness(copy) < s->distance)
                copiar(s, copy);
            
            //desfaz o movimento
            aux = copy[j];
            copy[j] = copy[i];
            copy[i] = aux;
        }
}

void Swap_2opt(Solution* s){
    /*Realiza a troca de posições seguindo o critério 2-opt.*/
    //int best_route[DIM], best_distance;
    Solution *best_route = new_solution();
    int route[DIM], route_distance;

    copiar(best_route, s->port);
    best_route->distance = fitness(best_route->port);

    //number of nodes eligible to be swapped: DIM-1 (penúltimo do array)
    for(int i=0; i < DIM - 3; i++){
        for(int k = i+2; k < DIM/4; k++){
            //  1. take s[0] to s[i-1] and add them in order to route
            for(int j = 0; j < i; j++)
                route[j] = s->port[j];
            
            //2. take s[i] to s[k] and add them in reverse order to route
            for(int j = 0; j < (k - i); j++)
                route[i+j] = s->port[k-j];
            
            //3. take [k+1] to end and add them in order to route
            for(int j = k; j < DIM - 1; j++)
                route[j] = s->port[j];
            
            if(is_Solution(route)){ //Verifica se a solução gerada é viável
                route_distance = fitness(route);
                if(route_distance < best_route->distance){ //Verifica se a solução é melhor que a corrente
                    copiar(best_route, route);
                    best_route->distance = route_distance;
                    //return;
                }
            }
        }
    } 

    //Atualiza a melhor solução
    copiar(s, best_route->port);        
}

int reverse_segment_if_better(Solution* s, int i, int j, int k){
    int A = s->port[i-1], B = s->port[i], C = s->port[j-1];
    int D = s->port[j], E = s->port[k-1], F = s->port[k % DIM];

    int d0, d1, d2, d3, d4;
    d0 = G->adj[A][B] + G->adj[C][D] + G->adj[E][F];
    d1 = G->adj[A][C] + G->adj[B][D] + G->adj[E][F];
    d2 = G->adj[A][B] + G->adj[C][E] + G->adj[D][F];
    d3 = G->adj[A][D] + G->adj[E][B] + G->adj[C][F];
    d4 = G->adj[F][B] + G->adj[C][D] + G->adj[E][A];

    if(d0 > d1){
        /*  
            tour[i:j] = reversed(tour[i:j])
            return -d0 + d1 
        */
        int arr[j-i], m=0;
        for(int l = i; l < j; l++)
            arr[m++] = s->port[l];
        m -= 1;
        for(int l = i; l < j; l++)
            s->port[l] = arr[m--];
        return -d0 + d1;
    }
    else if(d0 > d2){
        /*
            tour[j:k] = reversed(tour[j:k])
            return -d0 + d2
        */
        int arr[k-j], m=0;
        for(int l = j; l < k; l++)
            arr[m++] = s->port[l];
        m -= 1;
        for(int l = j; l < k; l++)
            s->port[l] = arr[m--];
        return -d0 + d2;
    }
    else if(d0 > d4){
        /*
            tour[i:k] = reversed(tour[i:k])
            return -d0 + d4
        */
        int arr[k-i], m=0;
        for(int l = i; l < k; l++)
            arr[m++] = s->port[l];
        m -= 1;
        for(int l = i; l < k; l++)
            s->port[l] = arr[m--];
        return -d0 + d4;
    }
    else if(d0 > d3){
        /*
            tmp = tour[j:k] + tour[i:j]
            tour[i:k] = tmp
            return -d0 + d3        
        */
        int arr[k-i], m=0;
        for(int l = j; l < k; l++)
            arr[m++] = s->port[l];
        for(int l = i; l < j; l++)
            arr[m++] = s->port[l];
        return -d0 + d3;
    }
    return 0;
}

void Swap_3opt(Solution* s){
    int delta;
   // while(1){
        delta = 0;
        for(int i = 0; i < DIM + 4; i++){
            for(int j = i+2; j < DIM + 2; j++){
                for(int k = j+2; k < DIM + (i>0); k++){
                    delta += reverse_segment_if_better(s, i, j, k);
                }
            }
        }
        /*if(delta >= 0)
            break;*/
        //printf("Entrei\n");
    //}
    s->distance = fitness(s->port);
}

void shuffle(Solution **Arr, int nChanges){
    Solution *aux;
    int idx1, idx2;

    for(int i = 0; i < nChanges; i++){
        idx1 = rand() % (2 * G->V - 1);
        do{
            idx2 = rand() % (2 * G->V - 1);
        }while(idx1 == idx2);
        aux = Arr[idx1];
        Arr[idx1] = Arr[idx2];
        Arr[idx2] = aux;
    }
}