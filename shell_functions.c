#include "shell.h"

/**
 * _getline - prints "$" and wait for user to enter command
 * and print it on the next line
 * @input: pointer to buffer to store input
 * @size: size of the buffer
 * Return: Number of characters read, or -1 if _realloc fails
 */

int _getline(char *input, int size)
{
	int index; /*index for traversing buffer*/
	int readval; /*value returned by read()*/
	struct stat sb;

	if (fstat(STDIN_FILENO, &sb) == -1)
	{

		perror("fstat");
		exit(-1);
	}

/*check if the input is coming from a pipe*/

	if ((sb.st_mode & S_IFMT) != S_IFIFO)
		_strprint(PROMPT);
	for (index = 0; index < size - 1; index++)
	{
/*Read one character*/
		readval = read(STDIN_FILENO, (input + index), 1);
		if (readval == 0)
			return (-1); /* End Of File*/
		if (input[index] == '\n')
			break;
	}

/*Terminate the string*/
	input[index] = '\0';
	return (index);
}

/**
 * exit_shell - checks if the user has enter "exit" and returns 1 if so
 * @line_tok: pointer to tokenized input
 * Return: 1 if user entered "exit", 0 otherwise
 */

int exit_shell(char **line_tok)
{
	int cmp, end_len, first_tok_len, size;

	size = arr_size(line_tok) < 3;/*Check if there are too many arguments*/
	cmp = strncmp(line_tok[0], END, _strlen(END));
/*Compare the first token to "exit"*/
	end_len = strlen(END);
	first_tok_len = _strlen(line_tok[0]);
/*Check if the first token is "exit" and there are no extra arguments*/
	if (cmp == 0 && end_len == first_tok_len && size)
		return (1);
	return (0);

}

/**
 * clear_buffer - Sets all the characters in a buffer to 0
 * @buffer: pointer to buffer to clear
 * Return: nothing
 */

void clear_buffer(char *buffer)
{
	int index;

	for (index = 0; index < BUFF_SIZE; index++)
		buffer[index] = 0;
}

/**
 * mem_cpy - copies n bytes of memory from src to dest
 * @dest: pointer to destination memory
 * @src: pointer to source memory
 * @n: number of bytes to copy
 * Return: Pointer to dest
 */

char *mem_cpy(char *dest, char *src, int n)
{
	int index;

	for (index = 0; index < n - 1; index++)
	{
		*(dest + index) = *(src + index);
	}
	*(dest + index) = '\0';
	return (dest);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the old memory
 * @old_size: size for old memory block
 * @new_size: size of the new memory location
 * Return: returns pointer to a new memory location
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_array, *helper;
	unsigned int index;

	if (old_size == new_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new_array = malloc(new_size);
		if (new_array == NULL)
			return (NULL);
		return (new_array);
	}
	new_array = malloc(sizeof(char) * new_size);
	if (new_array == NULL)
		return (NULL);
	if (new_size > old_size && old_size != 0)
	{
		helper = ptr;
		for (index = 0; index < old_size; index++)
			new_array[index] = helper[index];
		free(ptr);
	}
	if (new_size < old_size)
	{
		helper = ptr;
		for (index = 0; index < new_size; index++)
			new_array[index] = helper[index];
		free(ptr);
	}
	return (new_array);
}
