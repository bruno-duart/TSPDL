#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Type int

typedef struct graph_t{
    int V;
    int A;
    int **adj;
}Graph;

typedef struct _node_t{
    struct _node_t *next;
    int count_iter;
    int index_i, index_j;
}node_t;

typedef struct _list_t{
    node_t *head;
    int size_list;
}list_t;

typedef struct resultlocalsearch_t {
    int* s;
    int index_i;
    int index_j;
}ResultLocalSearch;

typedef struct tabulist_t
{
    int max_capacity;
    list_t* list;
} TabuList;


int** New_matrix(int row, int columns);

Graph* New_Graph(int V);

void insert_arc(Graph *G, Type i, Type j, Type value);

void remove_arc(Graph *G, Type i, Type j);

void Graph_print(Graph *G);

void free_Graph(Graph *G);




extern Graph *G;
extern size_t CONT_GER;
extern int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;
extern int *DEMAND, *DRAFT;

/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* ini_array();
/// @brief Prints an array of integers to the console
/// @param arr Array to be printed
void print_arr(int *arr);
/// @brief Initializes a new variable of Solution type
/// @return A reference to a Solution variable
int* new_solution();
/// @brief Deallocate memory of a Solution type variable
/// @param S Solution to be deallocated
void free_solution(int* s);
/// @brief Verifies if a port's sequence is a valid solution to the TSPDL
/// @param port Sequence of ports to be verified
/// @return True if is valid and False if not
bool is_Solution(int *port);

/// @brief Verifies if two solutions are the same
/// @param sA 
/// @param sB 
/// @return True or false
bool is_same_solution(int* sA, int* sB);

/// @brief Computes the fitnness (cost of route) of a port's sequence
/// @param port Sequence of ports
/// @return Cost(Distance) of route - Integer
int fitness(int *port);


/// @brief Verifies if a port is already in a route that is being constructed
/// @param port Port to be searched in route
/// @param route Route to be verified
/// @return 1 if is in route, else 0
int isIn(int port, int *route);
/// @brief Verifies if the arrays of Solutions has at least one solution with cost = value
/// @param Arr Array of Solutions to be verified
/// @param value Cost of solution desired
/// @return Index of solution, if found. Else, returns -1
int indexOf(int** Arr, int value);

int* random_solution();

/// @brief Build a new solution to the TSPDL using the greedy method
/// @return A new solution.
int* greedy_method();
/// @brief Build a new solution to the TSPDL. It uses a greedy_method, after choosing the first two ports randomly.
/// @return A new solution.
int* build_solution_pseudo_greedy();
/// @brief Makes a copy of the route to an existing Solution variable
/// @param S Target solution
/// @param ports Route of ports to be copied
void copy_solution(int* S_target, int *ports);

/// @brief Performs a Local-Search procedure using a random-swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* random_swap(int* s0, int index_i, int index_j, int n);
ResultLocalSearch* random_swap_first(int* s0, int n);

// /// @brief Performs a Local-Search procedure using a fixed_swap technique
// /// @param s Solution to be refined
// void fixed_swap(int* s); // adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a fixed_swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* fixed_swap(int* s0, int index_i, int index_j, int n);

// /// @brief Performs a Local-Search procedure using a 2-Opt technique
// /// @param s Solution to be refined
// void Swap_2opt(int* s); // adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a 2-Opt technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* swap_2opt(int* s0, int index_i, int index_j, int n);

/// @brief Reverse segments - part of 3-opt local-search
/// @param s Solution being analised
/// @param i 
/// @param j 
/// @param k 
/// @return Delta of distance between solutions
int reverse_segment_if_better(int* s, int i, int j, int k);

/// @brief Performs a Local-Search procedure using a 3-Opt technique
/// @param s Solution to be refined
void Swap_3opt(int* s);// adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a 3-Opt technique
/// @param s Solution to be refined
/// @return A new solution
int* swap_3opt(int* s, int n);

/// @brief Shuffle positions of Solutions in Array
/// @param Arr Array of Solutions to be shuffled
/// @param nChanges Number of changes to be made
void shuffle(int** Arr, int nChanges);

/// @brief Print a Solution s into the terminal
/// @param s Solution to be printed
void print_solution(int* s);

/// @brief Allocate memory to a new ResulLocalSearch variable
/// @return A pointer to the ResultLocalSearch variable
ResultLocalSearch* new_resultlocalsearch();

/// @brief Deallocate memory of a ResultLocalSearch variable
/// @param res ResultLocalSearch variable to be deallocated
void free_resultlocalsearch(ResultLocalSearch* res);

void print_resultlocalsearch(ResultLocalSearch* res);



/// @brief Creates a new (and empty) node. It's specific for Tabu List
/// @param index_i Index i of port changed on local search
/// @param index_j Index j of port changed on local search
/// @param T_iter Integer representing number of iterations to restrict solution
/// @return A pointer to node to be inserted into a list
node_t *new_node(int index_i, int index_j, int T_iter);
/// @brief Creates a new (and empty) list
/// @return A pointer to a list
list_t *new_list();
/// @brief Deallocate memory of a list
/// @param l List to be deallocated
void free_list(list_t *l);

/// @brief Returns a pointer to the node that is in a specific position from the list
/// @param l List to be searched in
/// @param position Position to be found
/// @return Pointer to the desired node
node_t *list_at(list_t *l, int position);

/// @brief Changes values of a node in a specific position of the list
/// @param l List to be searched in
/// @param position Position to be found
/// @param index_i Index i of port changed on local search
/// @param index_j Index j of port changed on local search
void list_set(list_t *l, int position, int index_i, int index_j);

/// @brief Returns size of the list
/// @param l List to be verified
/// @return Size of the list - integer
int list_size(list_t *l);

/// @brief Prints the list into terminal
/// @param l List to be printed
void print_list(list_t *l);

/// @brief Insert a new node to the list into a desired position
/// @param l List to have a new node inserted into
/// @param index_i Index i of port changed on local search
/// @param index_j Index j of port changed on local search
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
/// @param position Position to insert the new node into
void list_insert(list_t *l, int index_i, int index_j, int T_iter, int position);

/// @brief Insert a new node into the first position of the list
/// @param l List to have a new node inserted into
/// @param index_i Index i of port changed on local search
/// @param index_j Index j of port changed on local search
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
void list_push_front(list_t *l, int index_i, int index_j, int T_iter);

/// @brief Insert a new node into the last position of the list
/// @param l List to have a new node inserted into
/// @param index_i Index i of port changed on local search
/// @param index_j Index j of port changed on local search
/// @param T_iter Number of iterations to restrict a solution - Tabu Search
void list_push_back(list_t *l, int index_i, int index_j, int T_iter);

/// @brief Remove a node from nth position of the list
/// @param l List to have node removed from
/// @param position Position to remove the node
void list_erase(list_t *l, int position);

/// @brief Remove a node from first position of the list
/// @param l List to have node removed from
void list_pop_front(list_t *l);

/// @brief Remove a node from last position of the list
/// @param l List to have node removed from
void list_pop_back(list_t *l);



/// @brief 
/// @param capacity 
/// @return 
TabuList* new_tabu_list(int capacity);

/// @brief 
/// @param s0 
/// @param G 
/// @param iter_restricao 
/// @param size_tabu_list 
/// @param alpha 
/// @return 
int* tabu_search(int* s0, Graph* G, int iter_restricao, int size_tabu_list);

/// @brief 
/// @param tabu_list 
/// @param index_i 
/// @param index_j 
/// @return 
int is_in_tabu_list(TabuList* tabu_list, int index_i, int index_j);

/// @brief 
/// @param tl 
void free_tabu_list(TabuList* tl);

/// @brief ta
/// @param tabu_list 
/// @param index_i
/// @param index_j
/// @param iter_restricao 
void insert_tabu_list(TabuList* tabu_list, int index_i, int index_j, int iter_restricao);

/// @brief 
/// @param tabu_list 
void update_tabu_counter(TabuList* tabu_list);

/// @brief 
/// @param tabu_list 
/// @param index 
void remove_tabu_move(TabuList* tabu_list, int index);

/// @brief 
/// @param tabu_list 
void print_tabu_list(TabuList* tabu_list);
