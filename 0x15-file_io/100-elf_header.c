#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

/**
  * check_elf - Checks whether files are ELF files.
  * @e_ident: Pointer to an array containing the ELF magic numbers.
  *
  * Return: Void.
  * If file is not an ELF file - exit code 98.
  */
void check_elf(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
				e_ident[index] != 'E' &&
				e_ident[index] != 'L' &&
				e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
  * print_magic - Prints ELF headers' magic numbers.
  * @e_ident: Pointer to an array containing the ELF magic numbers.
  *
  * Return: Void
  * Description: Magic numbers are separated by spaces.
  */
void print_magic(unsigned char *e_ident)
{
	int index;

	printf(" Magic:\t");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("\t%02x", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
  * print_class - Prints ELF headers' class.
  * @e_ident: Pointer to an array containing the ELF class.
  *
  * Return: Void
  */
void print_class(unsigned char *e_ident)
{
	printf(" Class:\t");

	switch (e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf("\tnone\n");
			break;
		case ELFCLASS32:
			printf("\tELF32\n");
			break;
		case ELFCLASS64:
			printf("\tELF64\n");
			break;
		default:
			printf("\t<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
  * print_data - Prints ELF headers' data.
  * @e_ident: Pointer to an array containing the ELF class.
  *
  * Return: Void
  */
void print_data(unsigned char *e_ident)
{
	printf(" Data:\t");

	switch (e_ident[EI_DATA])
	{
		case ELFDATANONE:
			printf("\tnone\n");
			break;
		case ELFDATA2LSB:
			printf("\t2's complement, little endian\n");
			break;
		case ELFDATA2MSB:
			printf("\t2's complement, big endian\n");
			break;
		default:
			printf("\t<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
  * print_version - Prints ELF headers' version.
  * @e_ident: A pointer to an array containing the ELF version.
  *
  * Return: Void
  */
void print_version(unsigned char *e_ident)
{
	printf(" Version:\t%d",
			e_ident[EI_VERSION]);

	switch (e_ident[EI_VERSION])
	{
		case EV_CURRENT:
			printf(" (current)\n");
			break;
		default:
			printf("\n");
			break;
	}
}

/**
  * print_osabi - Prints ELF headers' OS/ABI.
  * @e_ident: Pointer to an array containing the ELF version.
  *
  * Return: Void
  */
void print_osabi(unsigned char *e_ident)
{
	printf(" OS/ABI:\t");

	switch (e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("\tUNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("\tUNIX - HP-UX\n");
			break;
		case ELFOSABI_NETBSD:
			printf("\tUNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("\tUNIX - Linux\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("\tUNIX - Solaris\n");
			break;
		case ELFOSABI_IRIX:
			printf("\tUNIX - IRIX\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("\tUNIX - FreeBSD\n");
			break;
		case ELFOSABI_TRU64:
			printf("\tUNIX - TRU64\n");
			break;
		case ELFOSABI_ARM:
			printf("\tARM\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("\tStandalone App\n");
			break;
		default:
			printf("\t<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
  * print_abi - Prints ELF headers' ABI version.
  * @e_ident: Pointer to an array containing the ELF ABI version.
  *
  * Return: Void
  */
void print_abi(unsigned char *e_ident)
{
	printf(" ABI Version:\t%d\n",
			e_ident[EI_ABIVERSION]);
}

/**
  * print_type - Prints ELF headers' type.
  * @e_type: The ELF type.
  * @e_ident: Pointer to an array containing the ELF class.
  *
  * Return: Void
  */
void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf(" Type:\t");

	switch (e_type)
	{
		case ET_NONE:
			printf("\tNONE (None)\n");
			break;
		case ET_REL:
			printf("\tREL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("\tEXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("\tDYN (Shared object file)\n");
			break;
		case ET_CORE:
			printf("\tCORE (Core file)\n");
			break;
		default:
			printf("\t<unknown: %x>\n", e_type);
	}
}

/**
  * print_entry - Prints ELF headers' entry point.
  * @e_entry: Address to the ELF entry point.
  * @e_ident: Pointer to an array containing the ELF class.
  *
  * Return: Void
  */
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf(" Entry point address:\t");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("\t%#x\n", (unsigned int)e_entry);

	else
		printf("\t%#lx\n", e_entry);
}

/**
  * close_elf - Closes ELF files.
  * @elf: File descriptor of the ELF file.
  *
  * Return: Void
  * Description: If the file cannot be closed - exit code 98.
  */
void close_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", elf);
		exit(98);
	}
}

/**
  * main - Displays information contained in the
  * ELF header at the start ELF files.
  * @argc: Count of arguments passed to the program.
  * @argv: Array of pointers to the arguments.
  *
  * Return: 0 on success.
  * If the file is not an ELF File or
  * the function fails - exit code 98.
  */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int o, r;

	o = open(argv[1], O_RDONLY);
	if (o == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	r = read(o, header, sizeof(Elf64_Ehdr));
	if (r == -1)
	{
		free(header);
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	check_elf(header->e_ident);
	printf("ELF Header:\n");
	print_magic(header->e_ident);
	print_class(header->e_ident);
	print_data(header->e_ident);
	print_version(header->e_ident);
	print_osabi(header->e_ident);
	print_abi(header->e_ident);
	print_type(header->e_type, header->e_ident);
	print_entry(header->e_entry, header->e_ident);

	free(header);
	close_elf(o);
	return (0);
}
