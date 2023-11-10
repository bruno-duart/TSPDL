#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphs.h"
#include "globals.h"

/// @brief 
typedef struct {
    int *port;
    int distance;
}Solution;

/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* ini_array();

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

/// @brief 
/// @return 
Solution* build_solution();
Solution* random_swap(Solution* individuo);
void fixed_swap(Solution* s);
void Swap_2opt(Solution* s);
int reverse_segment_if_better(Solution* s, int i, int j, int k);
void Swap_3opt(Solution* s);
void local_search_Allpopulation(Solution** S);

/// @brief Shuffle positions of Solutions in Array
/// @param Arr Array of Solutions to be shuffled
/// @param nChanges Number of changes to be made
void shuffle(Solution **Arr, int nChanges);