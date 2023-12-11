#include "solution.h"

typedef struct _node_t{
    struct _node_t *next;
    int count_iter;
    Solution* s;
}node_t;

typedef struct _list_t{
    node_t *head;
    int size_list;
}list_solution;

/// @brief Creates a new (and empty) node. It's specific for Tabu List
/// @param s A solution
/// @param T_iter Integer representing number of iterations to restrict solution
/// @return A pointer to node to be inserted into a list
node_t *new_node(Solution* s, int T_iter);

/// @brief Creates a new (and empty) list
/// @return A pointer to a list
list_solution *new_list();

/// @brief Deallocate memory of a list
/// @param l List to be deallocated
void free_list(list_solution *l);

/// @brief Returns a pointer to the node that is in a specific position from the list
/// @param l List to be searched in
/// @param position Position to be found
/// @return Pointer to the desired node
node_t *list_at(list_solution *l, int position);

/// @brief Changes values of a node in a specific position of the list
/// @param l List to be searched in
/// @param position Position to be found
/// @param s Solution to substitute original value
void list_set(list_solution *l, int position, Solution* s);

/// @brief Returns size of the list
/// @param l List to be verified
/// @return Size of the list - integer
int list_size(list_solution *l);

/// @brief Prints the list into terminal
/// @param l List to be printed
void print_list(list_solution *l);

/// @brief Insert a new node to the list into a desired position
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
/// @param position Position to insert the new node into
void list_insert(list_solution *l, Solution* s, int T_iter, int position);

/// @brief Insert a new node into the first position of the list
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
void list_push_front(list_solution *l, Solution* s, int T_iter);

/// @brief Insert a new node into the last position of the list
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
void list_push_back(list_solution *l, Solution* s, int T_iter);

/// @brief Remove a node from nth position of the list
/// @param l List to have node removed from
/// @param position Position to remove the node
void list_erase(list_solution *l, int position);

/// @brief Remove a node from first position of the list
/// @param l List to have node removed from
void list_pop_front(list_solution *l);

/// @brief Remove a node from last position of the list
/// @param l List to have node removed from
void list_pop_back(list_solution *l);