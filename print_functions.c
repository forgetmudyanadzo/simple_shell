#include "shell.h"

/**
 * _putchar - writes a character to the standard output stream
 * @c: the charcter to be written
 * Return: On success, 1. On error, -1 is returned and errno is set
 */

int _putchar(char c)
{
	/*writes the character c to the stdout*/
	return (write(1, &c, 1));
}

/**
 * _strprint - writes a string to the standard output strem
 * @str: the string to be written
 * Return: void
 */

void _strprint(char *str)
{
	write(1, str, _strlen(str));/*writes the string to stdout*/
}

/**
 * print_array - prints an array of strings to the standard output stream
 * @array: the array of strings to be pointed
 * Return: Void
 */

void print_array(char **array)
{
	int index;

	/*checks if the array or its first element is NULL*/
	if (!array || !(*array))
	{
		/*prints an error message to stderr using perror*/
		perror(WRONG);
		return;
	}
	/*loops through the array until a NULL pointer is found*/
	for (index = 0; array[index] != NULL; ++index)
	{
		_strprint(array[index]);/*prints the current string in the array*/
		_putchar('\n');/*prints a newline character to stdout*/
	}
}

/**
 * print_list - prints each string in a linked list to the
 * standard output stream
 * @head: a pointer to the head of the linked list
 * Return: the number of the elements in the list
 */

size_t print_list(list_t *head)
{
	size_t size = 0;/*size_t is an unsigned integer type used for sizes*/

	if (head == NULL)/*checks if the list is empty*/
		return (0);

	/*loops through the list until a NULL pointer is found*/
	while (head != NULL)
	{
		_strprint(head->str);/*prints the current string in the list*/
		_putchar('\n');/*prints a newline character to stdout*/
		head = head->next;/*moves to the next node in the list*/
		size++;/*increments the size count*/
	}
	return (size);/*returns the number of elements in the list*/
}
