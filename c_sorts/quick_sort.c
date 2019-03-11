#include "quick_sort.h"
#include <stdio.h>

// Implements the in place quicksort
void quick_sort_inner(int *arr, size_t n, int a, int b)
{
    // Initialise our temporary left and right pointers
    int l = a;
    int r = b;

    // Guard against the trivial case
    if (l >= r) { return; }

    // Find the pivot and swap this with the last value in the list
    int p = (l + r) / 2;
    int pivot = arr[p];
    arr[p] = arr[r];
    arr[r] = pivot;
    p = r;

    // Decrement the right index so we exclude the pivot from future comparisons
    r -= 1;

    // Scan and swap elements to create our sublists
    while (l <= r)
    {
        // Increment l until we find the first value for swapping
        while ((l <= r) & (arr[l] < pivot))
        {
            l += 1;
        }

        // Decrement r until we find the first value for swapping
        while ((l <= r) & (arr[r] > pivot))
        {
            r -= 1;
        }

        // Now make the swap if there is a valid swap and shrink the range
        if (l <= r)
        {
            int swap = arr[r];
            arr[r] = arr[l];
            arr[l] = swap;

            l += 1;
            r -= 1;
        }
    }

    // Finally we are done with swapping so move the pivot to the correct place
    // This should be the current location of the left index
    int swap = arr[p];
    arr[p] = arr[l];
    arr[l] = swap;

    // Now we can recurse on the sublists
    quick_sort_inner(arr, n, a, l - 1);
    quick_sort_inner(arr, n, l + 1, b);
}


int *quick_sort(int *arr, size_t n)
{
    quick_sort_inner(arr, n, 0, n - 1);
    return arr;
}


