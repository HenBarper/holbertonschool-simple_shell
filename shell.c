#include "main.h"

void tokenize_string(char *str, char *delims, char **tokens);
int create_child(char *stdpath, char *call_path, char **str_arr);
int check_path(char *stdpath, char **path_array, char **token_array);
char *_strdup(char *str);

/**
 * main - entry point
 * @argc: arg counter
 * @argv: array of args
 * @env: environment
 * Return: int
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL, *path = NULL;
	size_t size = 0;
	char *tokarr[20], *patharr[20];
	int ret_value = 0, i;

	(void)argc;
	(void)argv;
	while (1)
	{
		i = 0;
		while (env[i] != NULL)

		{
			if (_strncmp(env[i], "PATH=", 5) == 0)
			{
				path = _strdup((env[i] + 5));
				break;
			}
			i++;
		}
		tokenize_string(path, ":", patharr);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "BENRON $ ", 9);
		if (getline(&input, &size, stdin) == -1)
		{
			free(input);
			free(path);
			exit(EXIT_SUCCESS);
		}
		tokenize_string(input, " \n\t", tokarr);

		if (!tokarr[0])
		{
			free(path);
			continue;
		}
		if (_strcmp(tokarr[0], "exit") == 0)
		{
			free(input);
			free(path);
			exit(EXIT_SUCCESS);
		}
		if (_strcmp(tokarr[0], "env") == 0)
		{
			for (i = 0 ; env[i] != NULL ; i++)
			{
				write(STDOUT_FILENO, env[i], _strlen(env[i]));
				write(STDOUT_FILENO, "\n", 1);
			}
			free(path);
			continue;
		}

		if (access(tokarr[0], X_OK) == 0)
			create_child(path, tokarr[0], tokarr);
		else
			ret_value = check_path(path, patharr, tokarr);

	}
	return (ret_value);
}


/**
 * tokenize_string - tokenize a passed in string
 * @str: string to tokenize
 * @delims: deliminators
 * @tokens: the array to save the tokens
 * Return: void
 */
void tokenize_string(char *str, char *delims, char **tokens)
{
	char *path_token = strtok(str, delims);
	int i = 0;

	while (path_token != NULL)
	{
		tokens[i] = path_token;
		i++;
		path_token = strtok(NULL, delims);
	}
	tokens[i] = NULL;
}

/**
 * check_path - check if the path leads to a system call
 * @stdpath: the path variable to free
 * @path_array: the string array containing the paths
 * @token_array: the string array of tokens
 * Return: int 127
 */
int check_path(char *stdpath, char **path_array, char **token_array)
{
	int i = 0;
	char *comp_path = NULL;
	struct stat x;

	while (path_array[i] != NULL)
	{
		comp_path = malloc(_strlen(token_array[0]) + _strlen(path_array[i]) + 2);
		_strcpy(comp_path, path_array[i]);
		_strcat(comp_path, "/");
		_strcat(comp_path, token_array[0]);
		if (stat(comp_path, &x) == 0)
		{
			create_child(stdpath, comp_path, token_array);
			free(comp_path);
			return (0);
		}
		free(comp_path);
		i++;
	}
	return (127);
}

/**
 * create_child - function to create child process
 * @stdpath: the path variable to free
 * @call_path: path of system call
 * @str_arr: array of string
 * Return: int
 */
int create_child(char *stdpath, char *call_path, char **str_arr)
{
	pid_t cop;
	pid_t sig;
	int status = 0;

	free(stdpath);
	cop = fork();
	if (cop == 0)
	{
		if (execve(call_path, str_arr, NULL) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else if (cop < 0)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			sig = waitpid(cop, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	(void) sig;
	return (status);
}

/**
 * *_strdup - ret ptr to newly allocated mem space
 * @str: string
 * Return: NULL or ptr to dupe string
 */
char *_strdup(char *str)
{
	int i = 0;
	int n = 0;
	char *ar;

	if (str == NULL)
	{
		return (NULL);
	}
	while (str[i] != '\0')
	{
		i++;
		n++;
	}
	n++;

	ar = malloc(n * sizeof(char));
	if (ar == NULL)
	{
		return (NULL);
	}

	for (i = 0 ; i < n ; i++)
	{
		ar[i] = str[i];
	}

	return (ar);
}
