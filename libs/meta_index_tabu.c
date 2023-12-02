#include "meta_index_tabu.h"

TabuList* new_tabu_list(int capacity)
{
    TabuList* tabu_list = malloc(sizeof(TabuList));
    tabu_list->list = new_list();
    tabu_list->max_capacity = capacity;

    return tabu_list;
}

Solution* tabu_search(Solution* s0, Graph* G, int iter_restricao, int size_tabu_list, int alpha)
{
    TabuList* tabu_list = new_tabu_list(size_tabu_list);
    Solution* curr_s = new_solution(), *aux;
    Solution* best_s = new_solution();
    copy_solution(curr_s, s0->port);
    copy_solution(best_s, s0->port);
    ResultLocalSearch* new_res;
    
    //ResultLocalSearch* new_res2;
    
    ResultLocalSearch* new_res3;
    int index_tabu, iter_no_improv = 0;
    while (iter_no_improv < 100)
    {
        if (iter_no_improv % 10 == 0) {
            aux = random_solution();
            copy_solution(curr_s, aux->port);
            free_solution(aux);
        }
        new_res = random_swap_first(curr_s); // recebe resultado da busca local - definir
        new_res3 = fixed_swap(new_res);
        //new_res3 = swap_2opt(curr_s);
        //print_tabu_list(tabu_list);
        //print_resultlocalsearch(new_res);
        // local_search
        index_tabu = is_in_tabu_list(tabu_list, new_res3->index_i, new_res3->index_j);
        if (index_tabu == -1)
        {
            // aceita, e insere na lista
            // se precisar, remove o item mais antigo da lista
            copy_solution(curr_s, new_res3->s->port);
            insert_tabu_list(tabu_list, new_res3->index_i, new_res3->index_j, iter_restricao);
        }
        else if (new_res3->s->distance < (best_s->distance))
        {
            // verifica se é melhor que a melhor encontrada com diferença em x%
            // se sim, aceita a solução
            copy_solution(curr_s, new_res3->s->port);
            remove_tabu_move(tabu_list, index_tabu);
        }
        //print_tabu_list(tabu_list);
        update_tabu_counter(tabu_list);

        if (curr_s->distance < best_s->distance)
        {
            copy_solution(best_s, curr_s->port);
            iter_no_improv = 0;
        }
        else
        {
            iter_no_improv++;
        }

        free_resultlocalsearch(new_res);
        //free_resultlocalsearch(new_res2);
        free_resultlocalsearch(new_res3);
    }
    free_solution(curr_s);
    free_tabu_list(tabu_list);
    return best_s;
}

int is_in_tabu_list(TabuList* tabu_list, int index_i, int index_j){
    node_t* ptr = tabu_list->list->head;
    for (int i = 0; i < tabu_list->list->size_list && ptr != NULL; i++) {
        if ((ptr->index_i == index_i) && (ptr->index_j == index_j)) {
            return i;
        }
        ptr = ptr->next;
    }
    return -1;
}

void free_tabu_list(TabuList* tl)
{
    free_list(tl->list);
    free(tl);
}

void insert_tabu_list(TabuList* tabu_list, int index_i, int index_j, int iter_restricao) {
    if (tabu_list->list->size_list < tabu_list->max_capacity) {
        list_push_back(tabu_list->list, index_i, index_j, iter_restricao);
    }
    else {
        list_pop_front(tabu_list->list);
        list_push_back(tabu_list->list,index_i, index_j, iter_restricao);
    }
}

void update_tabu_counter(TabuList* tabu_list)
{
    node_t* ptr = tabu_list->list->head;
    int count;
    for (int i = 0; i < tabu_list->list->size_list && ptr != NULL; i++)
    {
        count = --(ptr->count_iter);
        ptr = ptr->next;
        if (count == 0)
        {
            remove_tabu_move(tabu_list, i--);
        }
    }
}

void remove_tabu_move(TabuList* tabu_list, int index)
{
    if (index == 0)
    {
        list_pop_front(tabu_list->list);
    }
    else if (index == tabu_list->list->size_list)
    {
        list_pop_back(tabu_list->list);
    }
    else
    {
        list_erase(tabu_list->list, index);
    }
}

void print_tabu_list(TabuList* tabu_list)
{
    printf("Size TL: %d\n", tabu_list->list->size_list);
    printf("Capacity TL: %d\n", tabu_list->max_capacity);
    node_t* ptr = tabu_list->list->head;
    while (ptr != NULL)
    {
        printf("Counter: %d\t(%d,%d)", ptr->count_iter, ptr->index_i, ptr->index_j);
        printf("------\n");
        ptr = ptr->next;
    }
}