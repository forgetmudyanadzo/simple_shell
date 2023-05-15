#include "shell.h"

/**
 * list_length - returns the number of nodes in a linked list
 * @head: pointer to the first node in the list
 * Return: number of nodes in the list
 */

size_t list_length(list_t *head)
{
	size_t length = 0;

/*traverse the list and count the number of nodes*/
	while (head != NULL)
	{
		length++;
		head = head->next;
	}
	return (length);
}

/**
 * add_node - adds a new at the beginning of a linked list
 * @head: pointer to the firstnode in the list
 * @str: the string to be added to the new node
 * Return: pointer to new node, or NULL if it failed
 */

list_t *add_node(list_t **head, char *str)
{
	list_t *new_node;

/*allocate memory for the new node*/
	new_node = malloc(sizeof(list_t));

	if (new_node == NULL)
		return (NULL);

/*copy the string and set the length*/
	new_node->str = _strdup(str);

	if (new_node->str == NULL)
		return (NULL);
	new_node->len = _strlen(str);

/*set the next pointer to the current head and update the head*/
	new_node->next = *head;
	*head = new_node;

	return (*head);
}

/**
 * add_node_end - adds a new node at the end of a linked list
 * @head: a pointer to first node in the list
 * @str: data the string to be added to the node
 * Return: a pointer to the new node, or NULL if it failed
 */

list_t *add_node_end(list_t **head, char *str)
{
	list_t *new_node, *tall;

/*allocate memory for the new node*/
	new_node = malloc(sizeof(list_t));

	if (new_node == NULL)
		return (NULL);

/*copy the string and set the length*/
	new_node->str = strdup(str);
	if (new_node->str == NULL)
		return (NULL);
	new_node->len = _strlen(str);
	new_node->next = NULL;

/*if the list is empty, set the head to the new node*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	tall = *head;
	while (1)
	{
		if (tall->next == NULL)
		{
			tall->next = new_node;
			break;
		}
		tall = tall->next;
	}
	return (new_node);
}

/**
 * free_list - frees a linked list
 * @head: a pointer to the first node in the list
 * Return: none
 */

void free_list(list_t *head)
{
	list_t *tmp;

/*traverse the list and free the memory allocated for each node*/
	while (1)
	{
		if (head == NULL)
			break;
		tmp = head;
		head = tmp->next;
		free(tmp->str);
		free(tmp);
	}
}

/**
 * get_node - returns the node with a given string
 * @head: a pointer to the head of the linked list
 * @str: the the string to search for in the node
 * Return: the node that contains the given string, or NULL if not found
 */

list_t *get_node(list_t **head, char *str)
{
	list_t *current_node;

/*traverse the list and search for the string*/
	current_node = *head;
	while (head && current_node)
	{
		if (_strcmp(current_node->str, str) == 0 && current_node)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}
