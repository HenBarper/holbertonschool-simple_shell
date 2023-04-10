#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buffer = malloc(1024);
	size_t buffsize = 1024;
	char args[];
	int i = 1;

	/* allows user to type in the command line and takes it as input */

	printf("$ "); 
	getline(&buffer, &buffsize, stdin);

	token = strtok(&buffer, " ");
	args[0] = token;

	while (token)
	{
		token = strok(NULL, " ");
		args[i] = token;
		i++;
	}

	for (i = 0; args[i]; i++)
		printf("%s\n", args[i]);
}	
