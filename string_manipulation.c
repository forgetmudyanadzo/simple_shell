#include "shell.h"

/**
 * _strlen - calculates the length of a string
 * @str: pointer to string
 * Return: length of string (excluding null terminator)
 */
int _strlen(char *str)
{
	int len = 0;

	/*itrate thrugh each character in string unti null is rched*/
	while (*(str + len) != '\0')
	{
		len++;
	}
	return (len);
}
/**
 * _strncmp - compares two strings for a specified number of characters
 * @s1: pointer to first string
 * @s2: pointer to second string
 * @n: number of characters to compare
 * Return: difference between the two strings or 0 if they are identical
 */
int _strncmp(char *s1, char *s2, int n)
{
	int j, diff;

	j = 0;
	while (j < n)
	{
		if (s1[j] == '\0' || s2[j] == '\0')
			return (-1);
		if (s1[j] != s2[j])
		{
			diff = s1[j] - s2[j];
			return (diff);
		}
		j++;
	}
	return (0);
}
/**
 * _strcpy - copies the string pointed to by src to the buffer
 * pointed to by dest
 * @dest: pointer to the destination buffer
 * @src: pointer to source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	while (*(src + j) != '\0')
	{
		*(dest + j) = *(src + j);
		j++;
	}
	*(dest + j) = '\0';
	return (dest);
}
/**
 * _strcat - appends the string pointed to by src to the end of the
 * string pointed to by dest
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: pointer to resulting string (dest)
 */
char *_strcat(char *dest, char *src)
{
	int j, dest_len;

	dest_len = _strlen(dest);
	for (j = 0 ; src[j] != '\0' ; j++)
		dest[dest_len + j] = src[j];
	dest[dest_len + j] = '\0'; /*add null term to end of res string*/
	return (dest);
}
/**
 * _strdup - duplicate a string
 * @str: pointer to the string to duplicate
 * Return: pointer to new string, or NULL if str = NULL
 */
char *_strdup(char *str)
{
	int j, length;
	char *new_string;

	if (str == NULL)
		return (NULL);
	length = _strlen(str);
	new_string = malloc(sizeof(char) * (length + 1));

	if (new_string == NULL)
		return (NULL);

	for (j = 0; j < length; j++)
		new_string[j] = str[j];
	new_string[length] = '\0';
	return (new_string);
}
