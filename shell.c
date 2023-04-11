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


	while (1)
	{

		printf("$ ");
		getline(&command, &size, stdin);
		words = split_string(command, &count);
		
		if (strcmp(words[0], "/bin/exit") == 0)
			exit(EXIT_SUCCESS);

		if (access(words[0], X_OK) == 0)
			CoP = fork();
		else
		{
			perror("Errorvvvvvvvvvvvv");
		}

		if (CoP == 0)
		{
			if (execve(words[0], words, NULL) == -1)
			{
				perror("Error");
				return (-1);
			}
			return (0);
		}
		else
		{
			wait(NULL);
		}
	}

	free(words);
	free(command);
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
			cmd = malloc(strlen("/bin/") + strlen(token) + 1);
			strcpy(cmd, "/bin/");
			strcat(cmd, token);
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
	for (j = 0 ; j < i ; j++)
	{
		result[j] = words[j];
	}
	result[i] = NULL;

	return (result);
}
