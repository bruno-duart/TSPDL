#include "lists.h"

PointerNode *new_pnode(void *p, int value){
    /**
     * Função para criar um novo nó na lista
     * @param index_i: índice do vértice alterado
     * @param undo_color: cor que desfaz a alteração
     * @param value: número de iterações que o movimento é tabu
     * @return node: novo nó criado
    */
    PointerNode *node = malloc(sizeof(PointerNode));
    node->p = p;
    node->value = value;
    node->next = NULL;
    return node;
}

PointerNode *new_snode(Solution* s, int value){
    Solution *sNew = solution_duplicate(s);
    return new_pnode((void*) sNew, value);
}

PointerNode *new_2inode(int i, int j, int value){
    int *arr = malloc(sizeof(int) * 2);
    arr[0] = i;
    arr[1] = j;
    return new_pnode((void*) arr, value);
}

void free_pnode(PointerNode *node, ptr_handler_t free_content)
{
	if(free_content != NULL)
		(*free_content)(node->p);
	free(node);
}

PointerList *new_plist(){
    /**
     * Função para criar uma nova lista
     * @return list: retorna a lista que foi criada
    */
    PointerList *list = malloc(sizeof(PointerList));
    list->head = NULL;
    list->size_list = 0;
    return list;
}

void free_plist(PointerList *list, ptr_handler_t free_content){
    /**
     * Libera a memória alocada para a lista
     * @param list: lista a ter memória liberada
    */
    while(list->head != NULL){
        PointerNode *aux;
        aux = list->head;
        list->head = aux->next;
        free_pnode(aux, free_content);
    }
    free(list);
}

PointerNode *plist_at(PointerList *list, int position){
    /**
     * Função que percorre a lista até uma determinada posição
     * e retorna um ponteiro para o nó que a ocupa
     * @param list: lista a ser percorrida
     * @param position: posição desejada
     * @return aux: ponteiro para a posição desejada
    */
    PointerNode *aux = list->head;

    for(int i=0; i < position && aux != NULL; i++){
        aux = aux->next;
    }
    return aux;
}

void plist_set(PointerList *list, int position, void *p){
    /**
     * Função que altera os valores de um nó na lista.
     * @param list: lista a ter algum valor alterado
     * @param position: posição desejada
     * @param index_i: novo índice de vértice
     * @param undo_color: nova cor
    */
    PointerNode *node = plist_at(list, position);
    node->p = p;
}

int plist_size(PointerList *list){
    /**
     * Função que retorna o tamanho da lista
     * @param list: lista a ter o tamanho calculado
    */
    PointerNode *aux = list->head;
    int i = 0;

    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    list->size_list = i;
    return (int) i;
}

void plist_print(PointerList *list, ptr_handler_t print_content){
    /**
     * Função para exibir a lista no console.
     * @param list: lista ser exibida
    */
    PointerNode *aux = list->head;
    while(aux != NULL){
        //printf("(%d,%d)", aux->index_i, aux->undo_color);
        print_content(aux->p);
        if(aux->next != NULL){
            printf("->");
        }
        aux = aux->next;
    }
    printf("\n");
}

void plist_insert(PointerList *l, void *p, int value, int position){
    /**
     * Função para inserir um novo nó na lista.
     * @param list: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param value: número de iterações com o movimento restrito
     * @param position: posição onde o novo nó deve ser inserido
    */
    PointerNode *node = new_pnode(p, value);

    if(position == 0){
        node->next = l->head;
        l->head = node;
    } else{
        PointerNode *aux = plist_at(l, position-1);
        node->next = aux->next;
        aux->next = node;
    }
    l->size_list++;
}

void plist_push_front(PointerList *l, void *p, int value){
    /**
     * Função para inserir um vértice no início da lista
     * @param l: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param value: número de iterações com o movimento restrito
    */
    plist_insert(l, p, value, 0);
}

void plist_push_back(PointerList *l, void *p, int value){
    /**
     * Função para inserir um vértice no final da lista
     * @param l: lista a ter um novo nó
     * @param index_i: índice do vértice correspondente
     * @param undo_color: cor que desfaz o movimento tabu
     * @param value: número de iterações com o movimento restrito
    */
    plist_insert(l, p, value, l->size_list);
}

void plist_erase(PointerList *l, int position, ptr_handler_t free_content){
    /**
     * Função para apagar um elemento de uma lista, 
     * em uma determinada posição.
     * @param l: lista a ter um elemento removido
     * @param position: posição do elemento a ser removido
    */
    PointerNode *aux, *ptr;
    if(position == 0){
        ptr = l->head;
        l->head = ptr->next;
    } else{
        aux = plist_at(l, position-1);
        ptr = aux->next;
        aux->next = ptr->next;
    }
    free_pnode(ptr, free_content);
    l->size_list--;
}

void plist_pop_front(PointerList *l, ptr_handler_t free_content){
    /**
     * Função para remover o primeiro elemento da lista
     * @param l: lista a ter o primeiro elemento removido
    */
    plist_erase(l, 0, free_content);
}

void plist_pop_back(PointerList *l, ptr_handler_t free_content){
    /**
     * Função para remover o último elemento da lista
     * @param l: lista a ter o último elemento removido
    */
     plist_erase(l, l->size_list-1, free_content);
}
