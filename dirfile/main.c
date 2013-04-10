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

void Initialisation (unsigned *TailleMemoireVive, unsigned *TailleMemoireVirtuelle,
					 unsigned *TailleCadrePages, unsigned *Quantum)
{
	//char ValeurEntree[128];

	printf ("Entrez la taille de la mémoire vive : ");
	scanf ("%d", TailleMemoireVive);
	fflush (stdin);

	printf ("Entrez la taille de la mémoire virtuelle : ");
	scanf ("%d", TailleMemoireVirtuelle);
	fflush (stdin);

	printf ("Entrez la taille des cadres de page : ");
	scanf ("%d", TailleCadrePages);
	fflush (stdin);

	printf ("Entrez le quantum pour l'ordonnancement : ");
	scanf ("%d", Quantum);
	fflush (stdin);

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
