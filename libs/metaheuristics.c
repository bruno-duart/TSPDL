#include "metaheuristics.h"

TabuList *new_tabu_list(int capacity)
{
    TabuList *tabu_list = malloc(sizeof(TabuList));
    tabu_list->list = new_list();
    tabu_list->max_capacity = capacity;
    // tabu_list->tabu_moves = malloc(sizeof(Solution *));

    return tabu_list;
}

Solution *tabu_search(Solution *s0, Graph *G, int iter_restricao, int size_tabu_list, int alpha)
{
    TabuList *tabu_list = new_tabu_list(size_tabu_list);
    Solution *curr_s = new_solution();
    Solution *best_s = new_solution();
    copy_solution(curr_s, s0->port);
    copy_solution(best_s, s0->port);
    Solution *new_s,*new_s2,*new_s3;
    int index_tabu = -1, iter_no_improv = 0;
    while (iter_no_improv < 1000)
    {
        
        //new_s = swap_2opt(curr_s);
        new_s2 =  fixed_swap(curr_s);// recebe resultado da busca local - definir
        // local_search
        index_tabu = is_in_tabu_list(tabu_list, new_s2);
        if (index_tabu == -1)
        {
            // aceita, e insere na lista
            // se precisar, remove o item mais antigo da lista
            copy_solution(curr_s, new_s2->port);
            insert_tabu_list(tabu_list, curr_s, iter_restricao);
        }
        else if (new_s->distance < (best_s->distance))
        {
            // verifica se é melhor que a melhor encontrada com diferença em x%
            // se sim, aceita a solução
            copy_solution(curr_s, new_s2->port);
            remove_tabu_move(tabu_list, index_tabu);
        }

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

        //free_solution(new_s);
        free_solution(new_s2);
    }
    // free_solution(new_s);
    free_solution(curr_s);
    free_tabu_list(tabu_list);
    return best_s;
}

int is_in_tabu_list(TabuList *tabu_list, Solution *s)
{
    node_t *ptr = tabu_list->list->head;
    for (int i = 0; i < tabu_list->list->size_list && ptr != NULL; i++)
    {
        if (is_same_solution(ptr->s, s))
        {
            return i;
        }
        ptr = ptr->next;
    }
    return -1;
}

void free_tabu_move(node_t *move)
{
    free_solution(move->s);
    free(move);
}

void free_tabu_list(TabuList *tl)
{
    free_list(tl->list);
    free(tl);
}

void insert_tabu_list(TabuList *tabu_list, Solution *s, int iter_restricao)
{
    if (tabu_list->list->size_list < tabu_list->max_capacity)
    {
        list_push_back(tabu_list->list, s, iter_restricao);
    }
    else
    {
        list_pop_front(tabu_list->list);
        list_push_back(tabu_list->list, s, iter_restricao);
    }
}

void update_tabu_counter(TabuList *tabu_list)
{
    node_t *ptr = tabu_list->list->head;
    int count;
    for (int i = 0; i < tabu_list->list->size_list && ptr != NULL; i++)
    {
        count = --(ptr->count_iter);
        ptr = ptr->next;
        if (count == 0)
        {
            remove_tabu_move(tabu_list, i);
        }
    }
}

void remove_tabu_move(TabuList *tabu_list, int index)
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

void print_tabu_list(TabuList *tabu_list)
{
    printf("Size TL: %d\n", tabu_list->list->size_list);
    printf("Capacity TL: %d\n", tabu_list->max_capacity);
    node_t *ptr = tabu_list->list->head;
    while (ptr != NULL)
    {
        printf("Counter: %d\n", ptr->count_iter);
        print_solution(ptr->s);
        printf("------\n");
        ptr = ptr->next;
    }
}