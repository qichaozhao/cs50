#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // Test referencing array of arrays
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

    int size = sizeof(INPUTS[1][0]) / sizeof(int);
    int size2 = sizeof(TC2) / sizeof(int);
    printf("Size: %i\n", size);
    printf("Size2: %i\n", size2);
    printf("First element: %i\n", INPUTS[1][0]);

}
