#include <stdio.h>
#include <math.h>
#include <cs50.h>

void populateDigitArray(int *digitArray, long digits, int card_len);

int main(void)
{
	// Let's get the input
	long card;
	int card_len;
	do
	{
		card = get_long("Number: ");
	}
	while (card < 0);

	// First perform a length check
	card_len = log10(card) + 1;
	if (card_len != 13 && card_len != 15 && card_len != 16)
	{
		printf("INVALID\n");
		return 0;
	}

	// If the card passes the length check, perform LUHN's ALGORTHIM
	int digitArray[card_len];
	populateDigitArray(digitArray, card, card_len);
	int digitSum = 0;

	// Loop through all the digits starting from the 2nd from last
	for (int i = 1; i < card_len; i += 2)
	{
		// Get the digit from the array and multiply by 2
		int digitProduct = digitArray[i] * 2;

		// Now make sure we just add the digits if the product is over 10
		// printf("%i: %i + %i\n", digitProduct, digitProduct / 10, digitProduct % 10);
		digitSum += (digitProduct / 10 + digitProduct % 10);
	}

	// printf("interim digitSum: %i\n", digitSum);

	// Loop through the non-product digits
	for (int i = 0; i < card_len; i += 2)
	{
		digitSum += digitArray[i];
	}

	// printf("final digitSum: %i\n", digitSum);

	// Check whether the last digit is a zero or not
	if (digitSum % 10 != 0)
	{
		printf("INVALID\n");
		return 0;
	}

	// Check for VISA, MASTERCARD, AMEX
	if (digitArray[card_len - 1] == 4)
	{
		printf("VISA\n");
	}
	else if (digitArray[card_len - 1] == 3 && (digitArray[card_len - 2] == 4 || digitArray[card_len - 2] == 7))
	{
		printf("AMEX\n");
	}
	else if (digitArray[card_len - 1] == 5 && (digitArray[card_len - 2] >= 1 && digitArray[card_len - 2] <= 5))
	{
		printf("MASTERCARD\n");
	}
	else
	{
		printf("INVALID\n");
	}

	return 0;
}

void populateDigitArray(int *digitArray, long digits, int card_len)
// Note the digits array becomes flipped (i.e. the last digit of the number becomes the 0th element of the array)
{
	int idx = 0;
	while (digits != 0)
	{
		digitArray[idx] = digits % 10;
		digits /= 10;
		idx++;
	}

	// 	Debug the array by printing it
	// printf("digitArray:\n");
	// for (int i = 0; i < card_len; i++)
	// {
	// 	printf("%i", digitArray[i]);
	// }
	//    printf("\n");
}

