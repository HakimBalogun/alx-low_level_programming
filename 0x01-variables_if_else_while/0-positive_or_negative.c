# include <stdlib.h>
# include <stdio.h>
# include <time.h>

/*
 * main - Determines if a number is positive, negative or zero.
 *
 * Return - Always 0 (Success)
 */

int main(void)
{
	int n;

	srand(time(0));
	n = rand() - RAND_MAX / 2;
	if (n > 0)
	{
		printf("%d is positive.\n", n);
	}
	else if (n == 0)
	{
		print("%d is zero.\n", n);
	}
	else
	{
		printf("%d i negative.\n", n);
	}
	return (0);
}
