#include "shell.h"

/**
 * count_words - counts the number of words in a string
 * separated by a delimiter
 * @str: string to count words from
 * @delim: delimiter used to separate words
 * Return: number of words in the string
 */
int count_words(char *str, char delim)
{
	int pos, num_words;

	pos = 0;
	num_words = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] != delim && (str[pos + 1] == delim || str[pos + 1] ==
					'\t' || str[pos + 1] == '\0'))
			num_words++;
		pos++;
	}
	return (num_words);
}
/**
 * _wrdlen - returns the lenght of a word in a string
 * @s: pointer to a string
 * @delim: delimiter used to separate words
 * Return: length of the word
 */
int _wrdlen(char *s, char delim)
{
	int len = 0;

	while (*(s + len) != delim && *(s + len) != '\0' && *(s + len) != '\t')
		len++;
	return (len);
}
/**
 * strtow - splits a string into an array of words based on a delimiter
 * @str: pointer to the string to be split
 * @delim: delimiter used to separate words
 * Return: pointer to the array of words
 */
char **strtow(char *str, char delim)
{
	int idx, m, n, s, total_words, word_size;
	char **output;

	if (str == NULL || str[0] == '\0') /* Check if string is NULL or empty*/
		return (NULL);
	total_words = count_words(str, delim);
	if (total_words == 0) /* If there are no words return NULL*/
	return (NULL);
	output = malloc(sizeof(char *) * (total_words + 1));
	if (output == NULL)
		return (NULL);
	idx = 0;
	m = 0;
	while (str[idx] != '\0')
	{
		while ((str[idx] == delim || str[idx] == '\t') && str[idx] != '\0')
			idx++;
		if (str[idx] == '\0')
		{
			output[m] = NULL;
			return (output);
		}
		output[m] = malloc(sizeof(char) * (_wrdlen(str + idx, delim) + 1));
		if (output[m] == NULL)
		{
			for (n = m - 1; n >= 0; n--)
				free(output[n]);
			free(output);
			return (NULL);
		}
		word_size = _wrdlen(str + idx, delim);
		for (s = 0; s < word_size && str[idx] != '\0'; s++, idx++)
			output[m][s] = str[idx];
		output[m][s] = '\0';
		m++;
	}
	output[m] = NULL;
	return (output);
}
