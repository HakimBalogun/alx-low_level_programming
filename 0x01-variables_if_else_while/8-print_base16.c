# include <stdio.h>

/**
 * main - Prints all base 16 numbers in lowercase.
 *
 * Return: Always 0. (Success)
 */
int main(void)
{
	char c;
	int d;

	c = 'a';
	d = 0;
	while
		(d < 10)
		{
			putchar(d + '0');
			d++;
		}
	while
		(c <= 'f')
		{
			putchar(c);
			c++;
		}
	putchar('\n');
	return (0);
}
