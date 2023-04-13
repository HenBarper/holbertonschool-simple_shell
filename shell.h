#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/* Prototypes */
char **split_string(char *str, int *count);
int main(void);

/*String Helpers*/
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);

#endif
