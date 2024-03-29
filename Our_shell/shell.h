#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

	void prompt(char **av, char **env);
	int proc_file_commands(char *file_path, int *exe_ret);
	extern char **environ;
	char *name;
	int hist;

/**
 * struct list_s - New struct type defining a linked list
 *
 * @dir: directory path
 * @next: pointer to another struct list_s
 */

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - New struct type defining builtin commands
 *
 * @name: name of the builtin command
 * @f: function pointer to the builtin command's function
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - New struct defining aliases
 *
 * @name: name of the alias
 * @value: value of the alias
 * @next: pointer to another struct alias_s
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

	/* Global aliases for linked list */
	alias_t *aliases;

	/* Main helpers */
	ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
	void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
	char **_strtok(char *line, char *delim);
	char *get_location(char *command);
	list_t *get_path_dir(char *path);
	int execute(char **args, char **front);
	void free_list(list_t *head);
	char *_itoa(int num);

	/* Input helpers */
	void handle_line(char **line, ssize_t read);
	void variable_replacement(char **args, int *exe_ret);
	char *get_args(char *line, int *exe_ret);
	int call_args(char **args, char **front, int *exe_ret);
	int run_args(char **args, char **front, int *exe_ret);
	int handle_args(int *exe_ret);
	int check_args(char **args);
	void free_args(char **args, char **front);
	char **replace_aliases(char **args);

	/* String functions */
	int _strlen(const char *str);
	char *_strcat(char *dest, const char *src);
	char *_strncat(char *dest, const char *src, size_t n);
	char *_strcpy(char *dest, const char *src);
	char *_strchr(char *str, char c);
	int _strspn(char *str, char *accept);
	int _strcmp(char *str1, char *str2);
	int _strncmp(const char *str1, const char *str2, size_t n);

	/* Builtins */
	int (*get_builtin(char *command))(char **args, char **front);
	int shellby_exit(char **args, char **front);
	int shellby_env(char **args, char __attribute__((__unused__)) **front);
	int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
	int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
	int shellby_cd(char **args, char __attribute__((__unused__)) **front);
	int shellby_alias(char **args, char __attribute__((__unused__)) **front);
	int shellby_help(char **args, char __attribute__((__unused__)) **front);

	/* Builtin helpers */
	char **_copyenv(void);
	void free_env(void);
	char **_getenv(const char *var);

	/* Error handlers */
	int create_error(char **args, int err);
	char *error_env(char **args);
	char *error_1(char **args);
	char *error_2_exit(char **args);
	char *error_2_cd(char **args);
	char *error_2_syntax(char **args);
	char *error_126(char **args);
	char *error_127(char **args);

	/* Linked_list helpers */
	alias_t *add_alias_end(alias_t **head, char *name, char *value);
	void free_alias_list(alias_t *head);
	list_t *add_node_end(list_t **head, char *dir);
	void free_list(list_t *head);

	void help_all(void);
	void help_alias(void);
	void help_cd(void);
	void help_exit(void);
	void help_help(void);
	void help_env(void);
	void help_setenv(void);
	void help_unsetenv(void);
	void help_history(void);

#endif

