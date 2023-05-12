#include "shell.h"

/**
 * cmd_line_loop - reads user input and executes commands
 * until user exits or EOF(ctrl^D)
 * @buffer: buffer to store input
 * @line: pointer to a string of the line input
 * @env_head: pointer to the head of the environment list
 * Return: 0 on success, or 1 if _realloc failed
 */

int cmd_line_loop(char *buffer, char *line, list_t **env_head)
{
	list_t *env_list_ptr;
	int input_len, old_len, retval = 0;
	char **token;

	env_list_ptr = *env_head;
	while (1)/*continusly loop untl user "exit" or EOF (ctrl-D*/
	{
		clear_buffer(buffer); /*clear the buffer for new input*/
		input_len = _getline(buffer, BUFF_SIZE); /*read in input from user*/
		/*if chars_read is -1, the user has entered EOF, so break the loop*/
		if (input_len == -1)
			break;
		if (line == NULL)
			old_len = 0;
		else
			old_len = _strlen(line);
		line = _realloc(line, old_len, ++input_len);
		if (line == NULL)
		{
			perror("ENOMEM");
			retval = 1;
			break;
		}
		line = mem_cpy(line, buffer, input_len);
		if (line[0] != '\0')
		{
			token = strtow(line, ' ');
			retval = built_ins(token, &env_list_ptr);
			if (exit_shell(token) && retval != -1)
			{
				free_array(token);
				break;
			}
			if (retval == -1)
				retval = execute_command(token, &env_list_ptr);
			free_array(token);
		}
	}
	free(line);
	return (retval);
}
