#include "main.h"

/*#define MAX_ARGS 100*/

/*char **split_string(char *str);*/
/*char **split_path(char *thePath);*/
void tokenize_string(char *str, char *delims, char **tokens);
int create_child(char *call_path, char **str_arr);
int check_path(char **path_array, char **token_array);

/**
 * main - entry point
 *
 * Return: int
 */
int main(void)
{
	char *input = NULL;
	char *path = NULL;
	size_t size = 0;
	char *tokarr[20];
	char *patharr[20];
	int ret_value = 0;

	path = getenv("PATH");
	tokenize_string(path, ":", patharr);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&input, &size, stdin) == -1)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		tokenize_string(input, " \n\t", tokarr);

		if (!tokarr[0] || _strcmp(tokarr[0], "env") == 0)
			continue;
		if (_strcmp(tokarr[0], "exit") == 0)
		{
			/*fflush(stdin);*/
			free(input);
			exit(EXIT_SUCCESS);
		}

		if (access(tokarr[0], X_OK) == 0)
			create_child(tokarr[0], tokarr);
		else
			ret_value = check_path(patharr, tokarr);

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
	/*char *saveptr;*/
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
 * @path_array: the string array containing the paths
 * @token_array: the string array of tokens
 * Return: int 127
 */
int check_path(char **path_array, char **token_array)
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
			create_child(comp_path, token_array);
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
 * @call_path: path of system call
 * @str_arr: array of string
 * Return: int
 */
int create_child(char *call_path, char **str_arr)
{
	pid_t cop;
	pid_t sig;
	int status = 0;

	cop = fork();
	if (cop == 0)
	{
		if (execve(call_path, str_arr, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (cop < 0)
		exit(EXIT_FAILURE);
	else
	{
		do {
			sig = waitpid(cop, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	(void) sig;
	return (status);
}


/*char **split_string(char *str)
{
	char *token;
	char *words[MAX_ARGS];
	char **result;
	int i = 0;
	int j;
	char *cmd = NULL;

	token = strtok(str, " \n");
	while (token != NULL && i < MAX_ARGS)
	{
		if (i == 0 && token[0] != '/')
		{
			cmd = malloc(_strlen("/bin/") + _strlen(token) + 1);
			if (cmd == NULL)
			{
				perror("malloc error");
				free(cmd);
				exit(EXIT_FAILURE);
			}
			_strcpy(cmd, "/bin/");
			_strcat(cmd, token);
			words[i] = cmd;
		}
		else
		{
			words[i] = token;
		}
		i++;
		token = strtok(NULL, " \n");
	}

	result = malloc((i + 1) * sizeof(char *));
	if (result == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	for (j = 0 ; j < i ; j++)
	{
		result[j] = words[j];
	}
	result[i] = NULL;

	if (j == 0 && words[j][0] != '/')
		free(cmd);

	return (result);
}

char **split_path(char *thePath)
{
	char *tok;
	char *array[MAX_ARGS];
	char **res;
	int i = 0;
	int j;

	tok = strtok(thePath, ":");
	while (tok != NULL && i < MAX_ARGS)
	{
		array[i] = tok;
		i++;
		tok = strtok(NULL, ":");
	}

	res = malloc((i + 1) * sizeof(char *));
	if (res == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	for (j = 0 ; j < i ; j++)
	{
		res[j] = array[i];
	}
	res[i] = NULL;

	return (res);
}*/
