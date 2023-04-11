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
	int CoP = 666;
	int i = 0;
	//char **cmd_chk = NULL;

	while (1)
	{
		printf("Entered while loop: %d\n", CoP);
		printf("$ ");
		getline(&command, &size, stdin);
		printf("Command received: %s", command);
		words = split_string(command, &count);
		
		if (strcmp(words[0], "/bin/exit") == 0)
			break;

		for (; i < count ; i++)
		{
			printf("token %d: %s\n", i, words[i]);
		}
		
		/*
		cmd_chk[0] = "which";
		cmd_chk[1] = command;
		cmd_chk[2] = NULL;
		if (execve(cmd_chk[0], cmd_chk, NULL) == -1)
		{
			printf("Command error!!!\n");
		}
		else*/
			CoP = fork();

		printf("Forked by %d\n", CoP);

		if (CoP == 0)
		{
			printf("Child executing.\n");
			if (execve(words[0], words, NULL) == -1)
			{
				perror("Error");
				return (-1);
			}
			return (0);
		}
		else
		{
			printf("Parent waiting.\n");
			wait(NULL);
			printf("Parent awakend.\n");
		}
		printf("Just before end of while loop: %d\n", CoP);
	}

	printf("End of prog: %d\n", CoP);

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
