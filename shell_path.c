#include "shell.h"

/**
 * get_path_dirs - returns an array of directories
 * listed in the PATH variable
 * @env_list: pointer to a linked list of environment variables
 * Return: an array of pointers to directories, or NULL on error
 */

char **get_path_dirs(list_t **env_list)
{
	char *path_var;
	char *path_val;
	char **dirs_array;
	char delimiter = ':';
	char *array = "PATH";
	list_t *env_ptr;

	/*get the value of the PATH environment variable*/
	env_ptr = *env_list;
	path_var = _getenv(array, &env_ptr);
	/*extract the directories from the PATH value*/
	path_val = _strdup(path_var + 5); /*skips over "PATH=" prfix*/
	dirs_array = strtow(path_val, delimiter);
	if (dirs_array == NULL)
	{
		free(path_val);
		return (NULL);
	}
	free(path_val);
	return (dirs_array);
}
/**
 * get_command_path - finds the absolute path of a command by
 * searching the PATH
 * @command: the command to search for
 * @env_list: pointer to a linked list of environment variables
 * Return: the absolute path of the command if found, otherwise
 *	the original command string
 */
char *get_command_path(char *command, list_t **env_list)
{
	char **path_dirs, *command_path;
	int index, m, status, len;
	list_t *env_ptr;

	for (m = 0; command[m] != '\0'; m++)
	{
		if (command[m] == '/' && command[m + 1] != '\0' && command[m + 1] != '/' &&
			access(command, F_OK | X_OK) == 0)
			return (command);
	}
	if ((command[0] == '/' || command[0] == '.') && command[m] == '\0')
	{
		_strprint(command);
		_strprint(": not found\n");
		return (NULL);
	}
	env_ptr = *env_list;/*check each directory in PATH for commnd*/
	path_dirs = get_path_dirs(&env_ptr);
	if (path_dirs == NULL)
	{
		perror(ENOMEM);
		return (NULL);
	}
	for (index = 0; path_dirs[index] != NULL; index++)
	{
		command_path = _strdup(path_dirs[index]); /*build path command*/
		status = _strlen(command_path);
		len = _strlen(command);
		command_path = _realloc(command_path, status, status + len + 2);
		command_path = _strcpy(command_path, path_dirs[index]);
		command_path = _strcat(command_path, "/");
		command_path = _strcat(command_path, command);
		if (access(command_path, F_OK) == 0)
		{
			free_array(path_dirs); /*command found, return the absolute path*/
			return (command_path);
		}
	}
	free_array(path_dirs);
	return (command);
}
/**
 * execute_command - forks a new process to run a command with arguments
 * @argv: array of arguments, with the first argument being the command
 * @env_list: pointer to a linked list of environment variables
 * Return: 0 on success, 1 on error
 */
int execute_command(char **argv, list_t **env_list)
{
	pid_t child_pid;
	int status;
	char **envp_array;
	char *command_path;
	list_t *env_ptr;

	env_ptr = *env_list;/*convert environ variables to array*/
	envp_array = list_to_array(&env_ptr);
	if (envp_array == NULL)
	{
		perror(ENOMEM);
		return (1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("execute_command: child pid is -1");
		free(envp_array);
		return (1);
	}
	if (child_pid == 0)
	{
		/*find the absolute path of the command*/
		command_path = get_command_path(argv[0], &env_ptr);
		if (command_path == NULL)
			exit(1);
		/*replace the current process with the command*/
		if (execve(command_path, argv, envp_array) == -1)
		{
			perror("execve");
				exit(1);
		}
	}
	else
	{
		wait(&status);
	}
	free(envp_array);
	return (0);
}
