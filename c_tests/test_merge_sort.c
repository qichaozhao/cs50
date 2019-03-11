#include "../c_sorts/merge_sort.h"
#include "helpers.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Define function prototypes
void test_merge_sort(void);
void test_init(void);
int *array_copy(int *src, size_t size);

// Declare global vars
int TC1[1] = {0};
int TC2[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int TC3[101];
int TC4[101];
int TC5[152];

int TC1O[1] = {0};
int TC2O[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int TC3O[101];
int TC4O[101];
int TC5O[152];

int *INPUTS[5] = {TC1, TC2, TC3, TC4, TC5};
int *OUTPUTS[5] = {TC1O, TC2O, TC3O, TC4O, TC5O};
int sizes[5] = {1, 11, 101, 101, 152};

// Run all tests
int main(void)
{
    test_init();
    test_merge_sort();
}


// Generate the arrays for TC3, TC4, TC5
void test_init(void)
{
    // TC3
    for (int i = 0; i < 101; i++)
    {
        TC3[i] = i;
        TC3O[i] = i;
    }
    shuffle(TC3, 101);

    // TC4
    for (int i = 0; i > -101; i--)
    {
        TC4[abs(i)] = i;
        TC4O[abs(i)] = -100 + abs(i);
    }
    shuffle(TC4, 101);

    // TC5
    for (int i = 0; i < 152; i++)
    {
        TC5[i] = i;
        TC5O[i] = i;
    }
    shuffle(TC5, 152);

}

void test_merge_sort(void)
{
    for (int i = 0; i < 5; i++)
    {   
        int *out = merge_sort(array_copy(INPUTS[i], sizes[i]), sizes[i]);
        assert(arraycmp(out, OUTPUTS[i], sizes[i]));
        free(out);
    }
}

int *array_copy(int *src, size_t size)
{
    int *dst = malloc(sizeof(int) * size);
    if (!dst)
    {
        printf("Unable to allocate array for copying...");
        exit(1);
    }
    return memcpy(dst, src, sizeof(int) * size);
}
