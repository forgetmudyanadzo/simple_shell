#include "shell.h"

/**
 * _getenv - searches for an environment variable in a linked list
 * @name: the name of the environment variable to get
 * @env_list: pointer to the head of the environment list
 * Return: a pointer to a string containing the value of the environment
 *	variable or NULL if the variable is not found in the list
 */

char *_getenv(char *name, list_t **env_list)
{
	list_t *env_ptr;
	int word_length, index;

	/*get the length of the environment list*/
	env_ptr = *env_list;
	word_length = list_length(env_ptr);

	/*check for the NULL pointers and empty list*/
	if (!env_list || !env_ptr || !name)
		return (NULL);

	/*iterate through the list and search for the given name*/
	index = 0;
	while (index < word_length)
	{
		if (_strncmp(env_ptr->str, name, _strlen(name)) == 0)
			return (env_ptr->str); /*found the variable, return its value*/
		index++;
		env_ptr = env_ptr->next;
	}
	return (NULL); /*name not found in the environment list*/
}

/**
 * _setenv - changes or adds the value of an environment variable
 * @name: the name of the environment variaable to set
 * @value: the new value to be assigned to the environment variable
 * @env_list: pointer to the head of the environment list
 * Return: 0 on success, or 1 on error
 */

int _setenv(char *name, char *value, list_t **env_list)
{
	char *new_str, *env_var;
	list_t *ret_node;

	/*create a new string with the variable and value*/
	env_var = var_str(name, value);
	if (env_var == NULL)
	{
		perror(ENOMEM);
		return (1);
	}

	/*search for the variable in yhe environment list*/
	new_str = _getenv(name, env_list);
	/*if variable not found, add it to the end of the list*/
	if (new_str == NULL)
	{
		ret_node = add_node_end(env_list, env_var);
		if (ret_node == NULL)
		{
			free(env_var);
			perror(ENOMEM);
			return (1);
		}
		/*free the new string and return success*/
		free(env_var);
		return (0);
	}
	/*if variable found, replace its value*/
	ret_node = get_node(env_list, new_str);
	free(ret_node->str);
	ret_node->str = env_var;
	return (0);
}

/**
 * _unsetenv - deletes an environment variable from the linked list
 * @name: name name of the environment variable to be deleted
 * @env_list: pointer to the head of the environment list
 * Return: 0 on success, or 1 on error
 */

int _unsetenv(char *name, list_t **env_list)
{
	char *equal, *env_var;
	int deleted;
	list_t *ptr;

	ptr = *env_list;
	equal = _strchr(name, '=');

	/*check if the name is NULL, empty, or contains an '=' character*/
	if ((name == NULL) || ((name[0] == '\0') != 0) || (equal != NULL))
	{
		perror(ENVIL);
		return (1);
	}
	env_var = _getenv(name, ptr);

	if (env_var == NULL) /*variable not found*/
	{
		perror("unsetenv: no such variable\n");
		return (1);
	}
	/*delete the node containing the environment variable*/
	deleted = delete_node(&ptr, env_var);
	return (deleted);
}

/**
 * delete_node - deletes the node with string of a list_t
 * @list: pointer to list pointer
 * @string: pointer to the string that needs to be removed from the list
 * Return: 0 on success, or 1 on failure
 */

int delete_node(list_t **list, char *string)
{
	list_t *ptr, *old_node;

	ptr = *list; /*set a pointer to the beginning of the list*/

	/*while the pointer is not NULL and the list exist*/
	while (ptr & list)
	{
		/*if the current node's string matches the input string*/
		if (_strcmp(ptr->str, string) == 0)
		{
			old_node = *list; /*set the node to the beginning of the list*/
			*list = old_node->next; /*set the list to the next node in the list*/
			free(old_node); /*free the memory ofthe old_node*/
			return (0); /*to indicatte success*/
		}
		if (_strcmp((ptr->next)->str, string) == 0)
		{
			old_node = ptr->next; /*set the old_node to the next in the list*/
			ptr->next = old_node->next;
			free(old_node->str); /*free the memory of the of the old_node's string*/
			free(old_node); /*free the memory of the old_node*/
			return (0); /*to indicate success*/
		}
		ptr = ptr->next; /*move the pointer to the next node in the list*/
	}
	return (1); /*if the string not found in the list, return 1 indicate success*/
}

/**
 * var_str - craetes new string variable wit name and value
 * @name: name of the variable
 * @value: value of a variable
 * Return: pointer to new string or NULL if failed
 */

char *var_str(char *name, char *value)
{
	char *new_value;

	if (((name[0] == '\0') != 0) || (_strchr(name, '=') != NULL))
	{
		perror(ENVIL);
		return (NULL);
	}
	if ((name == NULL) || (value == NULL))
	{
		perror(ENOMEM);
		return (NULL);
	}
	/*allocate memory for the new string*/
	new_value = malloc(_strlen(name) + _strlen(value) + 2);

	if (new_value == NULL)
	{
		perror(ENOMEM);
		return (NULL);
	}
	/*concatenate the name and value with an equal sign*/
	new_value = _strcpy(new_value, name);
	new_value = _strcat(new_value, "=");
	new_value = _strcat(new_value, value);

	return (new_value);
}
