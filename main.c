#include "shell.h"

/**
 * main - Entry point of the shell
 * Return: 0 on (success)
 */

int main(void)
{
	char *input, *cmd;/*pointer to character arrays*/
	list_t *env_list;/*pointer to a linked list*/
	int status;/*integer to store the status of the command line loop*/

	/*allocate memory for the input buffer using malloc ()*/
	input = malloc(sizeof(char) * BUFF_SIZE);

	/*check if memory was allocated successfully*/
	if (input == NULL)
		return (1);/*return an error code if memory allocation failed*/
	cmd = NULL;/*set the pointer to NULL*/
	/*convert the environment variables array into a linked list*/
	env_list = array_to_list(environ);
	/*call the command line loop function and store the return status*/
	status = cmd_line_loop(input, cmd, &env_list);

	/*free the memory allocated for the linked list and input buffer*/
	free_list(env_list);
	free(input);
	/*return the status of the command line loop to the calling function*/
	return (status);
}
