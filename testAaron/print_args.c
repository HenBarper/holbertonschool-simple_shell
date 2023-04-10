#include <stdio.h>
#include <stdlib.h>

int print_args(int ac, char **av)
{
	int i = 0;

	

	while (av[i])
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}
