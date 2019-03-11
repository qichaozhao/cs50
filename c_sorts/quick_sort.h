// Header file for our trivial sort functions
// These work on arrays of integers
#include <stdlib.h>

int *quick_sort(int *arr, size_t arr_len);
void quick_sort_inner(int *arr, size_t n, int a, int b);
