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

	pthread_t ThreadRR;
	int res;
	
	CreerTerminalAffichage ();

	Initialisation ();

	printf ("\n\nCalculating page frame's number ...\n");
	CalculDuNombreDeCadre ();
	
	res = pthread_create (&ThreadRR, NULL, FilePriorite, NULL);
	
	AfficheMenuChoix ();

	pthread_cancel (ThreadRR);
	
	fprintf(SortieAffichage, "\nOSS terminated ! Please close the window.\n");
	
	return 0;

} // main ()
