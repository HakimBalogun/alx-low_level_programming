#include "main.h"
/**
 * _isalpha - Checks for alphabetic characters
 * @c: Character to be checked
 *
 * Return: 1 if character is an alphabet, otherwise 0.
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
