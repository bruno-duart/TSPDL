#include "solution.h"
#include "metaheuristics.h"

typedef struct
{
    int size_tabu;
    int max_capacity;
    Solution **tabu_moves;
} TabuList;

TabuList *new_tabu_list(int capacity)
{
    TabuList *tabu_list = malloc(sizeof(TabuList));
    tabu_list->size_tabu = 0;
    tabu_list->max_capacity = capacity;
    tabu_list->tabu_moves = malloc(sizeof(Solution *) * capacity);

    return tabu_list;
}

Solution *tabu_search(Solution *s0, Graph *G, int iter_restricao, int size_tabu_list)
{
    TabuList *tabu_list = malloc(sizeof(TabuMove) * size_tabu_list);
    Solution *new_s = new_solution();
    Solution *best_s = new_solution();
    copiar(new_s, S->port);
    copiar(best_s, S->port);
    Solution *curr_s;

    while (/* condition */)
    {
        curr_s = //recebe resultado da busca local
        /* code */
        if (curr_s->distance < best_s->distance)
        {
            copiar(best_s, new_s->port);
        }

        if (is_in_tabu_list(tabu_list, curr_s)) {
            //verifica se é melhor que a melhor encontrada com diferença em x%
            //se sim, aceita a solução
        } else {
            //aceita, e insere na lista
            //se precisar, remove o item mais antigo da lista
        }

        update_tabu_counter();
        copiar(new_s, curr_s->port);

        free_solution(curr_s);
    }

    return best_s;
}

bool is_in_tabu_list(TabuList *tabu_list, Solution *s)
{
    for (int i = 0; i < tabu_list->size_tabu; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tabu_list->tabu_moves[i]->port[j] != s->port[j])
            {
                return false;
            }
        }
    }
    
    return true;
}

void insert_tabu_list() {}

void update_tabu_counter() {}

void remove_tabu_move() {}
