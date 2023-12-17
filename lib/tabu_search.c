#include "tabu_search.h"

TabuList* new_tabu_list(int restriction, int move_size)
{
    TabuList* tl = malloc(sizeof(TabuList));
    tl->list = new_plist();
    tl->restriction = restriction;
    tl->move_size = move_size;
    return tl;
}

void free_tabu_list(TabuList* tl)
{
    free_plist(tl->list, free);
    free(tl);
}

int tabu_list_find_move(TabuList* tl, int* move){
    PointerNode *node = tl->list->head;
    for (int i = 0; i < tl->list->size && node != NULL; i++) {
        if (array_compare((int*) node->p, move, tl->move_size))
            return i;
        node = node->next;
    }
    return -1;
}

void tabu_list_insert_move(TabuList* tl, int* move) {
    while (tl->list->size >= tl->restriction) {
        plist_pop_front(tl->list, free);
    }
    plist_push_back(tl->list, move, tl->restriction);
}

void tabu_list_count(TabuList* tl)
{
    PointerNode *node = tl->list->head;
    int count;
    for (int i = 0; i < tl->list->size && node != NULL; i++)
    {
        count = --(node->value);
        node = node->next;
        if (count == 0)
        {
            tabu_list_remove_move(tl, i--);
        }
    }
}

void tabu_list_remove_move(TabuList* tl, int index)
{
	plist_erase(tl->list, index, free);
}

void tabu_list_print(TabuList* tl)
{
    printf("Size TL: %d\n", tl->list->size);
    printf("Capacity TL: %d\n", tl->restriction);
    PointerNode *node = tl->list->head;
    while (node != NULL)
    {
        printf("Counter: %d\t >>> ", node->value);
        array_print((int*) node->p, tl->move_size);
        node = node->next;
    }
}

void mhsearch_tabu(SolutionChangeTrack* sctBest, TabuList *tl, int persist, int randomize_at, int max_swaps)
{
    SolutionChangeTrack* sctNext = changetrack_duplicate(sctBest);
    SolutionChangeTrack* sctCurr = changetrack_duplicate(sctBest);
    int index, count_iter = 0;
    int *move;
    
    while (count_iter < persist)
    {
        if (count_iter % randomize_at == 0) {
        	constructor_random_guided(sctCurr->s);
        }
        lsearch_random_swap(sctCurr, max_swaps);
        lsearch_fixed_swap(sctCurr);
        index = tabu_list_find_move(tl, sctCurr->change);
        if (index == -1)
        {
            // aceita, e insere na lista
            // se precisar, remove o item mais antigo da lista
            changetrack_copy(sctCurr, sctNext);
            move = array_duplicate(sctNext->change, sctNext->n);
            tabu_list_insert_move(tl, move);
        }
        else if (changetrack_update(sctNext, sctCurr))
        {
            tabu_list_remove_move(tl, index);
        }
        //print_tabu_list(tl);
        tabu_list_count(tl);

        if (changetrack_update(sctBest, sctNext))
        {
            count_iter = 0;
        }
        else
        {
            count_iter++;
        }
    	changetrack_copy(sctNext, sctCurr);
    }
    free_changetrack(sctCurr, false);
    free_changetrack(sctNext, false);
}
