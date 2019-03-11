#include "merge_sort.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Implements a recursive merge sort algorithm
int *merge_sort(int *arr, size_t n)
{
    // Base Case
    if ((n == 0) | (n == 1))
    {
        return arr;
    }
    // Recursive case
    else
    {
        int pivot = n / 2;

        // Create the two sub-arrays
        int size1 = pivot;
        int size2 = n - pivot;

        int *arr1 = malloc(sizeof(int) * size1);
        int *arr2 = malloc(sizeof(int) * size2);

        // Populate the two sub-arrays
        // First the left half
        for (int i = 0; i < pivot; i++)
        {
            arr1[i] = arr[i];
        }

        // Now the right half
        for (int i = pivot; i < n; i++)
        {
            arr2[i - pivot] = arr[i];
        }

        int *ms1 = merge_sort(arr1, size1);
        int *ms2 = merge_sort(arr2, size2);

        return merge(ms1, size1, ms2, size2);
    }
}


int *merge(int *arr1, size_t n1, int *arr2, size_t n2)
{
    int *out = malloc(sizeof(int) * (n1 + n2));
    if (!out)
    {
        printf("Failed to allocate array for merge output");
        exit(1);
    }

    int i, j, idx; i = j = idx = 0;

    while ((i + j) < (n1 + n2))
    {
        if ((j == n2) | ((i < n1) & (arr1[i] < arr2[j])))
        {
            out[idx] = arr1[i];
            i += 1;
        }
        else
        {
            out[idx] = arr2[j];
            j += 1;
        }

        idx += 1;
    }

    free(arr1);
    free(arr2);
    return out;
}



