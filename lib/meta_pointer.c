#include "meta_pointer.h"

TabuList* new_tabu_list(int capacity)
{
    TabuList* tabu_list = malloc(sizeof(TabuList));
    tabu_list->list = new_list();
    tabu_list->max_capacity = capacity;

    return tabu_list;
}

Solution* tabu_search(Solution* s0, Graph* G, int iter_restricao)
{
    TabuList* tabu_list = new_tabu_list(iter_restricao);
    Solution* curr_s = new_solution(), *aux;
    Solution* stored_s = new_solution();
    Solution* best_s = new_solution();
    copy_solution(curr_s, s0);
    copy_solution(best_s, s0);
    int* index = (int*) malloc(sizeof(int) * 2);
    index[0] = 0;
    index[1] = 0;
    
    int index_tabu, iter_no_improv = 0;
    while (iter_no_improv < MAX_ITER)
    {
        if ((iter_no_improv % 10 == 0) && (iter_no_improv > 0)) {
            aux = random_solution_guided();
            copy_solution(curr_s, aux);
            free_solution(aux);
        }
        lsearch_random_swap(curr_s, index, MAX_ITER/2);
        fixed_swap_pointer(curr_s, index);
        index_tabu = is_in_tabu_list(tabu_list, index[0], index[1]);
        if (index_tabu == -1)
        {
            copy_solution(stored_s, curr_s);
            insert_tabu_list(tabu_list, index[0], index[1], iter_restricao);
        }
        else if (curr_s->distance < (best_s->distance))
        {
            copy_solution(stored_s, curr_s);
            remove_tabu_move(tabu_list, index_tabu);
        }
        update_tabu_counter(tabu_list);

        if (stored_s->distance < best_s->distance)
        {
            copy_solution(best_s, stored_s);
            iter_no_improv = 0;
        }
        else
        {
            iter_no_improv++;
        }

        copy_solution(curr_s, stored_s);
    }
    free_solution(curr_s);
    free_solution(stored_s);
    free_tabu_list(tabu_list);
    free(index);
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