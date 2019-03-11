#include "helpers.h"
#include <stdio.h>

// Arrange the N elements of ARRAY in random order.
//   Only effective if N is much smaller than RAND_MAX;
//   if this may not be the case, use a better random
//   number generator. 
// http://benpfaff.org/writings/clc/shuffle.html
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

bool arraycmp(int *arr1, int *arr2, size_t n)
{
  for (int i = 0; i < n; i++)
  {
    if (arr1[i] != arr2[i])
    {
      return false;
    }
  }
  return true;
}
