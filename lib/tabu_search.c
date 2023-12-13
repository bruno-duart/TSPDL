#include "tabu_search.h"

TabuList* new_tabu_list(int capacity)
{
    TabuList* tl = malloc(sizeof(TabuList));
    tl->list = new_plist();
    tl->max_capacity = capacity;
    return tl;
}

int tabu_list_is_in(TabuList* tl, int index_i, int index_j){
    node_t* ptr = tl->list->head;
    for (int i = 0; i < tl->list->size && ptr != NULL; i++) {
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

void insert_tabu_list(TabuList* tl, int index_i, int index_j, int iter_restricao) {
    if (tl->list->size < tl->max_capacity) {
        list_push_back(tl->list, index_i, index_j, iter_restricao);
    }
    else {
        list_pop_front(tl->list);
        list_push_back(tl->list,index_i, index_j, iter_restricao);
    }
}

void update_tabu_counter(TabuList* tl)
{
    node_t* ptr = tl->list->head;
    int count;
    for (int i = 0; i < tl->list->size && ptr != NULL; i++)
    {
        count = --(ptr->count_iter);
        ptr = ptr->next;
        if (count == 0)
        {
            remove_tabu_move(tl, i--);
        }
    }
}

void remove_tabu_move(TabuList* tl, int index)
{
    if (index == 0)
    {
        list_pop_front(tl->list);
    }
    else if (index == tl->list->size)
    {
        list_pop_back(tl->list);
    }
    else
    {
        list_erase(tl->list, index);
    }
}

void print_tabu_list(TabuList* tl)
{
    printf("Size TL: %d\n", tl->list->size);
    printf("Capacity TL: %d\n", tl->max_capacity);
    node_t* ptr = tl->list->head;
    while (ptr != NULL)
    {
        printf("Counter: %d\t(%d,%d)", ptr->count_iter, ptr->index_i, ptr->index_j);
        printf("------\n");
        ptr = ptr->next;
    }
}

Solution* tabu_search(Solution* s0, Graph* G, int iter_restricao, int size_tabu_list, int alpha)
{
    TabuList* tl = new_tabu_list(size_tabu_list);
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
        //print_tabu_list(tl);
        //print_resultlocalsearch(new_res);
        // local_search
        index_tabu = is_in_tabu_list(tl, new_res3->index_i, new_res3->index_j);
        if (index_tabu == -1)
        {
            // aceita, e insere na lista
            // se precisar, remove o item mais antigo da lista
            copy_solution(curr_s, new_res3->s->port);
            insert_tabu_list(tl, new_res3->index_i, new_res3->index_j, iter_restricao);
        }
        else if (new_res3->s->distance < (best_s->distance))
        {
            // verifica se é melhor que a melhor encontrada com diferença em x%
            // se sim, aceita a solução
            copy_solution(curr_s, new_res3->s->port);
            remove_tabu_move(tl, index_tabu);
        }
        //print_tabu_list(tl);
        update_tabu_counter(tl);

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
    free_tabu_list(tl);
    return best_s;
}
