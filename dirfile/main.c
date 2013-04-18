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

#include "include.h"

void CalculDuNombreDeCadre ()
{
	unsigned i;
	double result;

	NombreCadreMemoireVive = TailleMemoireVive / TailleCadrePages;
	printf ("RAM creation (%d frame(s))\n", NombreCadreMemoireVive);

	/*
	if ()
		++NombreCadreMemoireVive;
	*/

	CadrePageMemVive = (SProcessus *)
					malloc (NombreCadreMemoireVive * sizeof (SProcessus));
	CadrePageMemViveRestante = (unsigned *) malloc (NombreCadreMemoireVive * sizeof (unsigned));

	for (i = 0; i < NombreCadreMemoireVive; ++i)
		CadrePageMemViveRestante [i] = TailleCadrePages;


	NombreCadreMemoireVirtuelle = TailleMemoireVirtuelle / TailleCadrePages;
	printf ("Virtual memory creation (%d frame(s))\n", NombreCadreMemoireVirtuelle);

	/*
	if ()
		++NombreCadreMemoireVirtuelle;
	*/

	CadrePageMemVirtuelle = (SProcessus *)
					malloc (NombreCadreMemoireVirtuelle * sizeof (SProcessus));
	CadrePageMemVirtuelleRestante = (unsigned *) malloc (NombreCadreMemoireVirtuelle * sizeof (unsigned));
	NbCadreMemVirtuelleLibre = NombreCadreMemoireVirtuelle;

	for (i = 0; i < NombreCadreMemoireVirtuelle; ++i)
		CadrePageMemVirtuelleRestante [i] = TailleCadrePages;

} // CalculDuNombreDeCadre ()


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
