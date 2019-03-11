#include <stdlib.h>
#include <stdio.h>

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

int main(void)
{
    int arr[10];

    for (int i = 0; i > -10; i--)
    {
        printf("%i ", i);
        arr[abs(i)] = i;
    }
    printf("\n");

    for (int i = 0; i > -10; i--)
    {
        printf("%i ", abs(i));
    }
    printf("\n");

    shuffle(arr, 10);

    for (int i = 0; i > -10; i--)
    {
        printf("%i ", arr[abs(i)]);
    }
    printf("\n");

}
