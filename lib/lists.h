#ifndef HEADER_LISTS
#define HEADER_LISTS

#include "presets.h"
#include "solutions.h"

typedef void (*ptr_handler_t)(void*);

typedef struct node_t{
    struct node_t *next;
    int value;
    void* p;
} PointerNode;

typedef struct _list_t{
    PointerNode *head;
    int size_list;
} PointerList;

/// @brief Creates a new (and empty) node. It's specific for Tabu List
/// @param s A solution
/// @param value Integer representing number of iterations to restrict solution
/// @return A pointer to node to be inserted into a list
PointerNode *new_pnode(void *p, int value);
PointerNode *new_snode(Solution *s, int value);
PointerNode *new_2inode(int i, int j, int value);
void free_pnode(PointerNode *node, ptr_handler_t free_content);

/// @brief Creates a new (and empty) list
/// @return A pointer to a list
PointerList *new_plist();

/// @brief Deallocate memory of a list
/// @param l List to be deallocated
void free_plist(PointerList *l, ptr_handler_t free_content);

/// @brief Returns a pointer to the node that is in a specific position from the list
/// @param l List to be searched in
/// @param position Position to be found
/// @return Pointer to the desired node
PointerNode *plist_at(PointerList *l, int position);

/// @brief Changes values of a node in a specific position of the list
/// @param l List to be searched in
/// @param position Position to be found
/// @param s Solution to substitute original value
void plist_set(PointerList *l, int position, void *p);

/// @brief Returns size of the list
/// @param l List to be verified
/// @return Size of the list - integer
int plist_size(PointerList *l);

/// @brief Prints the list into terminal
/// @param l List to be printed
void plist_print(PointerList *l, ptr_handler_t print_content);

/// @brief Insert a new node to the list into a desired position
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param value Number of iterations to restrict a solution - Tabu Search
/// @param position Position to insert the new node into
void plist_insert(PointerList *l, void *p, int value, int position);

/// @brief Insert a new node into the first position of the list
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param value Number of iterations to restrict a solution - Tabu Search
void plist_push_front(PointerList *l, void *p, int value);

/// @brief Insert a new node into the last position of the list
/// @param l List to have a new node inserted into
/// @param s Solution to be inserted into the new node
/// @param value Number of iterations to restrict a solution - Tabu Search
void plist_push_back(PointerList *l, void *p, int value);

/// @brief Remove a node from nth position of the list
/// @param l List to have node removed from
/// @param position Position to remove the node
void plist_erase(PointerList *l, int position, ptr_handler_t free_content);

/// @brief Remove a node from first position of the list
/// @param l List to have node removed from
void plist_pop_front(PointerList *l, ptr_handler_t free_content);

/// @brief Remove a node from last position of the list
/// @param l List to have node removed from
void plist_pop_back(PointerList *l, ptr_handler_t free_content);

#endif
