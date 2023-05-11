#include "shell.h"

/**
 * built_ins - checks if a command is a shell built-in function and executes
 * @token: array of tokens parsed from the command line input
 * @env_head: pointer to the head of the linked list containing
 * environment variables
 * Return: 0 on success, 1 on error, or -1 if the command is not
 *	a built-in function
 */

int built_ins(char **token, list_t **env_head)
{
	builtin_t builtins[] = {
		{"exit", exit_bi},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL} /*mark the end of the array with struct whose members are NULL*/
	};

	int loop_index, func_return;/*declare integer variables*/
	list_t *env_ptr;/*declare a pointer to the head of the environment list*/

	/*set the pointer to the head of the environment list*/
	env_ptr = *env_head;

	/*if the input is NULL, return an error*/
	if (!token)
	{
		perror("built_ins");
		return (1);
	}
	loop_index = 0; /*initialize the counter variable*/

	/*loop through the built-in array until the end*/
	while ((builtins + loop_index)->bi != NULL)
	{/*if the first element of the input matches a built-in command*/
		if (_strcmp(token[0], (builtins + loop_index)->bi) == 0)
		{
			/*if the command is "end", execute the command and return its return value*/
			if (_strcmp(token[0], END) == 0)
			{
				func_return = (builtins + loop_index)->f(token);
				return (func_return);
			}
			func_return = (builtins + loop_index)->f(token, &env_ptr);
			return (func_return);
		}
		loop_index++;/*increament the counter*/
	}
	return (-1);
}

/**
 * exit_bi - terminate the shell with a given exit status
 * @token: array of tokens parsed from the command line input
 * Return: the given exit status or 0 if no status is specified
 */

int exit_bi(char **token)
{
	int token_count, exit_code;/*declare integer variables*/

	/*get the size of the input array*/
	token_count = arr_size(token);

	/*if the input array has more than 2 elements, print an error and returns 1*/
	if (token_count > 2)
	{
		_strprint("Failed: Command syntax: exit status\n");
		return (1);
	}
	if (token_count == 1)
		return (0);
	/*if inpt array has 2 element, parse second elment as integer and retrn it*/
	if (token_count == 2)
	{
		exit_code = _atoi(token[1]);
		return (exit_code);
	}
	return (1);/*if anything else happens, return 1*/
}

/**
 * print_env - prints current environment variables
 * @token: array of tokens parsed from command line input
 * @env_head: a pointer to the head of the linked list containing
 * environment variables
 * Return: 0 on success, or 1 on error
 */

int print_env(char **token, list_t **env_head)
{
	int token_count;/*declare an integer variable*/
	list_t *env_ptr;/*declare a pointer to the head of the environment list*/

	/*set the pointer to the head of the environment list*/
	env_ptr = *env_head;
	token_count = arr_size(token);

	/*if the is more than 1 element, print an error message and return 1*/
	if (token_count > 1)
	{
		_strprint("Filed: Command syntax: env\n");
		return (1);
	}
	print_list(env_ptr);
	return (0);
}

/**
 * set_env - initialize a new environment variable or modify an existing one
 * @token: an array of tokens parsed from the command line input
 * @env_head: a pointer to the head of the linked list containing
 * environment variables
 * Return: returns 0 on success, 1 on error
 */

int set_env(char **token, list_t **env_head)
{
	int token_count;
	int func_return;
	list_t *env_ptr;

	env_ptr = *env_head;
	token_count = arr_size(token);

	if (token_count != 3)
	{
		_strprint("Failed: Command syntanx: setenv VARIABLE VALUE\n");
		return (1);
	}
	func_return = _setenv(token[1], token[2], &env_ptr);
	return (func_return);
}

/**
 * unset_env - remove the environment variable
 * @token: token tokenized from the command line
 * @env_head: a pointer to the head of the linked list
 * Return: 0 on success, 1 if failed
 */

int unset_env(char **token, list_t **env_head)
{
	int token_count, func_return;
	list_t *env_ptr;

	env_ptr = *env_head;
	token_count = arr_size(token);

	if (token_count != 2)
	{
		_strprint("Failed: Command syntax: unsetenv VARIABLE\n");
		return (1);
	}
	func_return = _unsetenv(token[1], &env_ptr);
	return (func_return);
}
