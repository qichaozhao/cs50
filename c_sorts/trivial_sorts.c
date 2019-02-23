#include "trivial_sorts.h"
#include <limits.h>
#include <stdbool.h>

// Implements the insertion sort algorithm
// 1. Consider each element in the array
// 2. If element k is smaller than element k-1, move it backwards until no longer true
int *insertion_sort(int *arr, size_t arr_len)
{
    for (int i = 0; i < arr_len; i++)
    {
        int cur_value = arr[i];
        int insert_idx = i - 1;

        while((insert_idx >= 0) && (arr[insert_idx] > cur_value))
        {
            arr[insert_idx + 1] = arr[insert_idx];
            arr[insert_idx] = cur_value;
            insert_idx -= 1;
        }

    }

    return arr;
}

// Implements the selection sort algorithm
// 1. Consider each element in the array of length n
// 2. Find the minimum value between index k and n and swap the current value with the value at index k
int *selection_sort(int *arr, size_t arr_len)
{
    for (int i = 0; i < arr_len; i++)
    {
        int mv = INT_MAX;
        int mv_idx = 0;

        for (int j = i; j < arr_len; j++)
        {
            if (arr[j] < mv)
            {
                mv = arr[j];
                mv_idx = j;
            }
        }

        // Swap values
        int tmp = arr[i];
        arr[i] = arr[mv_idx];
        arr[mv_idx] = tmp;
    }

    return arr;
}

// Implements the bubble sort algorithm
// 1. Consider a bubble of two elements (k, k+1)
// 2. If k > k + 1, swap the two elements
// 3. If a pass happens with no swaps, then consider the list sorted
int *bubble_sort(int *arr, size_t arr_len)
{
    bool swap = true;
    while (swap)
    {
        swap = false;

        for (int i = 0, n = arr_len - 1; i < n; i++)
        {

            if (arr[i] > arr[i + 1])
            {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swap = true;
            }
        }
    }

    return arr;
}

