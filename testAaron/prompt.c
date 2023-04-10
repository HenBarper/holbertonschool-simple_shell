#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buffer = malloc(1024);
	size_t buffsize = 1024;

	printf("$ ");
	getline(&buffer, &buffsize, stdin);
	printf("%s ", buffer);
	
	return(buffsize);
}
