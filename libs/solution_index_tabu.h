#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphs.h"

/// @brief 
typedef struct solution_t {
    int *port;
    int distance;
}Solution;

typedef struct resultlocalsearch_t {
    Solution* s;
    int index_i;
    int index_j;
}ResultLocalSearch;

extern Graph *G;
extern size_t CONT_GER;
extern int DIM, PSIZE, MAX_ITER, NUM_TESTES, OPT_VAL;
extern int *DEMAND, *DRAFT;

/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* ini_array();
/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* ini_array_dynamic(int size);
/// @brief Prints an array of integers to the console
/// @param arr Array to be printed
void print_arr(int *arr);
/// @brief Initializes a new variable of Solution type
/// @return A reference to a Solution variable
Solution* new_solution();
/// @brief Deallocate memory of a Solution type variable
/// @param S Solution to be deallocated
void free_solution(Solution *S);
/// @brief Verifies if a port's sequence is a valid solution to the TSPDL
/// @param port Sequence of ports to be verified
/// @return True if is valid and False if not
bool is_Solution(int *port);

/// @brief Verifies if two solutions are the same
/// @param sA 
/// @param sB 
/// @return True or false
bool is_same_solution(Solution* sA, Solution* sB);

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
int indexOf(Solution **Arr, int value);

Solution* random_solution();

/// @brief Build a new solution to the TSPDL using the greedy method
/// @return A new solution.
Solution* greedy_method();
/// @brief Build a new solution to the TSPDL. It uses a greedy_method, after choosing the first two ports randomly.
/// @return A new solution.
Solution* build_solution_pseudo_greedy();
/// @brief Makes a copy of the route to an existing Solution variable
/// @param S Target solution
/// @param ports Route of ports to be copied
void copy_solution(Solution *S, int *ports);

/// @brief Performs a Local-Search procedure using a random-swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* random_swap(ResultLocalSearch* s);
ResultLocalSearch* random_swap_first(Solution *s0);

// /// @brief Performs a Local-Search procedure using a fixed_swap technique
// /// @param s Solution to be refined
// void fixed_swap(Solution* s); // adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a fixed_swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* fixed_swap(ResultLocalSearch *s);

// /// @brief Performs a Local-Search procedure using a 2-Opt technique
// /// @param s Solution to be refined
// void Swap_2opt(Solution* s); // adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a 2-Opt technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
ResultLocalSearch* swap_2opt(ResultLocalSearch *s);

/// @brief Reverse segments - part of 3-opt local-search
/// @param s Solution being analised
/// @param i 
/// @param j 
/// @param k 
/// @return Delta of distance between solutions
int reverse_segment_if_better(Solution* s, int i, int j, int k);

/// @brief Performs a Local-Search procedure using a 3-Opt technique
/// @param s Solution to be refined
void Swap_3opt(Solution* s);// adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a 3-Opt technique
/// @param s Solution to be refined
/// @return A new solution
Solution* swap_3opt(Solution* s);

/// @brief Shuffle positions of Solutions in Array
/// @param Arr Array of Solutions to be shuffled
/// @param nChanges Number of changes to be made
void shuffle(Solution **Arr, int nChanges);

/// @brief Print a Solution s into the terminal
/// @param s Solution to be printed
void print_solution(Solution* s);

/// @brief Allocate memory to a new ResulLocalSearch variable
/// @return A pointer to the ResultLocalSearch variable
ResultLocalSearch* new_resultlocalsearch();

/// @brief Deallocate memory of a ResultLocalSearch variable
/// @param res ResultLocalSearch variable to be deallocated
void free_resultlocalsearch(ResultLocalSearch* res);

void print_resultlocalsearch(ResultLocalSearch* res);