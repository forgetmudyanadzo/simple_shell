#include "shell.h"

/**
 * arr_size - calculates the size of an array of strings
 * @arr: the array of strings
 * Return: the size of the array, -1 if the array is NULL or empty
 */

int arr_size(char **arr)
{
	int index;

	/*if the array of the first elements is NULL, return -1*/
	if (arr == NULL || *arr == NULL)
		return (-1);

	/*loop through the array until the end is reached*/
	index = 0;
	while (arr[index])
		index++;

	/*return the size of the array*/
	return (index);
}

/**
 * array_to_list - converts an array of strings to a linked list
 * @array: the array of strings
 * Return: a pointer to the head of the linked list, or NULL on failure
 */

list_t *array_to_list(char **array)
{
	list_t *list_head = NULL; /*initialize the head pointer to NULL*/
	list_t *list_node; /*temporary node for creating new linked list nodes*/
	int index;

	/*loop through the array and add each element to the end  of the linked list*/
	for (index = 0; array[index] != NULL; index++)
	{
		/*add the list_node element to the end of the linked list*/
		list_node = add_node_end(&list_head, array[index]);

		if (list_node == NULL)
		{
			free_list(list_head);
			return (NULL);
		}
	}
	/*return a pointer to the list_head of the linked list*/
	return (list_head);
}

/**
 * list_to_array - converts a linked list of strings to an array
 * @head: a pointer to the head of the linked list
 * Return: a pointer to the array of strings, or NULL on failure
 */

char **list_to_array(list_t **head)
{
	size_t num_nodes, index;
	list_t *current_node; /*temporary pointer for traversing the list*/
	char **array;

	/*get the number of nodes in the linked list*/
	num_nodes = list_length(*head);

	/*allocate memory for the array of pointers*/
	array = malloc(sizeof(char *) * (num_nodes + 1));
	if (array == NULL)
		return (NULL);

	/*traverse the linked list and add each node's string to the array*/
	current_node = *head;
	for (index = 0; index < num_nodes; index++)
	{
		array[index] = current_node->str;
		current_node = current_node->next;
	}
	/*set the last element of the array to NULL*/
	array[index] = NULL;
	/*return the array of pointer*/
	return (array);
}

/**
 * free_array - frees the 2D array
 * @array: the array to be freed
 * Return: void
 */

void free_array(char **array)
{
	int index, count;

	/*get the size of the array*/
	count = arr_size(array);

	/*if the array is NULL, or the element is NULL, return*/
	if (*array == NULL || array == NULL)
		return;

	/*loop through the array and free each element*/
	for (index = 0; index < count; index++)
	{
		if (array[index] != NULL)
			free(array[index]);
	}
	/*free the array*/
	free(array);
}
