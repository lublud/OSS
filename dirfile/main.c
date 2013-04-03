/**
 *
 * @file: main.c
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 3/04/13
 *
 * @brief Programme principale du projet d'système d'exploitation
 *
 **/

#include <stdio.h>

int main(int argc, const char *argv[])
{
	if (argc != 1)
	{
		fprintf (stderr, "Error: none argument expected.\n");
		return 1;
	}

	int pFils;

	if ( (pFils = fork ()) < 0)
	{
		perror ("fork()");
		exit (1);
	}

	return 0;
}
