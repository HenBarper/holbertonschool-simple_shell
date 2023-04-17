#include "main.h"

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);

/**
 * *_strcat - concats two strings together
 * @dest: starting string
 * @src: string to add
 * Return: finished string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * *_strcpy - copy a string
 * @src: source
 * @dest: destination
 * Return: copied string
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	while (*(src + a))
	{
		*(dest + a) = *(src + a);
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

/**
 * _strlen - find length of string
 * @s: string
 * Return: string length
 */
int _strlen(char *s)
{
	int a = 0;

	while (*(s + a) != '\0')
	{
		a++;
	}
	return (a);
}

/**
 * _strncmp - compares strings up to n chars
 * @s1: first string
 * @s2: second string
 * @n: num of chars to compare
 * Return: first dif or 0 if none
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0, dif = 0;

	while (s1[i] && s2[i] && (i < n))
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
			dif = s1[i] - s2[i];
			break;
		}
	}
	return (dif);
}

/**
 * _strcmp - compares strings ASCII values
 * @s1: string 1
 * @s2: string 2
 * Return: number of differences
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, dif = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
			dif = s1[i] - s2[i];
			break;
		}
	}
	return (dif);
}
