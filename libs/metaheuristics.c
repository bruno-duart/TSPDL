#include "solution.h"
#include "metaheuristics.h"

typedef struct
{
    int counter;
    Solution *s;
} TabuMove;

typedef struct
{
    int size_tabu;
    int max_capacity;
    TabuMove **tabu_moves;
} TabuList;

TabuList *new_tabu_list(int capacity)
{
    TabuList *tabu_list = malloc(sizeof(TabuList));
    tabu_list->size_tabu = 0;
    tabu_list->max_capacity = capacity;
    tabu_list->tabu_moves = malloc(sizeof(Solution *));

    return tabu_list;
}

Solution *tabu_search(Solution *s0, Graph *G, int iter_restricao, int size_tabu_list, int alpha)
{
    TabuList *tabu_list = malloc(sizeof(TabuList) * size_tabu_list);
    Solution *new_s = new_solution();
    Solution *best_s = new_solution();
    copy_solution(new_s, s0->port);
    copy_solution(best_s, s0->port);
    Solution *curr_s;
    int index_tabu = -1;

    while (true)
    {
        // curr_s = //recebe resultado da busca local
        /* code */
        // local_search
        index_tabu = is_in_tabu_list(tabu_list, new_s);
        if (index_tabu == 0)
        {
            // aceita, e insere na lista
            // se precisar, remove o item mais antigo da lista
            copy_solution(curr_s, new_s->port);
            insert_tabu_list(tabu_list, curr_s, iter_restricao);
        }
        else if (new_s->distance < (curr_s->distance * alpha))
        {
            // verifica se é melhor que a melhor encontrada com diferença em x%
            // se sim, aceita a solução
            copy_solution(curr_s, new_s->port);
            remove_tabu_move(tabu_list, index_tabu);
        }

        update_tabu_counter(tabu_list);
        copy_solution(new_s, curr_s->port);

        if (curr_s->distance < best_s->distance)
        {
            copy_solution(best_s, new_s->port);
        }

        free_solution(curr_s);
    }

    return best_s;
}

int is_in_tabu_list(TabuList *tabu_list, Solution *s)
{
    for (int i = 0; i < tabu_list->size_tabu; i++)
    {
        for (int j = 0; j < G->V; j++)
        {
            if (tabu_list->tabu_moves[i]->s->port[j] != s->port[j])
            {
                return i;
            }
        }
    }

    return -1;
}

void free_tabu_move(TabuMove* move) {
    free_solution(move->s);
    free(move);
}

void insert_tabu_list(TabuList *tabu_list, Solution *s, int iter_restricao)
{
    if ((tabu_list->size_tabu + 1) < tabu_list->max_capacity)
    {
        tabu_list->tabu_moves = (TabuMove *)realloc(tabu_list->tabu_moves, tabu_list->size_tabu++);
        TabuMove *new_move = malloc(sizeof(TabuMove));
        new_move->s = new_solution();
        copy_solution(new_move->s, s->port);
        new_move->counter = iter_restricao;
        tabu_list->tabu_moves = new_move;
    }
    else
    {
        int index_older = 0;
        for (int i = 0; i < tabu_list->size_tabu; i++)
        {
            if (tabu_list->tabu_moves[i]->counter < tabu_list->tabu_moves[index_older]->counter)
            {
                index_older = i;
            }
        }
        tabu_list->tabu_moves[index_older]->counter = iter_restricao;
        copy_solution(tabu_list->tabu_moves[index_older]->s, s->port);
    }
}

void update_tabu_counter(TabuList *tabu_list)
{
    for (int i = 0; i < tabu_list->size_tabu; i++)
    {
        tabu_list->tabu_moves[i]->counter--;
        if (tabu_list->tabu_moves[i]->counter == 0)
        {
            remove_tabu_move(tabu_list, i);
        }
    }
}

void remove_tabu_move(TabuList *tabu_list, int index)
{
    if (index < 0 || index > tabu_list->size_tabu)
    {
        return;
    }

    for (int i = index; i < tabu_list->size_tabu - 1; i++)
    {
        tabu_list->tabu_moves[i] = tabu_list->tabu_moves[i + 1];
    }
    free_tabu_move(tabu_list->tabu_moves[tabu_list->size_tabu--]);

    if (tabu_list->size_tabu > 0)
    {
        tabu_list->tabu_moves = (TabuMove *)realloc(tabu_list->tabu_moves, tabu_list->size_tabu);
    }
    else
    {
        // free(tabu_list);
    }
}
