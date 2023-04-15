#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/* Prototypes */
/*char **split_string(char *str);*/
/*char **split_path(char *thePath);*/
void tokenize_string(char *str, char *delims, char **tokens);
int create_child(char *call_path, char **str_arr);
int check_path(char **path_array, char **token_array);

/*String Helpers*/
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);

#endif
