#ifndef HEADER_LOCAL_SEARCH
#define HEADER_LOCAL_SEARCH

#include "solutions.h"

void lsearch_random(Solution *s);

/// @brief Build a new solution to the TSPDL using the greedy method
/// @return A new solution.
void lsearch_greedy(Solution *s);
/// @brief Build a new solution to the TSPDL. It uses a greedy_method, after choosing the first two ports randomly.
/// @return A new solution.

bool lsearch_try_swap(Solution *s, int i, int j);
bool lsearch_chose_better(SolutionChangeTrack *sctCurr, Solution *sCandidate, int *index);

void lsearch_pseudo_greedy(Solution *s);

/// @brief Performs a Local-Search procedure using a random-swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
void lsearch_random_swap(SolutionChangeTrack *sctCurr, int max_swaps)

// /// @brief Performs a Local-Search procedure using a fixed_swap technique
// /// @param s Solution to be refined
// void fixed_swap(Solution* s); // adaptar para retornar uma nova solução 

/// @brief Performs a Local-Search procedure using a fixed_swap technique
/// @param s Solution to be refined
/// @return A new solution and the indexes of the interval of changed ports
void lsearch_fixed_swap(SolutionChangeTrack *sctCurr)

#endif
