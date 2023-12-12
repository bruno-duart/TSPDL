#ifndef HEADER_ARRAYS
#define HEADER_ARRAYS

#include "presets.h"

/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* array_init(int n);

/// @brief Prints an array of integers to the console
/// @param arr Array to be printed
void array_print(int *arr, int n);

static inline void array_swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

static inline void array_copy(int *arrSource, int *arrTarget, int n)
{
    while(n--)
        arrTarget[n] = arrSource[n];
}

static inline int* array_duplicate(int *arrSource, int n)
{
	int *arrTarget = malloc(sizeof(int) * n);
	array_copy(arrSource, arrTarget, n);
    return arrTarget;
}

#endif
