#ifndef HEADER_SOLUTIONS
#define HEADER_SOLUTIONS

#include "presets.h"
#include "graphs.h"
#include "arrays.h"

/// @brief

typedef struct probinstance_t {
	Graph *graph;
	int *demand;
	int *draft;
} ProblemInstance;
 
typedef struct solution_t {
    int *route;
    int distance;
    int dim;
	ProblemInstance *pinst;
} Solution;

typedef struct solutionchangetrack_t {
    Solution *s;
    int *change;
    int n;
} SolutionChangeTrack;

/// @brief Computes the fitnness (cost of route) of a port's sequence
/// @param port Sequence of ports
/// @return Cost(Distance) of route - Integer
static inline void update_fitness(Solution *s)
{
	int pA, pB = 0, distance = 0;
	int **edge = s->pinst->graph->adj;

    for (int i = 0; i < s->dim; i++)
    {
    	pA = pB;
    	pB = s->route[i];
        distance += edge[pA][pB];
    }
    s->distance = distance;
}

ProblemInstance* pinstance_init(int dim);
void free_pinstance(ProblemInstance *pinst);

/// @brief Initializes a new variable of Solution type
/// @return A reference to a Solution variable
Solution* new_solution(ProblemInstance *pinst);

/// @brief Deallocate memory of a Solution type variable
/// @param S Solution to be deallocated
void free_solution(Solution *s);

/// @brief Verifies if a port's sequence is a valid solution to the TSPDL
/// @param port Sequence of ports to be verified
/// @return True if is valid and False if not
bool solution_is_valid(Solution *s);

/// @brief Verifies if two solutions are the same
/// @param sA 
/// @param sB 
/// @return True or false
bool solution_compare(Solution* sA, Solution* sB);

/// @brief Verifies if a port is already in a route that is being constructed
/// @param port Port to be searched in route
/// @param route Route to be verified
/// @return 1 if is in route, else 0
bool solution_is_in(Solution* s, int port);

/// @brief Verifies if the arrays of Solutions has at least one solution with cost = value
/// @param Arr Array of Solutions to be verified
/// @param value Cost of solution desired
/// @return Index of solution, if found. Else, returns -1
int solution_atleast(Solution **sArr, int cost);

/// @brief Makes a copy of the route to an existing Solution variable
/// @param S Target solution
/// @param ports Route of ports to be copied
void solution_copy(Solution *sSource, Solution *sTarget);

Solution* solution_duplicate(Solution *sSource);

/// @brief Print a Solution s into the terminal
/// @param s Solution to be printed
void solution_print(Solution* s);


SolutionChangeTrack* new_changetrack(Solution *s, int n_changes);
void free_changetrack(SolutionChangeTrack *sct, bool keep_solution);
SolutionChangeTrack* changetrack_duplicate(SolutionChangeTrack *sctSource);

#endif
