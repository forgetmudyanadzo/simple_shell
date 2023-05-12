#include "shell.h"

/**
 * _strcmp - compares two strings and returns the difference in value
 * of the first character that's different between them
 * @str1: pointer to the first string to compare
 * @str2: pointer to the second string to compare
 * Return: the difference in value of the first character that's different
 *	between the two string, or 0 if they are the same
 */

int _strcmp(char *str1, char *str2)
{
	int j, difference;

	j = 0;

	/*check the character until the end of one of the strings is reached*/
	while (str1[j] != '\0' || str2[j] != '\0')
	{
		if (str1[j] != str2[j]) /*if a difference is found*/
		{
			/*calculate the different in the value between two strings*/
			difference = str1[j] - str2[j];
			return (difference); /*return the difference*/
		}
		j++; /*move to the next character*/
	}
	/*if the strings are identical*/
	if (str1[j] == str2[j] && str1[j] == '\0')
	{
		difference = 0; /*the diffrence is 0*/
	}
	return (difference); /*return the difference*/
}

/**
 * _strchr - searches a string for a specific character and returns a
 * pointer to the first occurence of that character
 * @str: pointer to the string to search
 * @c: the character to search for
 * Return: pointer to the first occurence of the character in the string,
 *	or NULL if the character is not found
*/

char *_strchr(char *str, char c)
{
	int j;

	/*check each character until the end of the string is reached*/
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] == c) /*if the character is found*/
		{
			return ((char *)(str + j)); /*return a pointer to the character*/
		}
	}
	/*the character was not found, so return NULL*/
	return (NULL);
}

/**
 * len_to_char - calculates the length of a string up to a given charcter
 * @str: pointer to string to calculate the length of
 * @c: the character to calculate the length up to
 * Return: the length of the string up to the character, or 0 if the
 *	character is not found
 */

int len_to_char(char *str, char c)
{
	int j = 0;

	/*check each character until the end the string or the character is reached*/
	while (str[j] != c && str[j] != '\0')
	{
		j++; /*increament the counter for each character*/
	}
	/*if the chracter was not found in the string*/
	if (str[j] == '\0')
	{
		return (0);
	}
	/*return the length of the string up to the first occurence of the character*/
	return (j);
}

/**
 * _atoi - converts string to an integer
 * @str: pointer to the string to convert
 * Return: the integer value of the string, or -1 on error
 */

int _atoi(char *str)
{
	int count, num, exponent, j;

	/*calculates the size of the string*/
	count = _strlen(str);

	/*calculates the exponent of 10 for the leftmost digit*/
	exponent = 1;

	for (j = 1; j < count; j++)
		exponent *= 10;

	num = 0;
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			/*convert the character to a digit and multiply it by the exponent*/
			num += (str[j] - '0') * exponent;
		}
		else
		{
			/*print an error message if the input is not a valid integr*/
			perror("wrong input for exit status\n");
			return (-1);
		}
		/*update the exponent for the nest digit*/
		exponent /= 10;
	}
	return (num);
}
