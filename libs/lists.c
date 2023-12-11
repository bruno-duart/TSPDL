#include "lists.h"

node_t *new_node(Solution* s, int T_iter){
    /**
     * Função para criar um novo nó na lista
     * @param index_i: índice do vértice alterado
     * @param undo_color: cor que desfaz a alteração
     * @param T_iter: número de iterações que o movimento é tabu
     * @return node: novo nó criado
    */
    node_t *node = malloc(sizeof(node_t));
    
    node->s = new_solution();
    copy_solution(node->s, s->port);
    node->count_iter = T_iter;
    node->next = NULL;
    
    return node;
}

list_solution *new_list(){
    /**
     * Função para criar uma nova lista
     * @return list: retorna a lista que foi criada
    */
    list_solution *list = malloc(sizeof(list_solution));

    list->head = NULL;
    list->size_list = 0;

    return list;
}

void free_list(list_solution *list){
    /**
     * Libera a memória alocada para a lista
     * @param list: lista a ter memória liberada
    */
    
    while(list->head != NULL){
        node_t *aux;
        aux = list->head;
        free_solution(aux->s);
        list->head = aux->next;
        free(aux);
    }

    free(list);
}

node_t *list_at(list_solution *list, int position){
    /**
     * Função que percorre a lista até uma determinada posição
     * e retorna um ponteiro para o nó que a ocupa
     * @param list: lista a ser percorrida
     * @param position: posição desejada
     * @return aux: ponteiro para a posição desejada
    */
    node_t *aux = list->head;

    for(int i=0; i < position && aux != NULL; i++){
        aux = aux->next;
    }
    return aux;
}

void list_set(list_solution *list, int position, Solution* s){
    /**
     * Função que altera os valores de um nó na lista.
     * @param list: lista a ter algum valor alterado
     * @param position: posição desejada
     * @param index_i: novo índice de vértice
     * @param undo_color: nova cor
    */
    node_t *node = list_at(list, position);
    copy_solution(node->s, s->port);
}

int list_size(list_solution *list){
    /**
     * Função que retorna o tamanho da lista
     * @param list: lista a ter o tamanho calculado
    */
    node_t *aux = list->head;
    int i = 0;

    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    list->size_list = i;
    return (int) i;
}

void print_list(list_solution *list){
    /**
     * Função para exibir a lista no console.
     * @param list: lista ser exibida
    */
    node_t *aux = list->head;
    while(aux != NULL){
        //printf("(%d,%d)", aux->index_i, aux->undo_color);
        print_solution(aux->s);
        if(aux->next != NULL){
            printf("->");
        }
        aux = aux->next;
    }
    printf("\n");
}

void list_insert(list_solution *l, Solution* s, int T_iter, int position){
    /**
     * Função para inserir um novo nó na lista.
     * @param list: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param T_iter: número de iterações com o movimento restrito
     * @param position: posição onde o novo nó deve ser inserido
    */
    node_t *node = new_node(s, T_iter);

    if(position == 0){
        node->next = l->head;
        l->head = node;
    } else{
        node_t *aux = list_at(l, position-1);
        node->next = aux->next;
        aux->next = node;
    }
    l->size_list++;
}

void list_push_front(list_solution *l, Solution* s, int T_iter){
    /**
     * Função para inserir um vértice no início da lista
     * @param l: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param T_iter: número de iterações com o movimento restrito
    */
    list_insert(l, s, T_iter, 0);
}

void list_push_back(list_solution *l, Solution* s, int T_iter){
    /**
     * Função para inserir um vértice no final da lista
     * @param l: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param T_iter: número de iterações com o movimento restrito
    */
    list_insert(l, s, T_iter, l->size_list);
}

void list_erase(list_solution *l, int position){
    /**
     * Função para apagar um elemento de uma lista, 
     * em uma determinada posição.
     * @param l: lista a ter um elemento removido
     * @param position: posição do elemento a ser removido
    */
    node_t *aux, *ptr;
    Solution* value;
    if(position == 0){
        ptr = l->head;
        l->head = ptr->next;
        value = ptr->s;
    } else{
        aux = list_at(l, position-1);
        ptr = aux->next;
        value = ptr->s;
        aux->next = ptr->next;
    }
    free_solution(value);
    free(ptr);
    l->size_list--;
}

void list_pop_front(list_solution *l){
    /**
     * Função para remover o primeiro elemento da lista
     * @param l: lista a ter o primeiro elemento removido
    */
    list_erase(l, 0);
}

void list_pop_back(list_solution *l){
    /**
     * Função para remover o último elemento da lista
     * @param l: lista a ter o último elemento removido
    */
     list_erase(l, l->size_list-1);
}