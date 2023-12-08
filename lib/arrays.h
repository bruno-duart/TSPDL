#ifndef HEADER_ARRAYS
#define HEADER_ARRAYS

#include "presets.h"

/// @brief Initializes an array of integers with DIM positions 
/// @return A reference to an array of integers
int* array_init(int n);

int* array_copy(int *arr, int n);

/// @brief Prints an array of integers to the console
/// @param arr Array to be printed
void array_print(int *arr, int n);

inline void array_swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

#endif
