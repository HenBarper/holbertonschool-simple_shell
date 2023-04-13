#include "shell.h"

#define MAX_ARGS 100

char **split_string(char *str, int *count);

/**
 * main - entry point
 *
 * Return: int
 */
int main(void)
{
	char *command = NULL;
	size_t size = 0;
	char **words = NULL;
	int count;
	int CoP = 777;
	int i = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&command, &size, stdin) == -1)
		{
			exit(EXIT_SUCCESS);
		}

		if (command[0] == '\n')
			continue;
		else
			words = split_string(command, &count);

		if (strcmp(words[0], "/bin/exit") == 0)
		{
			while (words[i])
			{
				free(words[i]);
				i++;
			}

			free(words);
			free(command);
			exit(EXIT_SUCCESS);
		}

		if (access(words[0], X_OK) == 0)
		{
			CoP = fork();
			if (CoP == 0)
			{
				if (execve(words[0], words, NULL) == -1)
				{
					perror("Execve Error");
					return (-1);
				}
				return (0);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
			perror("Command Error");
		}
	}
	return (0);
}

/**
 * split_string - splits the string into arr of strings
 * @str: string
 * @count: count of strings
 * Return: char ptr
 */
char **split_string(char *str, int *count)
{
	char *token;
	char *words[MAX_ARGS];
	char **result;
	int i = 0;
	int j;
	char *cmd;

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
	*count = i;

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
	free(token);
	result[i] = NULL;
	return (result);
}
