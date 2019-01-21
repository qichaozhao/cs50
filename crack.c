// Author: Qichao Zhao
#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

static const char ALPHA[52] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz";
static const int PWD_LENGTH = 5;

int main(int argc, string argv[])
{
    // Get the input and do some validation
    if (argc != 2)
    {
        printf("Usage: %s hash\n", argv[0]);
        return 1;
    }

    // Now proceed to the rest of the program
    // Initialise our password buffer
    char pwd[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
    char salt[3] = {argv[1][0], argv[1][1], '\0'};
    
    // Initialise something to keep track of our indices
    int alpha_idx[PWD_LENGTH];
    for (int i = 0; i < PWD_LENGTH; i++)
    {
        alpha_idx[i] = 0;
    }

    // Perform a nested loop to brute force every combination
    while (strcmp(argv[1], crypt(pwd, salt)) != 0)
    {
        for (int i = 0; i < PWD_LENGTH; i++)
        {
            if (alpha_idx[i] == 52)
            {
                alpha_idx[i] %= 52;
                pwd[i] = ALPHA[alpha_idx[i]];
            }
            else
            {
                pwd[i] = ALPHA[alpha_idx[i]];
                alpha_idx[i]++;
                break;
            }
        }
    }

    printf("%s\n", pwd);
}
