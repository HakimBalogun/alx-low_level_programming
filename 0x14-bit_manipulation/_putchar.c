#include "main.h"
#include <unistd.h>

/**
  * _putchar - Writes character c to stdout.
  * @c: Character to print.
  *
  * Return: 1 on Success; -1 if error, and errno is set accordingly.
  */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
