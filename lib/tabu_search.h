#ifndef HEADER_TABU_SEARCH
#define HEADER_TABU_SEARCH

#include "arrays.h"
#include "solutions.h"
#include "lists.h"
#include "local_search.h"

typedef struct tabulist_t
{
	int restriction;
    int move_size;
    PointerList* list;
} TabuList;

/// @brief 
/// @param capacity 
/// @return 
TabuList* new_tabu_list(int restriction, int move_size);

/// @brief 
/// @param tl 
void free_tabu_list(TabuList* tl);

/// @brief 
/// @param tabu_list 
/// @param index_i 
/// @param index_j 
/// @return 
int tabu_list_find_move(TabuList* tl, int* move);

/// @brief 
/// @param tabu_list 
void tabu_list_count(TabuList* tl);

/// @brief ta
/// @param tabu_list 
/// @param index_i
/// @param index_j
/// @param restriction 
void tabu_list_insert_move(TabuList* tl, int* move);

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
/// @param restriction 
/// @param size_tabu_list 
/// @param alpha 
/// @return 
void mhsearch_tabu(SolutionChangeTrack* sctBest, TabuList *tl, int persist, int randomize_at, int max_swaps);

#endif
