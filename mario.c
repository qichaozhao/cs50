#include <cs50.h>
#include <stdio.h>

void pyramid_left(int height, int row);
void pyramid_right(int height, int row);

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int r = 1; r <= h; r++)
    {
        // Print left part
        pyramid_left(h, r);
        
        // Print two spaces
        printf("  ");

        // Print right part
        pyramid_right(h, r);
        
        // Print newline
        printf("\n");
    }
}

void pyramid_left(int height, int row)
{
    // Print spaces
    for (int r = 1; r <= (height - row); r++)
    {
        printf(" ");
    }
    
    // Print blocks
    for (int r = 1; r <= row; r++)
    {
        printf("#");
    }
}

void pyramid_right(int height, int row)
{
    // Print blocks
    for (int r = 1; r <= row; r++)
    {
        printf("#");
    }
}
