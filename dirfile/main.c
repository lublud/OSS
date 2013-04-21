/**
 *
 * @file:	main.c
 *
 * @author:	Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date:	3/04/13
 *
 * @brief:	Programme principale du projet d'système d'exploitation
 *
 **/

#include "include.h"


int main(int argc, const char *argv[])
{
	if (argc != 1)
	{
		fprintf (stderr, "Error: no argument expected.\n");
		return 1;
	}

	int pFils;

	Initialisation ();

	printf ("\n\nCalculating page frame's number ...\n");
	CalculDuNombreDeCadre ();
	
	AfficheMenuChoix ();

	/*
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
	*/

	return 0;

} // main ()
