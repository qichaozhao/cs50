#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// This function calculates the shift (from 1 to 26) for a letter.
int shift(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (int) c - 'a';
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return (int) c - 'A';
	}
	else
	{
		return 0;
	}
}

int main(int argc, string argv[])
{
	// Input validation occcurs in the next few steps
	// Checks for only one user argument
	if (argc != 2)
	{
		printf("Usage: %s keyword\n", argv[0]);
		return 1;
	}

	// Checks for numeric-ness of the user argument
	for (int i = 0; i < strlen(argv[1]); i++)
	{
		if (isalpha(argv[1][i]) == 0)
		{
			printf("Usage: %s keyword\n", argv[0]);
			return 1;
		}
	}

	//
	// Now proceed with the rest of the program
	//
	string plaintext = "";
	do
	{
		plaintext = get_string("plaintext: ");
	}
	while (strcmp(plaintext, "") == 0);

	// Perform ROT-key and print
	// printf("argv[1]: %s\n", argv[1]);
	// printf("key: %i\n", key);
	printf("ciphertext: ");
	int letter_pos = 0;
	for (int i = 0; i < strlen(plaintext); i++)
	{
		char to_print;
		int shift_idx = letter_pos % strlen(argv[1]);
		int to_shift = shift(argv[1][shift_idx]);

		if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
		{
			to_print = 'a' + (plaintext[i] - 'a' + to_shift) % 26;
			letter_pos++;
		} 
		else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
		{
			to_print = 'A' + (plaintext[i] - 'A' + to_shift) % 26;
			letter_pos++;
		}
		else
		{
			to_print = plaintext[i];
		}

		printf("%c", to_print);
	}
	printf("\n");
}
