#ifndef HEADER_TABU_SEARCH
#define HEADER_TABU_SEARCH

#include "arrays.h"
#include "solutions.h"
#include "lists.h"

typedef struct tabulist_t
{
    int max_capacity;
    PointerList* list;
} TabuList;

/// @brief 
/// @param capacity 
/// @return 
TabuList* new_tabu_list(int capacity);

/// @brief 
/// @param tl 
void free_tabu_list(TabuList* tl);

/// @brief 
/// @param tabu_list 
/// @param index_i 
/// @param index_j 
/// @return 
int tabu_list_is_in(TabuList* tl, int index_i, int index_j);

/// @brief 
/// @param tabu_list 
void tabu_list_count(TabuList* tl);

/// @brief ta
/// @param tabu_list 
/// @param index_i
/// @param index_j
/// @param iter_restricao 
void tabu_list_insert_move(TabuList* tl, int index_i, int index_j, int iter_restricao);

/// @brief 
/// @param tabu_list 
/// @param index 
void tabu_list_remove_move(TabuList* tl, int index);

/// @brief 
/// @param tabu_list 
void tabu_list_print(TabuList* tl);

/// @brief 
/// @param s0 
/// @param G 
/// @param iter_restricao 
/// @param size_tabu_list 
/// @param alpha 
/// @return 
Solution* tabu_search(Solution* s0, Graph* G, int iter_restricao, int size_tabu_list, int alpha);

#endif
