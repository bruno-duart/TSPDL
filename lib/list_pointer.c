#include "list_pointer.h"

node_t *new_node(int index_i, int index_j, int T_iter){
    node_t *node = malloc(sizeof(node_t));
    
    node->count_iter = T_iter;
    node->index_i = index_i;
    node->index_j = index_j;
    node->next = NULL;
    
    return node;
}
list_tuples *new_list(){
    list_tuples *list = malloc(sizeof(list_tuples));

    list->head = NULL;
    list->size_list = 0;

    return list;
}
void free_list(list_tuples *list){
    while(list->head != NULL){
        node_t *aux;
        aux = list->head;
        list->head = aux->next;
        free(aux);
    }

    free(list);
}

node_t *list_at(list_tuples *list, int position){
    node_t *aux = list->head;

    for(int i=0; i < position && aux != NULL; i++){
        aux = aux->next;
    }
    return aux;
}
void list_set(list_tuples *list, int position, int index_i, int index_j){
    node_t *node = list_at(list, position);
    node->index_i = index_i;
    node->index_j = index_j;
}
int list_size(list_tuples *list){
    node_t *aux = list->head;
    int i = 0;

    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    list->size_list = i;
    return (int) i;
}
void print_list(list_tuples *list){
    node_t *aux = list->head;
    while(aux != NULL){
        printf("(%d,%d)", aux->index_i, aux->index_j);
        if(aux->next != NULL){
            printf("->");
        }
        aux = aux->next;
    }
    printf("\n");
}

void list_insert(list_tuples *list, int index_i, int index_j, int T_iter, int position){
    node_t *node = new_node(index_i, index_j, T_iter);

    if(position == 0){
        node->next = list->head;
        list->head = node;
    } else{
        node_t *aux = list_at(list, position-1);
        node->next = aux->next;
        aux->next = node;
    }
    list->size_list++;
}
void list_push_front(list_tuples *list, int index_i, int index_j, int T_iter){
    list_insert(list, index_i, index_j, T_iter, 0);
}
void list_push_back(list_tuples *list, int index_i, int index_j, int T_iter){
    list_insert(list, index_i, index_j, T_iter, list->size_list);
}

void list_erase(list_tuples *list, int position){
    node_t *aux, *ptr;
    if(position == 0){
        ptr = list->head;
        list->head = ptr->next;
    } else{
        aux = list_at(list, position-1);
        ptr = aux->next;
        aux->next = ptr->next;
    }
    free(ptr);
    list->size_list--;
}
void list_pop_front(list_tuples *list){
    list_erase(list, 0);
}
void list_pop_back(list_tuples *list){
    list_erase(list, list->size_list-1);
}