#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
	// Get user input
	float change;
	do
	{
		change = get_float("How much change is needed? ");
	}
	while (change < 0);

	int cents = round(change * 100);
	int coins = 0;
	int add_coins = 0;

	// Try dividing by each coin size in turn
	if (cents >= 25)
	{
		// Calculate the number of 25s needed
		add_coins = cents / 25;
		cents -= add_coins * 25;
		coins += add_coins;
	}

	if (cents >= 10)
	{
		add_coins = cents / 10;
		cents -= add_coins * 10;
		coins += add_coins;
	}

	if (cents >= 5)
	{
		add_coins = cents / 5;
		cents -= add_coins * 5;
		coins += add_coins;
	}

	if (cents >= 1)
	{
		cents -= 0;
		coins += cents;

	}
	
	// Print the result
	printf("%i\n", coins);
}
