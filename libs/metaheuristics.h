#include "lists.h"

// typedef struct
// {
//     int counter;
//     Solution *s;
// } TabuMove;

typedef struct
{
    int max_capacity;
    list_t* list;
} TabuList;

/// @brief 
/// @param capacity 
/// @return 
TabuList *new_tabu_list(int capacity);
/// @brief 
/// @param s0 
/// @param G 
/// @param iter_restricao 
/// @param size_tabu_list 
/// @param alpha 
/// @return 
Solution *tabu_search(Solution *s0, Graph *G, int iter_restricao, int size_tabu_list, int alpha);
/// @brief 
/// @param tabu_list 
/// @param s 
/// @return 
int is_in_tabu_list(TabuList *tabu_list, Solution *s);
/// @brief 
/// @param move 
void free_tabu_move(node_t* move);
/// @brief 
/// @param tl 
void free_tabu_list(TabuList* tl);
/// @brief 
/// @param tabu_list 
/// @param s 
/// @param iter_restricao 
void insert_tabu_list(TabuList *tabu_list, Solution *s, int iter_restricao);
/// @brief 
/// @param tabu_list 
void update_tabu_counter(TabuList *tabu_list);
/// @brief 
/// @param tabu_list 
/// @param index 
void remove_tabu_move(TabuList *tabu_list, int index);
/// @brief 
/// @param tabu_list 
void print_tabu_list(TabuList *tabu_list);