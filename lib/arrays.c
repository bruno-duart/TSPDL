#include "arrays.h"

int *array_init(int n)
{
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    return arr;
}

int* array_copy(int *arr, int n)
{
	int *new_arr = malloc(sizeof(int) * n);
    while(n--)
        new_arr[n] = arr[n];
    return new_arr;
}

void array_print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]); // erro com valor não inicializado, por conta do 'i'
    printf("\n");
}

