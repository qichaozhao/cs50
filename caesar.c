#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
	// Input validation occcurs in the next few steps
	// Checks for only one user argument
	if (argc != 2)
	{
		printf("Usage: %s key\n", argv[0]);
		return 1;
	}

	// Checks for numeric-ness of the user argument
	bool is_numeric = 1;
	for (int i = 0; i < strlen(argv[1]); i++)
	{
		if (isdigit(argv[1][i]) == 0)
		{
			is_numeric = 0;
		}
	}

	int key;
	if (is_numeric == 0)
	{
		printf("Usage: %s key\n", argv[0]);
		return 1;
	}
	else
	{
		sscanf(argv[1], "%i", &key);
	}

	// Now proceed with the rest of the program
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
	for (int i = 0; i < strlen(plaintext); i++)
	{
		char to_print;

		if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
		{
			to_print = 'a' + (plaintext[i] - 'a' + key) % 26;
		} 
		else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
		{
			to_print = 'A' + (plaintext[i] - 'A' + key) % 26;
		}
		else
		{
			to_print = plaintext[i];
		}

		printf("%c", to_print);
	}
	printf("\n");
}
