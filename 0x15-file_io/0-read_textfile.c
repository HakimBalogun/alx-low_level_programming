#include "main.h"
#include <stdlib.h>

/**
  * read_textfile- Read and print text files to STDOUT.
  * @filename: Text file to be read.
  * @characters: Characters to be read.
  *
  * Return: w- actual count of bytes read and printed,
  * 0 when function fails or filename is NULL.
  */
ssize_t read_textfile(const char *filename, size_t characters)
{
	char *buf;
	ssize_t fd;
	ssize_t w;
	ssize_t t;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = malloc(sizeof(char) * characters);
	t = read(fd, buf, characters);
	w = write(STDOUT_FILENO, buf, t);

	free(buf);
	close(fd);
	return (w);
}
