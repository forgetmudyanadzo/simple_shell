#ifndef SHELL_H
#define SHELL_H
/*header*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdarg.h>
/*defines constants*/
#define PROMPT "$"
#define BUFF_SIZE 1024
/*error messages to display*/
#define ENVIL "Invalid argument"
#define WRONG "Something went wrong"
#define ERROR "Error"
#define ENOMEM "Out of memory"
#define END "exit"
/*define a structure for a singly linked list node*/
/**
 * struct list_s - the singly linked list
 * @str: string - (malloc string)
 * @len: the length of a string
 * @next: the next node
 * Description: node structure for singly linked list
 */
typedef struct list_s
{
	struct list_s *next;
	unsigned int len;
	char *str;
} list_t;
/*define a structure to hold the built-in*/
/**
 * struct built_in - all builtins list
 * @bi: specifier
 * @f: functions associated in printing
 */
typedef struct built_in
{
	char *bi;
	int (*f)();
} builtin_t;
/* prototypes for functions defines in shell_path.c */
void puts_half(char *str);
char *get_command_path(char *command, list_t **env_list);
int execute_command(char **argv, list_t **env_list);
char **get_path_dirs(list_t **env_list);
/* prototypes for functions defines in _getenv.c */
char *_getenv(char *name, list_t **env_list);
int _setenv(char *name, char *value, list_t **env_list);
int _unsetenv(char *name, list_t **env_list);
char *var_str(char *name, char *value);
int delete_node(list_t **list, char *string);
/* prototypes for functions defined in split_string.c */
int count_words(char *str, char delim);
char **strtow(char *str, char delim);
int _wrdlen(char *s, char delim);
/* prototypes for functions defines in strings_manipulation.c */
char *_strdup(char *str);
int _strncmp(char *s1, char *s2, int n);
char *_strcpy(char *dest, char *src);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
/* prototypes for functions defines in convert_array.c */
list_t *array_to_list(char **array);
int main(void);
int arr_size(char **arr);
void free_array(char **array);
char **list_to_array(list_t **head);
/* prototypes for functions defined in print_functions.c */
void _strprint(char *str);
size_t print_list(list_t *head);
int _putchar(char c);
void print_array(char **array);
/*declare the environ variable as an external variable*/
extern char **environ;
/* prototypes for functions defines in shell_functions.c */
int _getline(char *input, int size);
void clear_buffer(char *buffer);
char *mem_cpy(char *dest, char *src, int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int exit_shell(char **line_tok);
/* prototypes for functions defines in exit_bi.c */
int unset_env(char **token, list_t **env_head);
int exit_bi(char **token);
int set_env(char **token, list_t **env_head);
int built_ins(char **token, list_t **env_head);
int print_env(char **token, list_t **env_head);
/* prototypes or function defines in shell_executes.c */
int cmd_line_loop(char *buffer, char *line, list_t **env_head);
/* prototypes for functions defines in string_manipulation.c */
int len_to_char(char *str, char c);
char *_strchr(char *str, char c);
int _strcmp(char *str1, char *str2);
int _atoi(char *str);
/* prototypes for functions defines in linked_list.c */
list_t *add_node_end(list_t **head, char *str);
void free_list(list_t *head);
size_t list_length(list_t *head);
list_t *add_node(list_t **head, char *str);
list_t *get_node(list_t **head, char *str);
#endif
