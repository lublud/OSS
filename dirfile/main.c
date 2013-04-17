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
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

void Initialisation (unsigned *TailleMemoireVive, unsigned *TailleMemoireVirtuelle,
					 unsigned *TailleCadrePages, unsigned *Quantum)
{

	char rep[32];
	int i = -1;

	printf ("Enter RAM size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter RAM size: ");
				gets (&rep);
				break;
			}

	}
	TailleMemoireVive = atoi (&rep);

	i = -1;
	printf ("Enter virtual memory size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter virtual memory size: ");
				gets (&rep);
				break;
			}
	}
	TailleMemoireVirtuelle = atoi (&rep);

	i = -1;
	printf ("Enter frames size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter frames size: ");
				gets (&rep);
				break;
			}
	}
	TailleCadrePages = atoi (&rep);

	i = -1;
	printf ("Enter quantum: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter quantum: ");
				gets (&rep);
				break;
			}
	}
	Quantum = atoi (&rep);

} // Initialisation ()

int main(int argc, const char *argv[])
{
	if (argc != 1)
	{
		fprintf (stderr, "Error: none argument expected.\n");
		return 1;
	}

	int pFils;
	unsigned TailleMemoireVive, TailleMemoireVirtuelle, TailleCadrePages, Quantum;

	Initialisation (&TailleMemoireVive, &TailleMemoireVirtuelle, &TailleCadrePages, &Quantum);

	if ( (pFils = fork ()) < 0)
	{
		perror ("fork()");
		exit (1);
	}

	if (0 == pFils) // Fils
	{
		// ToDo
	}
	// Père

	return 0;
} // main ()
